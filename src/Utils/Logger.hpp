#pragma once
#include <sys/param.h>
#include <sys/lock.h>
#include <sys/mutex.h>

enum LogLevels
{
	LL_None,
	LL_Info,
	LL_Warn,
	LL_Error,
	LL_Debug,
	LL_All
};

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define Logger_MaxBuffer 0x500
#ifdef _DEBUG
#define WriteLog(x, y, ...) Mira::Utils::Logger::GetInstance()->WriteLog_Internal(x, __PRETTY_FUNCTION__, __LINE__, y, ##__VA_ARGS__)
#else
#define WriteLog(x, y, ...)
#endif

namespace Mira
{
	namespace Utils
	{
		class Logger
		{
		private:
			static Mira::Utils::Logger* m_Instance;

			enum LogLevels m_LogLevel;
			char m_Buffer[Logger_MaxBuffer];
			char m_FinalBuffer[Logger_MaxBuffer];

			volatile int32_t m_Handle;
			struct mtx m_Mutex;

		protected:
			Logger();
			~Logger();

		public:
			static Mira::Utils::Logger* GetInstance();

			void WriteLog_Internal(enum LogLevels p_LogLevel, const char* p_Function, int32_t p_Line, const char* p_Format, ...);
		};
	}
}
struct logger_t
{
	enum LogLevels logLevel;

	char buffer[Logger_MaxBuffer];
	char finalBuffer[Logger_MaxBuffer];

	// Handle to log file on hdd
	volatile int logHandle;

	struct mtx mutex;
};

extern struct logger_t* gLogger;

void logger_init(struct logger_t* logger);
void logger_writelog(struct logger_t* logger, enum LogLevels level, const char* function, int line, const char* fmt, ...);