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
char *errmsg = NULL;
int key_num;

/*
*首先利用sqlite3_open打开一个数据库，mdatabase.db，如果不存在就创建它
*然后创建一个测试表
*然后再表里面插入一些记录
*最后查询这个表，并打印出来
*/
//数据库信息
    db_info db_column[11] = {
	{
	"int", "key_num"}, {
	"int", "ID"}, {
	"float", "particulate_matter_25"}, {
	"float", "particulate_matter_10"}, {
	"float", "temperature_value"}, {
	"float", "humidity_value"}, {
	"float", "wind_direction"}, {
	"float", "wind_speed_value"}, {
	"float", "noise_value"}, {
	"float", "atmospheric_pressure_value"}, {
"TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP", "CreatedTime"}};

int sql_insert_data(char *table_name, struct environment_data *air_data)
{
int result;
	char creattime[20];
char sql_command[300] = { "insert into " };
	sinydtimetostring(creattime, 0);
	strcat(sql_command, table_name);
	strcat(sql_command,
	       "(key_num,ID,particulate_matter_25,particulate_matter_10, \
         temperature_value,humidity_value,wind_direction,wind_speed_value,noise_value,atmospheric_pressure_value)");
	strcat(sql_command, " ");
	strcat(sql_command, "values(");
char *sql = NULL;
sql = (char *)malloc(200);
sql = (char *)air_data;
air_data->id = configInfo.address;
sprintf(sql, "%d,%d,%g,%g,%g,%g,%g,%g,%g,%g", key_num, air_data->id,
air_data->particulate_matter_25,
		 air_data->particulate_matter_10,air_data->temperature_value,
		 air_data->humidity_value,air_data->wind_direction,
		 air_data->wind_speed_value,air_data->noise_value,
		 air_data->atmospheric_pressure_value);
//  strcat(sql,",");
//  strcat(sql,creattime);
	strcat(sql_command, sql);
strcat(sql_command, ")");
#if DEBUG
	printf("%s", sql_command);
#endif /* */
	result = sqlite3_exec(db, sql_command, 0, 0, &errmsg);
if (result != SQLITE_OK) {
printf("Can't insert into datebase：%s\n", errmsg);
		return -1;
}

	else
 {
printf("insert into datebase ok\n");
		//  sql_query(db,1,1);
}

//  free(sql);
	    return 0;
}

extern struct msg_data modbus_data;

//查询数据库
int sqlquery_callback(void *para, int nCount, char **pValue, char **pName)
{

    /**********************************************************************
          sqlite 每查到一条记录，就调用一次这个回调
          para是你在 sqlite3_exec 里传入的 void * 参数, 通过para参数，你可以传入一些特殊的指针（比如类指  针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
          nCount是这一条(行)记录有多少个字段 (即这条记录有多少列)
          char ** pValue 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char* 值，是一个字段内容（用字符串来表示，以/0结尾）
          char ** pName 跟pValue是对应的，表示这个字段的字段名称, 也是个1维数组
     **************************************************************************/
	char *msg;

	  msg=(char *)malloc(400);
	  *msg='\0';
	int i;
	printf("nCount is %d \n", nCount);
for (i = 0; i < nCount; i++) {
printf("%s,", pValue[i]);
strcat(msg,pValue[i]);
strcat(msg,",");
}

	    free(msg);
	    return 0;
}

 //得到数据库总行数
u32 get_row_num(sqlite3 * ppDb)
{
	int result;

	char *errmsg = NULL;

	char **dbResult;	//是 char ** 类型，两个*号

	int nRow, nColumn;

	result =
	    sqlite3_get_table(ppDb, "select * from data;", &dbResult, &nRow,
			      &nColumn, &errmsg);

	if (SQLITE_OK == result) {
		//查询成功
		return nRow;
	}
	return nRow;
}

 //查询数据库
int sql_query(sqlite3 * ppDb, int start_row, int end_row)
{

	int result;
char sql_command[100] = { "select *from data limit " };
char *sql = NULL;
sql = (char *)malloc(100);
sprintf(sql, "%d,%d", start_row, end_row);
strcat(sql_command, sql);
printf("%s\n", sql_command);
result = sqlite3_exec(db, sql_command, sqlquery_callback, 0, &errmsg);
//     result = sqlite3_exec(db,"select *from environmental",sqlquery_callback,0,&errmsg);
	// sqlite3_close(db); //关闭数据库
	return result;
}

void next_row(void)
{
	configInfo.break_id++;
	printf("------break_id:%d-------\n", configInfo.break_id);
}


/*****************************************
创建数据库
****************************************/
int creat_db(char *db_path, char *db_name)
{
int result;
char creattime[100];
char db_all_name[100];
sinydtimetodirstring(creattime, 0);

	strcat(db_all_name, db_name);
strcat(db_all_name, creattime);
	strcat(db_all_name, ".db");

	chdir(db_path);
result = sqlite3_open(db_all_name, &db);	//打开数据库mdatabase.db，如果不存在就创建它
	if (result != SQLITE_OK)
 {
printf("Can't open datebase\n%s\n", sqlite3_errmsg(db));
return -1;
}
result = creat_table("data", db_column);
if(result==0)
   printf("creat table ok");
else
   printf("creat table fault");
return 0;
}


/*****************************************
创建数据表
****************************************/
int creat_table(char *table_name, db_info * column_info)
{
int result;
int k;

//      result = sqlite3_exec(db,"create table data(ID INTEGER PRIMARY KEY,wind_speed,rainfall,temperature,air_pressure,radiation,wind_diretion,humidity,test,test2,time TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP)",0,0, &errmsg);
char sql_command[400] = { "create table " };
strcat(sql_command, table_name);
	strcat(sql_command, "(");
for (k = 0; k < field_column_count; k++)
 {
		strcat(sql_command, column_info[k].column_name);
		strcat(sql_command, " ");
strcat(sql_command, column_info[k].data_type);
strcat(sql_command, ",");
}
	strcat(sql_command, column_info[field_column_count].column_name);
	strcat(sql_command, " ");
	strcat(sql_command, column_info[k].data_type);
strcat(sql_command, ")");

#if DEBUG
	    printf("%s\n", sql_command);

#endif /* */
	    result = sqlite3_exec(db, sql_command, 0, 0, &errmsg);

	    //创建一个测试表，表名My1table，有两个字段ID和name
	    if (result != SQLITE_OK)
 {
printf("warning:Create table fail! May table data already.\n");

             return -1;
		}		//  test();
//      sqlite3_close(db); //关闭数据库
	return 0;
}

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
printf("Can't open datebase\n%s\n", sqlite3_errmsg(db));
return -1;
}
all_row = get_row_num(break_db);
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


