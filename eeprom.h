
//#include <lpc21xx.h>
//#include "delay.h"
#include <string.h>
#define clk 60000000
#define pclk clk/4
#define speed 100000
#define loadval ((pclk/speed)/2)
#define rled 1<<16
 typedef unsigned char u8;
void i2c_init(void);
void i2c_page_write(u8,u8,u8*,u8);
void i2c_page_read(u8,u8,u8*,u8);
void i2c_init(void)
{
  PINSEL0|=0X50;
  I2SCLL=loadval;
  I2SCLH=loadval;
  I2CONSET=1<<6;
}
void i2c_page_write(u8 slaveaddr,u8 dataaddr,u8*buff,u8 n)
{
int i;
//START
   I2CONSET=1<<5;
   while(((I2CONSET>>3)&1)==0);
   I2CONCLR=1<<5;
//SLAVE ADDRESS

I2DAT=slaveaddr<<1;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);

 //DATA WORD ADDR

I2DAT=dataaddr;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);

//DATA WORD

for(i=0;i<n;i++)
{
  I2DAT=buff[i];
  I2CONCLR=1<<3;
  while(((I2CONSET>>3)&1)==0);
}
  //STOP
  I2CONSET=1<<4;
  I2CONCLR=1<<3;
  delayms(10);
}

void i2c_page_read(u8 slaveaddr,u8 dataaddr,u8* buff,u8 n)
{
  int i;
//START
   I2CONSET=1<<5;
   while(((I2CONSET>>3)&1)==0);
   I2CONCLR=1<<5;
//SLAVE ADDRESS

I2DAT=slaveaddr<<1;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);

 //DATA WORD ADDR

 I2DAT=dataaddr;
 I2CONCLR=1<<3;
 while(((I2CONSET>>3)&1)==0);

//restart

I2CONSET=1<<5;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);
I2CONCLR=1<<5;

 //slave
 I2DAT=(slaveaddr<<1)|1;
 I2CONCLR=1<<3;
 while(((I2CONSET>>3)&1)==0);

//ACK&DATA READ

for(i=0;i<n;i++)
{
if(i<n-1)
I2CONSET=1<<2;
else
I2CONCLR=1<<2;
I2CONCLR=1<<3;
while(((I2CONSET>>3)&1)==0);
buff[i]=I2DAT;
}


//STOP

I2CONSET=1<<4;
I2CONCLR=1<<3;
delayms(10);

}

