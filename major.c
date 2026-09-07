#include <lpc21xx.h>
#include "lcdheader.h"
#include "keypadheader.h"
#include "eeprom.h"
#include "spi_header.h"
#include"uart.h"
#include <string.h>
//#define DC1 1<<16 //P1.16
// #define DC2 1<<17 //P1.17
// #include <lpc21xx.h>

#define DC1 (1UL << 18)
#define DC2 (1UL << 19)

void temperature_monitor(void)
{
    f32 f;
    int gsm_sent = 0;
    int loop_count;
    for(loop_count = 0; loop_count < 20; loop_count++)
    {
        f = Read_ADC_LM35(1);
        LCD_COMMAND(0x01);
        LCD_COMMAND(0x80);
        LCD_STR((unsigned char*)"TEMP:");
        LCD_FLOAT(f);
        LCD_COMMAND(0xC0);
        if(f >= 30.0)
        {
            IOSET1 = DC1;
            IOCLR1 = DC2;
            LCD_STR((unsigned char*)"FAN ON");
            if(gsm_sent == 0)
            {
                delayms(500);
                gsm_msgse((unsigned char*)"ALERT: Temp > 30C. Fan is ON.");
                gsm_sent = 1;
            }
        }
        else
        {
            IOCLR1 = DC1 | DC2;
            LCD_STR((unsigned char*)"FAN OFF");
        }
        delayms(500);
    }
    IOCLR1 = DC1 | DC2;
}

void voltage_monitor(void)
{
    f32 f;
    int loop_count;

    for(loop_count = 0; loop_count < 20; loop_count++)
    {
        f = Read_ADC_MCP3204(0);
        
        LCD_COMMAND(0x01);
        LCD_COMMAND(0x80);
        LCD_STR((unsigned char*)"VOLTAGE:");
        LCD_COMMAND(0xC0);
        LCD_FLOAT(f);
        
        delayms(500);
    }
}


int main(void)
{
   // f32 f;
int k,j,st =0;
    int i,op,res, count = 0;
unsigned char str[20];
    unsigned char txbuff[] = "vector@123";
      unsigned char rxbuff[20];
  char s[] = "RESTRICTED ACCESSC EMBEDDED CONSOLE FOR MULTI_CHANNEL TELEMENTARY  ";
 
 IODIR1|=DC1|DC2;
  LCD_INIT();
 
  LCD_COMMAND(0X80);
 //LCD_STR("OK");
 i2c_init(); //i2c initialisation
 Init_SPI0(); //hw SPI initialisation
 IOPIN0 |= 1<<7;//cs initially high
 UART0_INIT();
 gsm_config();
i2c_page_write(0x50,0x00,txbuff,10);
 i2c_page_read(0x50,0x00,rxbuff,10);
 rxbuff[10]='\0';
 delayms(100);
 

for(k=0;s[k];k++)
{
if(s[k]==' ')
{
LCD_COMMAND(0X01);
LCD_COMMAND(0X80);
for(j=st;j<k;j++)
{
LCD_DATA(s[j]);
}
delayms(1000);
st=k+1;
}
}

    while(1)
    {
        if(count >= 3)
        {
            LCD_COMMAND(0x01);
            LCD_STR("LIMIT REACHED");
            break;
        }

        LCD_COMMAND(0x01);
        LCD_STR("ENTER PIN");
        LCD_COMMAND(0xC0);

        for(i = 0; i < 10; i++)
        {
            str[i] = keyscan();
            LCD_DATA('*');
        }

        str[10] = '\0';

       // res = strcmp(str1, str2);
  res=strcmp((const char *)rxbuff,(const char *)str);
        //count++;

        if(res == 0)
        {
             count = 0; // Reset counter on correct PIN
            LCD_COMMAND(0x01);
            LCD_STR("CORRECT");
            delayms(1000);
			
            while(1)
            {
                LCD_COMMAND(0x01);
                LCD_COMMAND(0x80);
                LCD_STR("ENTER 0 OR 1");
                op = keyscan();
 
if(op=='0')
{
LCD_COMMAND(0x01);
LCD_COMMAND(0x80);
LCD_STR((unsigned char*)"VOLT MONITOR");
delayms(1000);    
voltage_monitor();
}
else if(op=='1')
{
                LCD_COMMAND(0x01);
                LCD_COMMAND(0x80);
                LCD_STR("TEMP MONITOR");

                delayms(1000);
                temperature_monitor();
}
else
{
LCD_COMMAND(0XC0);
LCD_STR("INVALID");
delayms(1000);
}
        }
		}  
        else
        {
		count++;
            LCD_COMMAND(0x01);
            LCD_STR("WRONG PIN");
delayms(1000);
        }
    }
 
    //while(1);
}

