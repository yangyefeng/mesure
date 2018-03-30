/*
 * Copyright 漏 2001-2011 St茅phane Raimbault <stephane.raimbault@gmail.com>
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

#ifndef _AIR_MODBUS_H_
#define _AIR_MODBUS_H_
#include"modbus.h"
#include"sqlite3.h"
#include "emsascommon.h"

//采集数据结构体
struct environment_data{
u32   id;
float particulate_matter_25;
float particulate_matter_10;
float temperature_value;
float humidity_value;
float wind_direction;
float wind_speed_value;
float noise_value;
float atmospheric_pressure_value;
};

extern struct environment_data var_environment_data;
void modbus_init(void);

char read_air_environment(struct environment_data *air_data);

#endif  /* _MODBUS_H_ */
