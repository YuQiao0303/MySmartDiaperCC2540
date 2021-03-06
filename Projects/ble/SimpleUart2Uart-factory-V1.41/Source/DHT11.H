#ifndef __DHT11_H__
#define __DHT11_H__


#define DATA_PIN P2_0
#define uchar unsigned char
typedef unsigned int  uint;
//--------------
#include "OSAL.h"

#define TABLE_SIZE 4
#define DATA_SIZE 6


typedef struct
{
    uint8 table[4];
    uint8 data[32][7];
}Stored_data;


extern Stored_data *stored_data;
extern bool android_ready;
extern bool save_power;

extern bool pee();
extern void updateLastData();
extern void stored_data_Init();

//-----------------
extern void Delay_ms(unsigned int xms);	//��ʱ����
extern void COM(void);                  // ��ʪд��
extern void DHT11(void);                //��ʪ��������


extern uchar temp[2]; 
extern uchar temp1[5];
extern uchar humidity[2];
extern uchar humidity1[9];
extern uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge;

#endif