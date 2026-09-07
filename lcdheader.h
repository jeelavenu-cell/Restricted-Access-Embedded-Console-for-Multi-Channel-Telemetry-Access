 #include"delay.h"
#define  LCD 0xff<<8
#define RS 1<<16
#define E  1<<17
  void LCD_INIT(void);
  void LCD_COMMAND(unsigned char cmd);
  void LCD_DATA(unsigned char d);
  void LCD_INTEGER(int n);
void LCD_FLOAT(float f);
void LCD_STR(unsigned char *p);

void LCD_INIT(void)
{
IODIR0|=LCD|RS|E;
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}
void LCD_COMMAND(unsigned char cmd)
{
  IOCLR0=LCD;
  IOSET0=cmd<<8;
  IOCLR0=RS;
  IOSET0=E;
  delayms(2);
  IOCLR0=E;
}
void LCD_DATA(unsigned char d)
{
 IOCLR0=LCD;
  IOSET0=d<<8;
  IOSET0=RS;
  IOSET0=E;
  delayms(2);
  IOCLR0=E;
}
void LCD_INTEGER(int n)
{
 signed char i=0;
 unsigned char arr[16];
 if(n==0)
 {
 LCD_DATA('0');
 }
 else
 {
   if(n<0)
   {
   LCD_DATA('-');
   n=-n;
   }
   while(n>0)
   {
   arr[i]=n%10;
   n=n/10;
   i++;
   }
   for(--i;i>=0;i--)
   LCD_DATA(arr[i]+48);
 }
}
void LCD_FLOAT(float f)
{
  int temp;
  temp=f;
  LCD_INTEGER(temp);
  LCD_DATA('.');
  temp=(f-temp)*100;
  LCD_INTEGER(temp);
 
}
void LCD_STR(unsigned char *p)
{
 while(*p)
 {
   LCD_DATA(*p++);
 }

}
