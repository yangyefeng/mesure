/*
 * Copyright © 2001-2011 Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _RUN4G_H_
#define _RUN4G_H_

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>

#include<sys/time.h>
#include<time.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<pthread.h>

#include<event.h>
#include<event2/util.h>
#include <event2/http.h>
#include "config.h"
#include "sqlite3.h"
#include "air_modbus.h"
#include "air_db.h"
#include "memento.h"

typedef struct{
char year[40];
char month[4];
short day;
short hour;
short min;
short second;
}syd_time;

struct msg_data
{
  short id;
  float wind_speed;
  float rainfall;
  float temperature;
  float air_pressure;
  float radiation;
  float wind_diretion;
  float humidity;
  syd_time tm;
};
extern struct msg_data tcp_data;

int run4g_init(void);
int trans_handle(void);
int tcp_connect_server(const char* server_ip, int port);
void cmd_msg_cb(int fd, short events, void* arg);
void socket_read_cb(int fd, short events, void *arg);
void on_write(int sock, short event, void* arg);



#endif  /* _MODBUS_H_ */
