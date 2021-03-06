#include "scoped_ptr.hh"
#include "Logger.hh"
#include "LogStream.hh"
#include "FileUtil.hh"
#include "LogFile.hh"
#include "SyncLogging.hh"
#include "TimeStamp.hh"
#include <errno.h>
#include <unistd.h>
#include <assert.h>

const off_t kRollSize = 1024*200;

SyncLogging* g_SyncLogging = NULL;

void SyncLoggingOutput(const char* logline, int len){
	g_SyncLogging->append(logline, len);
}

void SyncLoggingflush(){
	g_SyncLogging->flush();
}

void prinTime()
{
	TimeStamp m_time(TimeStamp::now());
	int64_t microSecondsSinceEpoch = m_time.microSecondsSinceEpoch();
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / TimeStamp::kMicroSecondsPerSecond);
	int microseconds = static_cast<int>(microSecondsSinceEpoch % TimeStamp::kMicroSecondsPerSecond);
	struct tm tm_time;

	::gmtime_r(&seconds, &tm_time); // FIXME TimeZone::fromUtcTime

	int len = printf("%4d-%02d-%02d %02d:%02d:%02d",
	tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
	tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec);

	Fmt us(".%06d ", microseconds);
	assert(us.length() == 8);
	printf(":%s\n", us.data());
}


int main(){

/*
	//scoped_ptr test
	scoped_ptr<LogStream> lsp(new LogStream);
	
	LogStream()<<"stream test\n";
	(*lsp)<<"scope_test\n";
*/
	
	//fileutil test
/*	FileUtil::AppendFile testfile("./testfile");
	testfile.append("12345\n", 6);
	testfile.append("54321\n", 6);
*/

	//LogFile test
/*	LogFile output("tttt");
	output.append("56789\n", 6);
	output.append("98765\n", 6);
*/

//SyncLogging  thread test

	//SyncLogging alog("2131", 12345);

//Log stdout test

	short it1=1;
	unsigned it2=2;
	int it3 =-3;
	long  it4 = 4;
	unsigned long long it5 = 5; 
	double dtest = 2.0/3;
	bool bt1 = false;
	bool bt2 = true;
	char *pt1 = NULL;
	char *pt2 = (char *)"abcdefg";
/*
	printf("(%d  %d %d)\n", Logger::TRACE, Logger::DEBUG, Logger::logLevel());
	Logger::setLogLevel(Logger::TRACE);
	printf("(%d  %d %d)\n", Logger::TRACE, Logger::DEBUG, Logger::logLevel());

	//for(int i = 0; i< 200 ; i++){
		LOG_DEBUG << "int test" << ' ' << it1 << it2 << it3 << it4 << it5;
		LOG_DEBUG << "double test"<< ' ' << 3.1415926 << ' ' << dtest;
		LOG_DEBUG << "bool test"<< ' ' << bt1 << ' '<< bt2;
		LOG_DEBUG << "ptr test"<< ' ' << pt1 << ' '<<pt2;
		LOG_DEBUG << "just test";
	//}

	LOG_INFO <<" just Test ";
	LOG_TRACE <<" just Test ";
	LOG_WARN <<" just Test ";
	LOG_DEBUG <<" just Test ";
	

	LOG_ERROR <<" just Test E";

	//abort()
	//LOG_FATAL <<" just Test F";

	errno = 11;	
	LOG_SYSERR << " just Test SE";

	//abort()
	//LOG_SYSFATAL << " just Test SF";
	LOG_DEBUG << "test to write in ./test.log";*/
	//SyncLogging Test
	SyncLogging log("./test.log", kRollSize);
	g_SyncLogging = &log;

	Logger::setOutput(SyncLoggingOutput);
	Logger::setFlush(SyncLoggingflush);

	prinTime();

	for(int j = 0 ; j < 1 ; ++j){
		for (int i = 1; i <= 100; ++i){
			LOG_WARN << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz ";
			LOG_DEBUG << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz ";
			LOG_TRACE << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz ";
			if(i == 90) 
				{
					LOG_FATAL << "FATAL~~~~~~~~~~~~~";
					//log.~SyncLogging();
					//abort();
				}
		}
	//printf("sleep 1\n");
	//sleep(1);
	}

	prinTime();

	getchar();

	return 0;
}