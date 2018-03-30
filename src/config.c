/**********************************************************************
* 版权所有 (C)2017, yangyefeng。
*
* 文件名称：GetConfig.c
* 文件标识：无
* 内容摘要：Linux下配置文件的读取方法
* 其它说明：无
* 当前版本：V1.0
* 作    者：yangyefgeng
* 完成日期：20171117
*
**********************************************************************/

#include "config.h"

#define LINESIZE 128
#define MODE_DELETE_SECTION 1
#define MODE_DELETE_KEY     2
#define MODE_OVERWRITE_KEY  3
#define MODE_APPEND_SECTION 4
#define MODE_APPEND_KEY		5
T_ConfigInfo configInfo = {
"0"};


/**********************************************************************
* 功能描述： 获取配置文件完整路径(包含文件名)
* 输入参数： pszConfigFileName-配置文件名
             pszWholePath-配置文件完整路径(包含文件名)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期        版本号         修改人       修改内容
* ------------------------------------------------------------------
* 20150507       V1.0     Zhou Zhaoxiong     创建
********************************************************************/
void GetCompletePath(char *pszConfigFileName, char *pszWholePath)
{
	char *pszHomePath = NULL;
	char szWholePath[256] = { 0 };

	// 先对输入参数进行异常判断
	if (pszConfigFileName == NULL || pszWholePath == NULL) {
		printf("GetCompletePath: input parameter(s) is NULL!\n");
		return;
	}

	pszHomePath = (char *)getenv("HOME");	// 获取当前用户所在的路径
	if (pszHomePath == NULL) {
		printf("GetCompletePath: Can't find home path!\n");
		return;
	}
	// 拼装配置文件路径
	snprintf(szWholePath, sizeof(szWholePath) - 1, "/opt/%s",
		 pszConfigFileName);

	strncpy(pszWholePath, szWholePath, strlen(szWholePath));
}

/**********************************************************************
* 功能描述： 获取具体的字符串值
* 输入参数： fp-配置文件指针
             pszSectionName-段名, 如: GENERAL
             pszKeyName-配置项名, 如: EmployeeName
             iOutputLen-输出缓存长度
* 输出参数： pszOutput-输出缓存
* 返 回 值： 无
* 其它说明： 无
* 修改日期         版本号        修改人       修改内容
* ------------------------------------------------------------------
* 20150507       V1.0     Zhou Zhaoxiong     创建
********************************************************************/
void GetStringContentValue(FILE * fp, char *pszSectionName, char *pszKeyName,
			   char *pszOutput, u32 iOutputLen)
{
	char szSectionName[100] = { 0 };
	char szKeyName[100] = { 0 };
	char szContentLine[256] = { 0 };
	char szContentLineBak[256] = { 0 };
	u32 iContentLineLen = 0;
	u32 iPositionFlag = 0;

	// 先对输入参数进行异常判断
	if (fp == NULL || pszSectionName == NULL || pszKeyName == NULL
	    || pszOutput == NULL) {
		printf("GetStringContentValue: input parameter(s) is NULL!\n");
		return;
	}

	sprintf(szSectionName, "[%s]", pszSectionName);
	strcpy(szKeyName, pszKeyName);

	while (feof(fp) == 0) {
		memset(szContentLine, 0x00, sizeof(szContentLine));
		fgets(szContentLine, sizeof(szContentLine), fp);	// 获取段名

		// 判断是否是注释行(以;开头的行就是注释行)或以其他特殊字符开头的行
		if (szContentLine[0] == ';' || szContentLine[0] == '\r'
		    || szContentLine[0] == '\n' || szContentLine[0] == '\0') {
			continue;
		}
		// 匹配段名
		if (strncasecmp
		    (szSectionName, szContentLine,
		     strlen(szSectionName)) == 0) {
			while (feof(fp) == 0) {
				memset(szContentLine, 0x00,
				       sizeof(szContentLine));
				memset(szContentLineBak, 0x00,
				       sizeof(szContentLineBak));
				fgets(szContentLine, sizeof(szContentLine), fp);	// 获取字段值

				// 判断是否是注释行(以;开头的行就是注释行)
				if (szContentLine[0] == ';') {
					continue;
				}

				memcpy(szContentLineBak, szContentLine,
				       strlen(szContentLine));

				// 匹配配置项名
				if (strncasecmp
				    (szKeyName, szContentLineBak,
				     strlen(szKeyName)) == 0) {
					iContentLineLen = strlen(szContentLine);
					for (iPositionFlag = strlen(szKeyName);
					     iPositionFlag <= iContentLineLen;
					     iPositionFlag++) {
						if (szContentLine[iPositionFlag]
						    == ' ') {
							continue;
						}
						if (szContentLine[iPositionFlag]
						    == '=') {
							break;
						}

						iPositionFlag =
						    iContentLineLen + 1;
						break;
					}

					iPositionFlag = iPositionFlag + 1;	// 跳过=的位置

					if (iPositionFlag > iContentLineLen) {
						continue;
					}

					memset(szContentLine, 0x00,
					       sizeof(szContentLine));
					strcpy(szContentLine,
					       szContentLineBak +
					       iPositionFlag);

					// 去掉内容中的无关字符
					for (iPositionFlag = 0;
					     iPositionFlag <
					     strlen(szContentLine);
					     iPositionFlag++) {
						if (szContentLine[iPositionFlag]
						    == '\r'
						    ||
						    szContentLine[iPositionFlag]
						    == '\n'
						    ||
						    szContentLine[iPositionFlag]
						    == '\0') {
							szContentLine
							    [iPositionFlag] =
							    '\0';
							break;
						}
					}

					// 将配置项内容拷贝到输出缓存中
					strncpy(pszOutput, szContentLine,
						iOutputLen - 1);
					break;
				} else if (szContentLine[0] == '[') {
					break;
				}
			}
			break;
		}
	}
}

