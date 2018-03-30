#include "config.h"
#include "dirent.h"
#include "air_db.h"

void get_open_database(char *basePath)
{
	DIR *dir;
	struct dirent *ptr;


	if ((dir = opendir(basePath)) == NULL) {
		perror("Open dir error...");
		exit(1);
	}
	while ((ptr = readdir(dir)) != NULL) {
		if (strcmp(ptr->d_name, ".") == 0
		    || strcmp(ptr->d_name, "..") == 0) {
			///current dir OR parrent dir
			continue;
		} else if (strcmp(ptr->d_name, configInfo.data_file_name) == 0) {
			db_open(configInfo.data_file_name, configInfo.break_id);
		} else if (strcmp(ptr->d_name, configInfo.data_file_name) > 0) {
			strcpy(configInfo.data_file_name, ptr->d_name);
			//   sprintf(test_db_name,"%s",configInfo.data_file_name);
			//   printf("============%s============\n",test_db_name);
			db_open(configInfo.data_file_name, 1);
			printf("****************%s***************\n",
			       configInfo.data_file_name);

		}
		break;
	}
}

void get_breakpoint(void)
{

	GetConfigFileStringValue("EMPLOYEEINFO", "data_file_name", "",
				 configInfo.data_file_name,
				 sizeof(configInfo.data_file_name),
				 "Config.ini");
	configInfo.break_id =
	    GetConfigFileIntValue("EMPLOYEEINFO", "dataID", 4, "Config.ini");
	//   printf("data_file_name is %s,dataID is %d \n",configInfo.data_file_name,configInfo.break_id);

	//判断打开哪个数据库文件
	//      get_open_database("/mnt/database");
}

void init_breakpoint(char *name, int id)
{
	strcpy(configInfo.data_file_name, name);
	configInfo.break_id = id;
}

void restore_breakpoint(void)
{
	char id[10];
	sprintf(id, "%d", configInfo.break_id);
	WriteProfileString("EMPLOYEEINFO", "data_file_name",
			   configInfo.data_file_name, "/opt/Config.ini");
	WriteProfileString("EMPLOYEEINFO", "dataID", id, "/opt/Config.ini");
}
