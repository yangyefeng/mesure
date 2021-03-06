
#include "run4g.h"

#define RECV  0
#define SEND  1

//extern T_ConfigInfo configInfo;
extern sqlite3 *db;
extern struct environment_data var_environment_data;
extern int key_num;
char tcp_flag = SEND;
int sockfd;
struct timeval tv;

//char msg[1024]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
char heat_mes[15] = { 0 };

struct msg_data tcp_data;
void init_send_package(struct environment_data *air_data)
{
char msg[200];

//  msg=(char *)malloc(sizeof(modbus_data));
	    time_t now;
struct tm *tm_now;
time(&now);
tm_now = localtime(&now);
tcp_data.id = 1;
tcp_data.wind_speed = air_data->particulate_matter_25;	//·
	tcp_data.rainfall = air_data->particulate_matter_10;
tcp_data.temperature = air_data->temperature_value;
tcp_data.air_pressure = air_data->atmospheric_pressure_value;
tcp_data.radiation = air_data->humidity_value;
tcp_data.wind_diretion = air_data->temperature_value;
tcp_data.humidity = air_data->wind_direction;
sprintf(msg, "%d,%g,%g,%g,%g,%g,%g,%g,%d,%d,%d,%d,%d,%d", tcp_data.id,
		 tcp_data.wind_speed, tcp_data.rainfall, tcp_data.temperature,
		 tcp_data.air_pressure, tcp_data.radiation,
		 tcp_data.wind_diretion, tcp_data.humidity,
		 tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
		 tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
write(sockfd, msg, sizeof(msg));
}

void ad_task(void)
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
struct timeval tv;
tv.tv_sec = configInfo.time;
tv.tv_usec = 0;
evtimer_add(*((struct event **)arg), &tv);
if (1)			//(key_num%2)==0)
	{
sprintf(heat_mes, "ID %d %s", tcp_data.id, "is on line");
write(sockfd, heat_mes, sizeof(heat_mes));
if (key_num % 10 == 0)
 {
if (tcp_flag == SEND)
 {
init_send_package(&var_environment_data);
tcp_flag = RECV;
}
}
}
}
int run4g_init(void)
{
    sockfd =tcp_connect_server(configInfo.server_ip_address,
			       configInfo.server_ip_port);
	get_breakpoint();
if (sockfd == -1)
 {
perror("tcp_connect error ");
return -1;
}
printf("connect to server successful\n");
	return 0;
}

int trans_handle(void)
{
	//struct event_base 事件集合
struct event_base *base = event_init();
struct event *timer_ev = NULL;
struct event *ev_sockfd =
	    event_new(base, sockfd,EV_READ | EV_PERSIST,socket_read_cb,
		      NULL);
event_add(ev_sockfd, NULL);
struct event *ev_cmd =
	    event_new(base, sockfd,EV_READ | EV_PERSIST, cmd_msg_cb,
(void *)&sockfd);

	    //   struct event* ev_cmd = event_new(base, timeevent,
	    //                                    EV_READ | EV_PERSIST, on_write,
	    //                                    (void*)&sockfd);
timer_ev = evtimer_new(base, onTime, (void *)&timer_ev);
memset(&tv, 0, sizeof(tv));
tv.tv_sec = 1;
evtimer_add(timer_ev, &tv);
event_add(ev_cmd, NULL);
pthread_t tid;
int err;
	err = pthread_create(&tid, NULL, ad_task, NULL);
	if (err != 0) {
		perror(" fail to create thread ");
		return -1;
	}
event_base_dispatch(base);
printf("finished \n");
return 0;
}

void on_write(int sock, short event, void *arg)
{
char *buffer = (char *)arg;
send(sock, buffer, strlen(buffer), 0);
free(buffer);
}void cmd_msg_cb(int fd, short events, void *arg)
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
}void socket_read_cb(int fd, short events, void *arg)
{
char msg[1024];
int res;

	    //ä¸ºäºç®åèµ·è§ï¼ä¸èèè¯»ä¸åæ°æ®çæåµ
	int len = read(fd, msg, sizeof(msg) - 1);
if (len <= 0)
 {
perror("read fail ");
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
msg[len] = '\0';

	    //  temp=strcmp(msg,"ok");
	    //  printf("temp %d \n", temp);
if (0 == strcmp(msg, "ok"))
 {
tcp_flag = SEND;
printf("recv %s from server\n", msg);

		    //    printf("recv %s from server\n", send_flag);
		}
}

typedef struct sockaddr SA;
int tcp_connect_server(const char *server_ip, int port)
{
int sockfd, status, save_errno;
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
status = inet_aton(server_ip, &server_addr.sin_addr);
if (status == 0)	//the server_ip is not valid value
	{
errno = EINVAL;
return -1;
}
sockfd = socket(PF_INET, SOCK_STREAM, 0);
if (sockfd == -1)
return sockfd;
status =
	    connect(sockfd, (SA *) & server_addr, sizeof(server_addr));
if (status == -1)
 {
save_errno = errno;
close(sockfd);
errno = save_errno;	//the close may be error
		return -1;
}
evutil_make_socket_nonblocking(sockfd);
return sockfd;
}


