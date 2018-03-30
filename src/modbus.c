#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"air_modbus.h"
#include"config.h"
#define MAX_SENSOR_COUNT 2


//int modbus485_sync_time=100000;
modbus_t * mb;		//����һ��modbus_t���͵�context�������򿪴���



//���豸��ַ
char read_slave_address(void)
{









	else






//��������������
char read_air_environment(struct environment_data *air_data)
{

	switch (configInfo.factory_num) {
	case 0:
		res = modbus_read_registers(mb, 12, 4, modbus_buf);
		/*
		   air_data->particulate_matter_25= (float)(modbus_buf[0]<<8)+modbus_buf[1];
		   air_data->particulate_matter_10= (float)(modbus_buf[2]<<8)+modbus_buf[3];
		   air_data->temperature_value= (float)(modbus_buf[4]<<8)+modbus_buf[5];
		   air_data->humidity_value= (float)(modbus_buf[6]<<8)+modbus_buf[7];
		   air_data->wind_direction= (float)(modbus_buf[8]<<8)+modbus_buf[9];
		   air_data->wind_speed_value= (float)(modbus_buf[10]<<8)+modbus_buf[11];
		   air_data->noise_value= (float)(modbus_buf[12]<<8)+modbus_buf[13];
		   air_data->atmospheric_pressure_value=(float)(modbus_buf[14]<<8)+modbus_buf[15];
		 */
		air_data->particulate_matter_25 = 1.2;







		break;
	case 1:


		    (float)(modbus_buf[0] << 8) + modbus_buf[1];

		    (float)(modbus_buf[2] << 8) + modbus_buf[3];

		    (float)(modbus_buf[4] << 8) + modbus_buf[5];

		    (float)(modbus_buf[6] << 8) + modbus_buf[7];

		    (float)(modbus_buf[8] << 8) + modbus_buf[9];

		    (float)(modbus_buf[10] << 8) + modbus_buf[11];

		    (float)(modbus_buf[12] << 8) + modbus_buf[13];

		    (float)(modbus_buf[14] << 8) + modbus_buf[15];
		break;
	default:
		break;
	}



		    //  printf("%g %g \n",    air_data->particulate_matter_25,air_data->particulate_matter_10);
		    return 1;


	else





/**
��ʼ��
**/
void modbus_init(void)
{

	modbus_set_slave(mb, 1);	//set slave address
	modbus_connect(mb);



	modbus_set_response_timeout(mb, &t);
