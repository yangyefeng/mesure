#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "emsascommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
数据库路径和名称
**/
#define DB_PATH "/mnt/database/"
#define DB_NAME "air_data_"
#define TCP_RECONNNECT_TIMER  60
// 配置参数结构体定义
typedef struct
{
    char  server_ip_address[128];    // 服务器IP地址
    u32  address;                        //设备编号
    u32 server_ip_port;            //服务器端口
    u32  time;                  // 读取数据间隔时间
    u32  factory_num;               //设备厂家编号
    char  data_file_name[128];    // 断点数据库名称
    u32   break_id;
} T_ConfigInfo;

extern T_ConfigInfo configInfo;



//
u32 para_init(void);
//void GetCompletePath(char *pszConfigFileName,  char *pszWholePath);
//void GetStringContentValue(FILE *fp, char *pszSectionName, char *pszKeyName, char *pszOutput, u32 iOutputLen);
void GetConfigFileStringValue(char *pszSectionName, char* pszKeyName, char *pDefaultVal, char *pszOutput, u32 iOutputLen, char *pszConfigFileName);
s32 GetConfigFileIntValue(char *pszSectionName, char *pszKeyName, u32 iDefaultVal, char *pszConfigFileName);
char WriteProfileString(char lpAppName[], char lpKeyName[], char lpString[], char lpFileName[]);
#endif