/**********************************************************************
* 功能描述： 从配置文件中获取字符串
* 输入参数： pszSectionName-段名, 如: GENERAL
             pszKeyName-配置项名, 如: EmployeeName
             pDefaultVal-默认值
             iOutputLen-输出缓存长度
             pszConfigFileName-配置文件名
* 输出参数： pszOutput-输出缓存
* 返 回 值： 无
* 其它说明： 无
* 修改日期        版本号         修改人       修改内容
* ------------------------------------------------------------------
* 20150507       V1.0     Zhou Zhaoxiong     创建
********************************************************************/
void GetConfigFileStringValue(char *pszSectionName, char *pszKeyName,
			      char *pDefaultVal, char *pszOutput,
			      u32 iOutputLen, char *pszConfigFileName)
{
	FILE *fp = NULL;
	char szWholePath[256] = { 0 };

	// 先对输入参数进行异常判断
	if (pszSectionName == NULL || pszKeyName == NULL || pszOutput == NULL
	    || pszConfigFileName == NULL) {
		printf
		    ("GetConfigFileStringValue: input parameter(s) is NULL!\n");
		return;
	}
	// 获取默认值
	if (pDefaultVal == NULL) {
		strcpy(pszOutput, "");
	} else {
		strcpy(pszOutput, pDefaultVal);
	}

	// 打开配置文件
	GetCompletePath(pszConfigFileName, szWholePath);
	fp = fopen(szWholePath, "r");
	if (fp == NULL) {
		printf("GetConfigFileStringValue: open %s failed!\n",
		       szWholePath);
		return;
	}
	// 调用函数用于获取具体配置项的值
	GetStringContentValue(fp, pszSectionName, pszKeyName, pszOutput,
			      iOutputLen);

	// 关闭文件
	fclose(fp);
	fp = NULL;
}

