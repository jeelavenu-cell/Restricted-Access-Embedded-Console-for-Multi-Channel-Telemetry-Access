#include<lpc21xx.h>
 void delayseconds(unsigned int seconds)
 {
  T0PR=15000000-1;
  T0TCR=0x01;
  while(T0TC<seconds);
  T0TCR=0X03;
  T0TCR=0X00;
 } 
 void delayms(unsigned int ms)
 {
  T0PR=15000-1;
  T0TCR=0x01;
  while(T0TC<ms);
  T0TCR=0X03;
  T0TCR=0X00;
 }
