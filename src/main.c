#include "config.h"
#include"air_modbus.h"
#include "run4g.h"
#include "air_db.h"
#include "log.h"

#define DEBUG 0

 int main(void) 
{
	int res;
	init_zlog();
	res = para_init();
	res = creat_db(DB_PATH, DB_NAME);
	if (res == 0)
		zlog_info(c, "creat db ok");
	modbus_init();
	run4g_init();
//主循环

	trans_handle();
	while (1)
		 {
		
//  res=read_slave_address();
//modbus_read_registers(mb, 8, 2, tab_reg);
//  res=read_air_environment(&var_environment_data);
//  usleep(modbus485_sync_time);
		}
	
//  res=read_reg();
	    
//  modbus_close(mb);
//  modbus_free(mb);
//  sqlite3_close(db); //¹Ø±ÕÊý¾Ý¿â
	    return 0;
}