/**********************************************************************
* 功能描述： 从配置文件中获取整型变量
* 输入参数： pszSectionName-段名, 如: GENERAL
             pszKeyName-配置项名, 如: EmployeeName
             iDefaultVal-默认值
             pszConfigFileName-配置文件名
* 输出参数： 无
* 返 回 值： iGetValue-获取到的整数值   -1-获取失败
* 其它说明： 无
* 修改日期         版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150507       V1.0     Zhou Zhaoxiong     创建
********************************************************************/
s32 GetConfigFileIntValue(char *pszSectionName, char *pszKeyName,
			  u32 iDefaultVal, char *pszConfigFileName)
{
	char szGetValue[512] = { 0 };
	s32 iGetValue = 0;

	// 先对输入参数进行异常判断
	if (pszSectionName == NULL || pszKeyName == NULL
	    || pszConfigFileName == NULL) {
		printf("GetConfigFileIntValue: input parameter(s) is NULL!\n");
		return -1;
	}

	GetConfigFileStringValue(pszSectionName, pszKeyName, NULL, szGetValue, 512 - 1, pszConfigFileName);	// 先将获取的值存放在字符型缓存中

	if (szGetValue[0] == '\0' || szGetValue[0] == ';')	// 如果是结束符或分号, 则使用默认值
	{
		iGetValue = iDefaultVal;
	} else {
		iGetValue = atoi(szGetValue);
	}

	return iGetValue;
}

char WriteProfileString(char lpAppName[], char lpKeyName[], char lpString[],
			 char lpFileName[])
{
	FILE *stream;
	char *pVoid = NULL;	//文件的后半部分
	char bFindKey = false;
	char bFindSection = false;
	char line[LINESIZE];
	size_t sectionLength, keyLength, lineLength, nBytesRead = 0;
	long nInsertPos = -1, nCopyPos = -1, nFileEndPos, nPos;	//文件指针位置
	long nSectionBegin = -1, nKeyBegin = -1, nNextKey = -1, nNextSection =
	    -1;
	int mode = 0;
	//如果 sectionName 为NULL，返回成功
	if (lpAppName == NULL)
		return true;
	//r+: Opens for both reading and writing. (The file must exist.)
	stream = fopen(lpFileName, "r+");
	if (stream == NULL) {
		printf("stream is null");
		return false;
	}
	//先取一次mode的默认值
	if (lpKeyName == NULL)
		mode = MODE_DELETE_SECTION;
	else if (lpString == NULL)
		mode = MODE_DELETE_KEY;
	else
		mode = MODE_OVERWRITE_KEY;
	sectionLength = strlen(lpAppName);
	//每次读行前，保存文件指针位置
	while (nPos = ftell(stream), fgets(line, LINESIZE, stream) != NULL) {
		//忽略注释行和空行
		if (line[0] == 0 || line[0] == ';')
			continue;
		lineLength = strlen(line);
		//注意：把LF(0xa)字符替换成0，这在UNICODE环境下可能出现结尾是LF)
		if (line[lineLength - 1] == 0x0a) {
			line[lineLength - 1] = 0;
			lineLength--;
			//注意此时可能会成为空字符串
			if (lineLength == 0)
				continue;
		}
		//尝试寻找到 section
		if (!bFindSection) {
			if (line[0] != '[')
				continue;	//本行是否是 [section]
			//这里是我们想要的Section吗?
			//检查这一行的宽度是否正好是section长度加2， [lpAppName]
			if (line[sectionLength + 1] != ']')
				continue;
			if (strncmp(line + 1, lpAppName, sectionLength) != 0)
				continue;
			//Now Section will appear on next line
			//读取section前求出 Key 的长度
			if (lpKeyName != NULL)
				keyLength = strlen(lpKeyName);
			nSectionBegin = nPos;
			bFindSection = true;
			continue;
		}
		//Section找到了，
		//Section End ?
		if (line[0] == '[') {
			nNextSection = nPos;
			break;	//遇到了下一个
		}
		//是否需要查找KEY?
		if (lpKeyName != NULL) {
			if (lineLength < keyLength + 1
			    || line[keyLength] != '=')
				continue;	//"KeyName="
			if (strncmp(line, lpKeyName, keyLength) != 0)
				continue;
			//Now We Get the Key!
			nKeyBegin = nPos;
			nNextKey = ftell(stream);	//要拷贝的起始位置
			//Now It's done.
			bFindKey = true;
			break;
		}
	}
	//如果已经到达文件尾部，则追加换行
	//      if(feof(stream))
	//              _ftprintf(stream, _T("\n"));
	if (nNextSection < 0)
		nNextSection = ftell(stream);
	if (nNextKey < 0)
		nNextKey = ftell(stream);
	//遍历后再次更新mode值
	if (mode == MODE_DELETE_SECTION) {
		if (!bFindSection) {
			fclose(stream);
			return true;
		} else {
			nInsertPos = nSectionBegin;
			nCopyPos = nNextSection;
		}
	}
	if (mode == MODE_DELETE_KEY) {
		if (!bFindKey) {
			fclose(stream);
			return true;
		} else {
			nInsertPos = nKeyBegin;
			nCopyPos = nNextKey;
		}
	}
	if (mode == MODE_OVERWRITE_KEY) {
		if (!bFindSection) {
			mode = MODE_APPEND_SECTION;
		} else {
			if (bFindKey) {
				nInsertPos = nKeyBegin;
				nCopyPos = nNextKey;
			} else {
				mode = MODE_APPEND_KEY;
				nInsertPos = nNextSection;
				nCopyPos = nNextSection;
			}
		}
	}
	//追加一个新的Section
	if (mode == MODE_APPEND_SECTION) {
		fprintf(stream, "\n[%s]\n%s=%s\n", lpAppName, lpKeyName,
			lpString);
		fclose(stream);
		return true;
	}
	//先把文件的后半部分拷贝到内存
	fseek(stream, 0, SEEK_END);
	nFileEndPos = ftell(stream);
	if (nCopyPos >= 0 && nCopyPos < nFileEndPos) {
		//分配内存作为缓冲区
		pVoid = malloc(nFileEndPos - nCopyPos + 1);
		if (pVoid == NULL) {
			fclose(stream);
			printf("memory is not enough");
			return false;	//堆内存不足
		}
		fseek(stream, nCopyPos, SEEK_SET);
		nBytesRead =
		    fread(pVoid, 1, nFileEndPos - nCopyPos + 1, stream);
	}
	//写入新的value值
	fseek(stream, nInsertPos, SEEK_SET);
	if (lpKeyName != NULL && lpString != NULL)
		fprintf(stream, "%s=%s\n", lpKeyName, lpString);
	//现在把文件的后半部分写回文件中
	if (pVoid != NULL && nBytesRead > 0) {
		fwrite(pVoid, 1, nBytesRead, stream);
		free(pVoid);
	}
	//此时结尾可能还有一些内容，属于原来的ini文件
	//我们把它写成注释
	nPos = ftell(stream);
	fclose(stream);
	//如果文件变小了，那么我们需要更改文件大小
	return true;
}

