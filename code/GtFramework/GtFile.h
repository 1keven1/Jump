/**
  @file GtFile.h

  @author Kaiming

  @brief 文件类

  更改日志 history
  ver:1.0

 */

#ifndef GtFile_h__
#define GtFile_h__

class GtFile
{
public:
	GtFile(const std::string& name);
	~GtFile(void);

	void	Open();
	bool	IsOpen() { return m_open; }
	void	Close();
	char* Data() const;
	uint32  Size() const { return m_size; }

private:
	bool m_open;
	std::string m_name;
	char* m_data;
	uint32 m_size;
};

#endif



