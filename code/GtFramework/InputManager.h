/**
  @file InputManager.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef InputManager_h__
#define InputManager_h__

#include "prerequisite.h"
#include <dinput.h>
#include <dinputd.h>

struct SInputSymbol;

struct SKeyState
{
	SKeyState(EKeyId id) :keyId(id)
	{
		state = eIS_Released;
		value = 0;
	}

	void MakeEvent(SInputEvent& event)
	{
		event.keyId = keyId;
		event.state = state;
		event.value = value;
		event.keyStatePtr = this;
	}

	EKeyId		keyId;
	EInputState state;
	float		value;
};
typedef std::vector<IInputEventListener*> InputEventListeners;

class SrInputManager;

struct InputDeviceBase
{
	InputDeviceBase(SrInputManager* creator, const char* deviceName, const GUID& guid);
	virtual ~InputDeviceBase();

	virtual const char* GetDeviceName() const = 0;
	virtual EDeviceId		GetDeviceId() const = 0;

	virtual bool			Init() = 0;
	virtual void			Update(bool bFocus) = 0;

	bool CreateDirectInputDevice(const DIDATAFORMAT* dataFormat, DWORD coopLevel, DWORD bufSize);
	bool Acquire();
	bool Unacquire();
	IDirectInputDevice8* GetDevice() { return m_pDevice; }
	SrInputManager* GetInputManager() { return m_creator; }
	EDeviceId				m_deviceId;

protected:
	SrInputManager* m_creator;
	IDirectInputDevice8* m_pDevice;
	const GUID& m_guid;
	const DIDATAFORMAT* m_pDataFormat;
	DWORD					m_dwCoopLevel;
	bool					m_bNeedsPoll;
};

typedef std::vector<InputDeviceBase*> InputDevices;

class SrInputManager
{
public:
	SrInputManager(void);
	~SrInputManager(void);
	HRESULT Init(HWND hDlg);
	void Destroy();
	void Update();

	void FreeDirectInput();

	IDirectInput8* getDI() { return m_pDI; }
	HWND getHwnd() { return m_hWnd; }

	bool PostInputEvent(SInputEvent& event);

	void AddListener(IInputEventListener* listener);
	void RemoveListener(IInputEventListener* listener);
	bool AddInputDevice(InputDeviceBase* pDevice);
private:
	HWND m_hWnd;

	IDirectInput8* m_pDI; // DirectInput interface       
	InputEventListeners		m_listeners;
	InputDevices			m_inputDevices;

	std::vector<SKeyState*> m_holdKeys;
};

#endif