/**********************************************************************
* 功能描述: 获取配置参数
* 输入参数：无
* 输出参数：-1 没成功  0成功
* 返 回 值：无
* 其它说明：无
* 修改日期         版本号         修改人            修改内容
* ---------------------------------------------------------------
* 20171117        V1.0     杨叶峰         创建
***********************************************************************/
u32 para_init(void)
{

	    // 获取配置信息
	    // 获取服务器IP
	    GetConfigFileStringValue("EMPLOYEEINFO", "server_ip_addr", "",
				     configInfo.server_ip_address,
				     sizeof(configInfo.server_ip_address),
				     "Config.ini");
        configInfo.server_ip_port =
	    GetConfigFileIntValue("EMPLOYEEINFO", "server_ip_port", 4,
				  "Config.ini");

	    //获取设备厂家´
	    configInfo.factory_num =
	    GetConfigFileIntValue("EMPLOYEEINFO", "factory", 4, "Config.ini");
	//获取设备编号
	configInfo.address =
	    GetConfigFileIntValue("EMPLOYEEINFO", "id", 4, "Config.ini");

	    // 获取读取间隔时间
	    configInfo.time =
	    GetConfigFileIntValue("EMPLOYEEINFO", "time", 4, "Config.ini");
if (configInfo.time == -1)	//
	{
printf("Get server_ip_addr failed!\n");
return -1;
}

#if DEBUG
	    printf
	    ("server_ip_addr is %s\n,server_ip_port is %d\n,time is %d\n,factory_num is %d\n,id is %d\n",
	     configInfo.server_ip_address, configInfo.server_ip_port,
	     configInfo.time, configInfo.factory_num, configInfo.id);

#endif /* */
	    return 0;
}


