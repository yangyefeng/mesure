#include "sinyd_time.h"
#include <stdio.h>
void sinyd_reset()
{
	m_time.tv_sec = 0;
	m_time.tv_usec = 0;
}  bool sinyd_iszero()
{
	return (m_time.tv_sec == 0) && (m_time.tv_usec == 0);
}

void sinyd_now()
{
	gettimeofday(&m_time, NULL);
 } s32 get_year(void)
{
	struct tm *p = localtime(&m_time.tv_sec);
	return p->tm_year + 1900;
}

s32 get_month(void)
{
	struct tm *p = localtime(&m_time.tv_sec);
	return p->tm_mon + 1;
}

s32 get_day()
{
	struct tm *p = localtime(&(m_time.tv_sec));
	return p->tm_mday;
}

s32 get_hour()
{
	struct tm *p = localtime(&(m_time.tv_sec));
	return p->tm_hour;
}

 s32 get_min()
{
	struct tm *p = localtime(&(m_time.tv_sec));
	return p->tm_min;
}

 s32 get_second()
{
	struct tm *p = localtime(&(m_time.tv_sec));
	return p->tm_sec;
}

 s32 get_millisecond()
{
	return (int)(m_time.tv_usec / 1000);
}  s64 get_totalseconds()
{
	return m_time.tv_sec;
}

 void sinydtimetostring(char *szBuf, bool bIncludeMilliSeconds)
{
	struct tm *p = localtime(&(m_time.tv_sec));
	 if (bIncludeMilliSeconds) {
		sprintf(szBuf, "%d-%02d-%02d-%02d:%02d:%02d.%03d",
			 p->tm_year + 1900, p->tm_mon + 1, p->tm_mday,
			 \p->tm_hour, p->tm_min, p->tm_sec,
			 (int)(m_time.tv_usec / 1000));
	} else {
		sprintf(szBuf, "%d-%02d-%02d-%02d-%02d-%02d",
			 p->tm_year + 1900, p->tm_mon + 1, p->tm_mday,
			 \p->tm_hour, p->tm_min, p->tm_sec);
	}
}

 void sinydtimetodirstring(char *szBuf, bool bIncludeMilliSeconds)
{
	
	    // char szBuf[100];
	    time(&(m_time.tv_sec));
	struct tm *p = localtime(&(m_time.tv_sec));
	 if (bIncludeMilliSeconds) {
		sprintf(szBuf, "%d-%02d-%02d_%02d_%02d_%02d_%03d",
			 p->tm_year + 1900, p->tm_mon + 1, p->tm_mday,
			 p->tm_hour, p->tm_min, p->tm_sec,
			 (int)(m_time.tv_usec / 1000));
	} else {
		sprintf(szBuf, "%d-%02d-%02d_%02d_%02d_%02d",
			 p->tm_year + 1900, p->tm_mon + 1, p->tm_mday,
			 p->tm_hour, p->tm_min, p->tm_sec);
	}
	
	    //  return szBuf;
}

   
