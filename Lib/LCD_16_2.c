//4 bit 16x2 LCD Library

#include <REGX52.H>
#include "Delay.h"
#include <intrins.h>

sbit LCD_RS	= P2^0;
sbit LCD_RW = P2^1; 
sbit LCD_EN	= P2^2; 
sbit LCD_D4	= P2^4; //Define LCD's pins
sbit LCD_D5 = P2^5;
sbit LCD_D6 = P2^6;
sbit LCD_D7 = P2^7;

unsigned int t;
unsigned int x;

void Delay_us(unsigned int t){
	for(x = 0; x < t;  x++)
		_nop_();
}

void LCD_Enable(){
    LCD_EN =1;
    Delay_us(3);
    LCD_EN =0;
    Delay_us(50); 
}

void LCD_Send4Bit(unsigned char Data){
     LCD_D4=Data & 0x01;
     LCD_D5=(Data>>1)&1;
     LCD_D6=(Data>>2)&1;
     LCD_D7=(Data>>3)&1;
}

void LCD_SendCommand(unsigned char command){
     LCD_Send4Bit(command >>4);
     LCD_Enable();
     LCD_Send4Bit(command); 
     LCD_Enable();
}

void LCD_Clear(){
      LCD_SendCommand(0x01); 
      Delay_us(10);
}

void LCD_Init(){ //Put this before using the LCD
      LCD_Send4Bit(0x00);	  
      Delay_ms(20);
      LCD_RS=0;
      LCD_RW=0;
      LCD_Send4Bit(0x03);	 
      LCD_Enable();
      Delay_ms(5);
      LCD_Enable();
      Delay_us(100);
      LCD_Enable();
      LCD_Send4Bit(0x02);	  
      LCD_Enable();
      LCD_SendCommand( 0x28 ); 
      LCD_SendCommand( 0x0c);  
      LCD_SendCommand( 0x06 );
      LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y){
      unsigned char address;
      if(!y)
				address=(0x80+x);
      else 
				address=(0xc0+x);
      Delay_us(1000);
      LCD_SendCommand(address);
      Delay_us(50);
}

void LCD_PutChar(unsigned char Data){
      LCD_RS=1;
      LCD_SendCommand(Data);
      LCD_RS=0 ;
}

void LCD_Puts(char *s){
      while (*s){
         LCD_PutChar(*s);
       s++;
        }
}

