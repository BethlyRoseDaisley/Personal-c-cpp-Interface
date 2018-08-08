#ifndef _LOG_FILE_HH
#define _LOG_FILE_HH
#include <string>
#include "ScopePtr.hh"
#include "MutexLock.hh"

namespace FileUtil{
	class AppendFile;
}

class LogFile
{
public:
	LogFile(const std::string& baseName, off_t rollSize = 2048*1000, bool threadSafe = true, int flushInterval = 3);
	~LogFile();

	void append(const char* logline, int len);
	void flush();

private:
	void append_unlocked(const char* logline, int len);

	//static std::string getlogFileName(const std::string& baseName);
	bool rollFile();

	const std::string m_baseName;
	const int m_flushInterval;

	off_t m_roolSize;
	scoped_ptr<MutexLock> m_mutex;
	scoped_ptr<FileUtil::AppendFile> m_file;
};

#endif