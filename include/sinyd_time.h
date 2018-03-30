/////////////////////////////////////////////////////////////////////////////
/// @File name: syd_time.h
/// @Author: h
/// @Copyright Shenyang new generation of information technology Co., Ltd.
/// @Version: 1.0
/// @Date: 2017/09/08
/// @Description:
/// 	Time Manage Class
/// @History:
/// 	version: author, date, desc\n 
/////////////////////////////////////////////////////////////////////////////
#ifndef SYD_TIME_H
#define SYD_TIME_H
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "emsascommon.h"
struct timeval m_time;
time_t timep;
s32 get_year(void);
s32 get_month(void);
s32 get_day();
s32 get_hour();
s32 get_min();
s32 get_second();
s32 get_millisecond();
void sinydtimetostring(char *szBuf, bool bIncludeMilliSeconds);
void sinydtimetodirstring(char *szBuf, bool bIncludeMilliSeconds);
#endif