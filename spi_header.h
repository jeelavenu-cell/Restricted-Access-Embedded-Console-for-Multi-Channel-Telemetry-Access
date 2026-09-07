
//#include <lpc21xx.h>
//#include "delay.h"
#define Mode_0     0x00  // CPOL 0 CPHA 0
#define Mode_1     0x08  // CPOL 0 CPHA 1
#define Mode_2     0x10  // CPOL 1 CPHA 0
#define Mode_3     0x18  // CPOL 1 CPHA 1
typedef unsigned char u8;
typedef unsigned int  u32;
typedef float f32;
void Init_SPI0(void);
u8 SPI0(u8);
f32 Read_ADC_MCP3204(u8 channelNo);
f32 Read_ADC_LM35(u8 channelNo);
void Init_SPI0(void)
{

PINSEL0 |=0X00001500;
  S0SPCCR  = 150;// to set 100kbps(The SPI rate may be
                   //calculated as: PCLK rate / SPI_RATE
                        //S0SPCCR  = 60;// To set 250kbps
S0SPCR  = (1<<5|Mode_0); //spi module in master mode,
                                  //CPOL =1,CCPHA = 1. MSB first
IODIR0 |= (1<<7);
IOSET0 = (1 << 7);
}

u8 SPI0(u8 data)
{
   u8 stat;
   stat = S0SPSR;    //clear SPIF
   S0SPDR = data;   // load spi tx reg
   while((S0SPSR & (1 << 7)) == 0);
   return S0SPDR;    // read data from SPI data reg, place into buffer
}


f32 Read_ADC_MCP3204(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
   
  IOCLR0|=(1<<7);
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
  IOSET0|=(1<<7);
  adcVal=((hByte&0x0f)<<8)|lByte;
  return ((adcVal*3.3)/4096);
}


f32 Read_ADC_LM35(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
  f32 temp,voltage;
   
  IOCLR0|=(1<<7);
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
  IOSET0|=(1<<7);
  adcVal=((hByte&0x0f)<<8)|lByte;
  voltage= ((adcVal*3.3)/4096);
  temp=voltage/0.01; //caluculate temp-> 10mv=1 degree cel
  return temp;
}

