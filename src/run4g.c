
#include "run4g.h"

#define RECV  0
#define SEND  1

//extern T_ConfigInfo configInfo;
extern sqlite3 *db;






//char msg[1024]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
char heat_mes[15] = { 0 };



{


//  msg=(char *)malloc(sizeof(modbus_data));
	    time_t now;





	tcp_data.rainfall = air_data->particulate_matter_10;






		 tcp_data.wind_speed, tcp_data.rainfall, tcp_data.temperature,
		 tcp_data.air_pressure, tcp_data.radiation,
		 tcp_data.wind_diretion, tcp_data.humidity,
		 tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
		 tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);




{
	int res;
	while (1) {
		res = read_air_environment(&var_environment_data);
		if (res)
			printf("read data ok\n");
		sql_insert_data("data", &var_environment_data);
		printf("%d\n", key_num++);
		if (key_num == 65535) {
			key_num = 0;
			res = creat_db(DB_PATH, DB_NAME);
		}

		sleep(1);

	}

}
// Time callback function
void onTime(int sock, short event, void *arg)
{

	    //
	    get_open_database("/mnt/database");





	{













{

			       configInfo.server_ip_port);
	get_breakpoint();






	return 0;
}


{
	//struct event_base 事件集合
struct event_base *base = event_init();


	    event_new(base, sockfd,
		      NULL);


	    event_new(base, sockfd,


	    //   struct event* ev_cmd = event_new(base, timeevent,
	    //                                    EV_READ | EV_PERSIST, on_write,
	    //                                    (void*)&sockfd);







	err = pthread_create(&tid, NULL, ad_task, NULL);
	if (err != 0) {
		perror(" fail to create thread ");
		return -1;
	}






{




{

	    //   int ret = read(fd, msg, sizeof(msg));
	    //   if( ret <= 0 )
	    //   {
	    //       perror("read fail ");
	    //       exit(1);
	    //   }

//    int sockfd = *((int*)arg);

	    //æç»ç«¯çæ¶æ¯åéç»æå¡å¨ç«¯
	    //ä¸ºäºç®åèµ·è§ï¼ä¸èèåä¸åæ°æ®çæåµ
	    //   write(sockfd, msg, ret);
}
{



	    //ä¸ºäºç®åèµ·è§ï¼ä¸èèè¯»ä¸åæ°æ®çæåµ
	int len = read(fd, msg, sizeof(msg) - 1);



		restore_breakpoint();
		while (1) {
			res = run4g_init();
			sleep(TCP_RECONNNECT_TIMER);
			if (res == 0) {
				get_breakpoint();
				trans_handle();
				break;
			}

		}

		    //  exit(1);
		}


	    //  temp=strcmp(msg,"ok");
	    //  printf("temp %d \n", temp);





		    //    printf("recv %s from server\n", send_flag);
		}




{







	{







	    connect(sockfd, (SA *) & server_addr, sizeof(server_addr));





		return -1;





