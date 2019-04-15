#ifndef __DHT11_H__
#define __DHT11_H__

#include "OSAL.h"

#define DATA_PIN P2_0
#define uchar unsigned char
typedef unsigned int  uint;




#define TABLE_SIZE 4
#define DATA_SIZE 7


typedef struct
{
    uint8 table[4];
    uint8 data[32][7];
}Stored_data;

extern uchar currentData[3]; 
extern uchar lastData[3];
extern Stored_data *stored_data;
extern bool android_ready;


uint dataChange();
void updateLastData();


extern void Delay_ms(unsigned int xms);	//延时函数
extern void COM(void);                  // 温湿写入
extern void DHT11(void);                //温湿传感启动


extern uchar temp[2]; 
extern uchar temp1[5];
extern uchar humidity[2];
extern uchar humidity1[9];
extern uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge;

#endif