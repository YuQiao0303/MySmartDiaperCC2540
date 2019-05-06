#include <ioCC2540.h>
#include "DHT11.H"
//

uchar lastHumidity;
uchar lastTemperature;
Stored_data *stored_data;
bool android_ready;
bool save_power;
//温湿度定义
uchar ucharFLAG,uchartemp;
uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge=4;
uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
uchar ucharcomdata;

//延时函数
void Delay_us() //1 us延时
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");    
    asm("nop");
    asm("nop");
    asm("nop");    
    asm("nop"); 
}

void Delay_10us() //10 us延时
{
#if 0  
  Delay_us();
  Delay_us();
  Delay_us();
  Delay_us();
  Delay_us();   
#else
  int i = 6;
  while(i--);  
#endif  
}

void Delay_ms(uint Time)//n ms延时
{
    unsigned char i;
    while(Time--)
    {
        for(i=0;i<100;i++)
            Delay_10us();
    }
}

//温湿度传感
void COM(void)    // 温湿写入
{     
    uchar i;         
    for(i=0;i<8;i++)    
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);
        Delay_10us();
        Delay_10us();
        Delay_10us();
        Delay_10us();
        Delay_10us();
        Delay_10us();

        uchartemp=0;
        if(DATA_PIN)uchartemp=1;
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++);   
        if(ucharFLAG==1)break;    
        ucharcomdata<<=1;
        ucharcomdata|=uchartemp; 
    }    
}

void DHT11(void)   //温湿传感启动
{
    DATA_PIN=0;
    Delay_ms(19);  //>18MS
    DATA_PIN=1; 
    P2DIR &= ~0x01; //重新配置IO口方向
    Delay_10us();
    Delay_10us();                        
    Delay_10us();
    Delay_10us();  

    if(!DATA_PIN) 
    {
        ucharFLAG=2; 
        while((!DATA_PIN)&&ucharFLAG++);
        ucharFLAG=2;
        while((DATA_PIN)&&ucharFLAG++); 
        COM();
        ucharRH_data_H_temp=ucharcomdata;
        COM();
        ucharRH_data_L_temp=ucharcomdata;
        COM();
        ucharT_data_H_temp=ucharcomdata;
        COM();
        ucharT_data_L_temp=ucharcomdata;
        COM();
        ucharcheckdata_temp=ucharcomdata;
        DATA_PIN=1; 
        uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_temp+ucharRH_data_L_temp);
        if(uchartemp==ucharcheckdata_temp) 
        {
            ucharRH_data_H=ucharRH_data_H_temp;
            ucharRH_data_L=ucharRH_data_L_temp;
            ucharT_data_H=ucharT_data_H_temp;
            ucharT_data_L=ucharT_data_L_temp;
            ucharcheckdata=ucharcheckdata_temp;
        }
        wendu_shi=ucharT_data_H;///10; 
       // wendu_ge=ucharT_data_H%10;
        
        shidu_shi=ucharRH_data_H;///10; 
       // shidu_ge=ucharRH_data_H%10;        
    } 
    else //没用成功读取，返回0
    {
        wendu_shi=0x55; 
        wendu_ge=0;
        
        shidu_shi=0x55; 
        shidu_ge=0;  
    } 
    
    P2DIR |= 0x01; //IO口需要重新配置 
    
}








//---------------下面的内容是省电模式新增
void stored_data_Init(){
    //开机初始化stored_data;
    for(int i=0;i<TABLE_SIZE;i++)
    {
        stored_data->table[i] = 0x00;

    }
    for(int i=0;i<32;i++)
    {
      for(int j=0;j<7;j++)
        stored_data->data[i][j] = 0;
    }
    android_ready = false;
    save_power = false;
}

bool pee(){
    bool flag;
    if(shidu_shi >= 60 && lastHumidity<60)
        flag = true;
    else 
        flag = false;
    return flag;
}

void updateLastData(){
    lastHumidity = shidu_shi;
}

