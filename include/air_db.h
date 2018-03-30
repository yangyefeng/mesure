#ifndef _AIR_DB_H_
#define _AIR_DB_H_
#include "air_modbus.h"
#include "config.h"

#define field_column_count 10
typedef struct DB_info
{
 char * data_type;
 char * column_name;
}db_info;
extern db_info db_column[];

int creat_db(char *db_path,char *db_name);
int creat_table(char *table_name, db_info * column_info);
int sql_insert_data(char *table_name,struct environment_data *air_data);
int sql_query(sqlite3 *ppDb,int start_row,int end_row);
int sqlquery_callback(void*para , int nCount, char** pValue, char** pName);
u8 db_open(char *db_name,u32 id);
#endif
