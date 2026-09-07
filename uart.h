#include <lpc21xx.h>
//#include "delay.h"
void UART0_INIT(void);
void UART0_TX(unsigned char);
void UART0_STR(unsigned char *);
unsigned char UART0_RX(void);
//void UART0_STR(unsigned char *);
#define NUMBER "+919949081242"

void gsm_config(void)
{
    delayms(2000);

    /* Check GSM module */
    UART0_STR("AT\r\n");
   delayms(500);

    /* Set SMS text mode */
    UART0_STR("AT+CMGF=1\r\n");
     delayms(500);
}

void gsm_msgse(unsigned char *msg)
{
    /* Tell GSM module to send SMS */
    UART0_STR("AT+CMGS=\"");

    /* Send farmer's phone number */
    UART0_STR(NUMBER);

    /* Send closing quote and Enter */
    UART0_STR("\"\r\n");

    /* Wait for GSM '>' prompt */
    delayms(2000);

    /* Send the actual message */
    UART0_STR(msg);

    /* Ctrl + Z = send SMS */
    UART0_TX(0x1A);

    /* Wait for SMS to be sent */
   delayms(5000);
}


 void UART0_INIT(void)
{
PINSEL0 &=~0X0000000F;
 PINSEL0|=0X00000005;
 U0LCR=0X83;
 U0DLL=97;
 U0DLM=0;
 U0LCR=0X03;
}
void UART0_TX(unsigned char txbyte)
{
  while(((U0LSR>>5)&1)==0);
   U0THR=txbyte;
}
unsigned char UART0_RX(void)
{
    while((U0LSR&1)==0);
     return U0RBR;
}
void UART0_STR(unsigned char *p)
{
  while(*p)
  UART0_TX(*p++);

}
