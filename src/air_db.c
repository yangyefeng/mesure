#include <stdio.h>
#include <sqlite3.h>
#include <malloc.h>
#include <sinyd_time.h>
#include "air_db.h"
#include <stdlib.h>
#include "dirent.h"
#include <unistd.h>
#define DEBUG 0
sqlite3 *db;

int key_num;

/*
*��������sqlite3_open��һ�����ݿ⣬mdatabase.db����������ھʹ�����
*Ȼ�󴴽�һ�����Ա�
*Ȼ���ٱ��������һЩ��¼
*����ѯ�����������ӡ����
*/
//���ݿ���Ϣ
    db_info db_column[11] = {
	{
	"int", "key_num"},
	"int", "ID"}, {
	"float", "particulate_matter_25"},
	"float", "particulate_matter_10"},
	"float", "temperature_value"},
	"float", "humidity_value"},
	"float", "wind_direction"},
	"float", "wind_speed_value"},
	"float", "noise_value"},
	"float", "atmospheric_pressure_value"},
"TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP", "CreatedTime"}


{

	char creattime[20];

	sinydtimetostring(creattime, 0);
	strcat(sql_command, table_name);
	strcat(sql_command,
	       "(key_num,ID,particulate_matter_25,particulate_matter_10, \
         temperature_value,humidity_value,wind_direction,wind_speed_value,noise_value,atmospheric_pressure_value)");
	strcat(sql_command, " ");
	strcat(sql_command, "values(");






		 air_data->particulate_matter_10,
		 air_data->humidity_value,
		 air_data->wind_speed_value,
		 air_data->atmospheric_pressure_value);
//  strcat(sql,",");
//  strcat(sql,creattime);
	strcat(sql_command, sql);

#if DEBUG
	printf("%s", sql_command);
#endif /*
	result = sqlite3_exec(db, sql_command, 0, 0, &errmsg);


		return -1;


	else


		//  sql_query(db,1,1);


//  free(sql);
	    return 0;




//��ѯ���ݿ�
int sqlquery_callback(void *para, int nCount, char **pValue, char **pName)
{

    /**********************************************************************
          sqlite ÿ�鵽һ����¼���͵���һ������ص�
          para������ sqlite3_exec �ﴫ��� void * ����, ͨ��para����������Դ���һЩ�����ָ�루������ָ  �롢�ṹָ�룩��Ȼ����������ǿ��ת���ɶ�Ӧ�����ͣ���������void*���ͣ�����ǿ��ת����������Ͳſ��ã���Ȼ�������Щ����
          nCount����һ��(��)��¼�ж��ٸ��ֶ� (��������¼�ж�����)
          char ** pValue �Ǹ��ؼ�ֵ������������ݶ������������ʵ�����Ǹ�1ά���飨��Ҫ��Ϊ��2ά���飩��ÿһ��Ԫ�ض���һ�� char* ֵ����һ���ֶ����ݣ����ַ�������ʾ����/0��β��
          char ** pName ��pValue�Ƕ�Ӧ�ģ���ʾ����ֶε��ֶ�����, Ҳ�Ǹ�1ά����
     **************************************************************************/
	char *msg;

	  msg=(char *)malloc(400);
	  *msg='\0';
	int i;
	printf("nCount is %d \n", nCount);


strcat(msg,pValue[i]);
strcat(msg,",");


	    free(msg);
	    return 0;


 //�õ����ݿ�������
u32 get_row_num(sqlite3 * ppDb)
{
	int result;

	char *errmsg = NULL;

	char **dbResult;	//�� char ** ���ͣ�����*��

	int nRow, nColumn;

	result =
	    sqlite3_get_table(ppDb, "select * from data;", &dbResult, &nRow,
			      &nColumn, &errmsg);

	if (SQLITE_OK == result) {
		//��ѯ�ɹ�
		return nRow;
	}
	return nRow;
}

 //��ѯ���ݿ�
int sql_query(sqlite3 * ppDb, int start_row, int end_row)
{

	int result;







//     result = sqlite3_exec(db,"select *from environmental",sqlquery_callback,0,&errmsg);
	// sqlite3_close(db); //�ر����ݿ�
	return result;


void next_row(void)
{
	configInfo.break_id++;
	printf("------break_id:%d-------\n", configInfo.break_id);
}


/*****************************************
�������ݿ�
****************************************/
int creat_db(char *db_path, char *db_name)
{





	strcat(db_all_name, db_name);

	strcat(db_all_name, ".db");

	chdir(db_path);

	if (result != SQLITE_OK)





if(result==0)
   printf("creat table ok");
else
   printf("creat table fault");




/*****************************************
�������ݱ�
****************************************/
int creat_table(char *table_name, db_info * column_info)
{



//      result = sqlite3_exec(db,"create table data(ID INTEGER PRIMARY KEY,wind_speed,rainfall,temperature,air_pressure,radiation,wind_diretion,humidity,test,test2,time TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP)",0,0, &errmsg);


	strcat(sql_command, "(");


		strcat(sql_command, column_info[k].column_name);
		strcat(sql_command, " ");



	strcat(sql_command, column_info[field_column_count].column_name);
	strcat(sql_command, " ");
	strcat(sql_command, column_info[k].data_type);


#if DEBUG
	    printf("%s\n", sql_command);

#endif /*
	    result = sqlite3_exec(db, sql_command, 0, 0, &errmsg);

	    //����һ�����Ա�������My1table���������ֶ�ID��name
	    if (result != SQLITE_OK)



             return -1;
		}		//  test();
//      sqlite3_close(db); //�ر����ݿ�
	return 0;


//
u8 get_database_state(char *basePath)
{
	DIR *dir;
	int state;
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
		} else if (strcmp(ptr->d_name, configInfo.data_file_name) > 0) {
			state = 1;

			break;
		} else {
			state = 0;
		}

	}
	return state;
}

u8 end_of(u32 row)
{
	if (row <= configInfo.break_id) {
		return 0;
	} else {
		return 1;
	}
}

u8 db_open(char *db_name, u32 id)
{
	sqlite3 *break_db;

	int result;
	int state;
	u32 all_row;

	chdir("/mnt/database/");
	result = sqlite3_open(db_name, &break_db);
	if (result != SQLITE_OK) {




	printf("-----%d--------------\n", all_row);
	configInfo.break_id = id;
	while (all_row != 0 && end_of(all_row)) {

		sql_query(break_db, configInfo.break_id, 1);
		next_row();
		sleep(1);
	}

	state = get_database_state("/mnt/database/");
	if (state) {
		printf("-----%s--------------\n\n", db_name);
		sqlite3_close(break_db);
		unlink(db_name);
	}

	return 0;
}

