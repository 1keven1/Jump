//输入消息结构和枚举

/**
 *@brief 输入状态
 */
enum EInputState
{
	eIS_Unknown = 0,
	eIS_Pressed = (1 << 0),
	eIS_Released = (1 << 1),
	eIS_Down = (1 << 2),
	eIS_Changed = (1 << 3),
};

#define KI_KEYBOARD_BASE	0
#define KI_MOUSE_BASE		256
#define KI_XINPUT_BASE		512

/**
 *@brief 抽象按键消息
 */
enum EKeyId
{
	eKI_Escape = KI_KEYBOARD_BASE,
	eKI_1,
	eKI_2,
	eKI_3,
	eKI_4,
	eKI_5,
	eKI_6,
	eKI_7,
	eKI_8,
	eKI_9,
	eKI_0,
	eKI_Minus,
	eKI_Equals,
	eKI_Backspace,
	eKI_Tab,
	eKI_Q,
	eKI_W,
	eKI_E,
	eKI_R,
	eKI_T,
	eKI_Y,
	eKI_U,
	eKI_I,
	eKI_O,
	eKI_P,
	eKI_LBracket,
	eKI_RBracket,
	eKI_Enter,
	eKI_LCtrl,
	eKI_A,
	eKI_S,
	eKI_D,
	eKI_F,
	eKI_G,
	eKI_H,
	eKI_J,
	eKI_K,
	eKI_L,
	eKI_Semicolon,
	eKI_Apostrophe,
	eKI_Tilde,
	eKI_LShift,
	eKI_Backslash,
	eKI_Z,
	eKI_X,
	eKI_C,
	eKI_V,
	eKI_B,
	eKI_N,
	eKI_M,
	eKI_Comma,
	eKI_Period,
	eKI_Slash,
	eKI_RShift,
	eKI_NP_Multiply,
	eKI_LAlt,
	eKI_Space,
	eKI_CapsLock,
	eKI_F1,
	eKI_F2,
	eKI_F3,
	eKI_F4,
	eKI_F5,
	eKI_F6,
	eKI_F7,
	eKI_F8,
	eKI_F9,
	eKI_F10,
	eKI_NumLock,
	eKI_ScrollLock,
	eKI_NP_7,
	eKI_NP_8,
	eKI_NP_9,
	eKI_NP_Substract,
	eKI_NP_4,
	eKI_NP_5,
	eKI_NP_6,
	eKI_NP_Add,
	eKI_NP_1,
	eKI_NP_2,
	eKI_NP_3,
	eKI_NP_0,
	eKI_F11,
	eKI_F12,
	eKI_F13,
	eKI_F14,
	eKI_F15,
	eKI_Colon,
	eKI_Underline,
	eKI_NP_Enter,
	eKI_RCtrl,
	eKI_NP_Period,
	eKI_NP_Divide,
	eKI_Print,
	eKI_RAlt,
	eKI_Pause,
	eKI_Home,
	eKI_Up,
	eKI_PgUp,
	eKI_Left,
	eKI_Right,
	eKI_End,
	eKI_Down,
	eKI_PgDn,
	eKI_Insert,
	eKI_Delete,
	eKI_LWin,
	eKI_RWin,
	eKI_Apps,
	eKI_OEM_102,

	// Mouse.
	eKI_Mouse1 = KI_MOUSE_BASE,
	eKI_Mouse2,
	eKI_Mouse3,
	eKI_Mouse4,
	eKI_Mouse5,
	eKI_Mouse6,
	eKI_Mouse7,
	eKI_Mouse8,
	eKI_MouseWheelUp,
	eKI_MouseWheelDown,
	eKI_MouseX,
	eKI_MouseY,
	eKI_MouseZ,
	eKI_MouseLast,

	// Terminator.
	eKI_Unknown = 0xffffffff,
};

/**
 *@brief 抽象设备id
 */
enum EDeviceId
{
	eDI_Keyboard = 0,
	eDI_Mouse = 1,
	eDI_Unknown = 0xff,
};

struct SKeyState;

struct SInputEvent
{
	EDeviceId		deviceId;
	EInputState		state;
	EKeyId			keyId;
	float			value;
	SKeyState* keyStatePtr;

	SInputEvent()
	{
		deviceId = eDI_Unknown;
		state = eIS_Released;
		keyId = eKI_Unknown;
		value = 0;
		keyStatePtr = 0;
	}
};
struct IInputEventListener
{
	virtual bool OnInputEvent(const SInputEvent& event) = 0;
};