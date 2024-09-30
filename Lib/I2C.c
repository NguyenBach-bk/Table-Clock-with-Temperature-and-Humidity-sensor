#include <REGX52.H>
#include "intrins.h"

sbit I2C_SCL = P1^7;
sbit I2C_SDA = P1^5;

void I2C_Delay(){
	_nop_() ; _nop_() ;  _nop_() ; _nop_() ; _nop_() ;
	_nop_() ; _nop_() ;  _nop_() ; _nop_() ; _nop_() ;
}

void I2C_Init(){
	I2C_SCL = 1;
	I2C_SDA = 1;
}

void I2C_Start(){
	I2C_SCL = 1;
	I2C_Delay();
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 0;
}

void I2C_Stop(){
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
	I2C_SDA = 1;
}

bit I2C_Get_Ack()
{
	bit result;
  I2C_SDA = 1;
	I2C_Delay();
  I2C_SCL = 1;
	I2C_Delay();
	result = I2C_SDA;
  I2C_SCL = 0;
	return result;
}

bit I2C_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
	  I2C_SDA = (bit)(dat&0x80);	
	  I2C_SCL = 1;
		I2C_Delay();
		I2C_SCL = 0;
	  dat<<=1;
	}
	return(I2C_Get_Ack());
}

void I2C_Ack()
{
	I2C_SDA = 0;
	I2C_Delay();
	I2C_SCL = 1;
	I2C_Delay();
  I2C_SCL = 0;
}

void I2C_Nak()
{
  I2C_SDA = 1;
	I2C_Delay();
  I2C_SCL = 1;
	I2C_Delay();
  I2C_SCL = 0;
}

unsigned char I2C_Read(bit ack)
{
    unsigned char i, dat=0;
    for(i=0;i<8;i++)
	{
	  I2C_SDA = 1;
		I2C_Delay();
	  I2C_SCL = 1;
		I2C_Delay();
	    dat <<= 1;
		if(I2C_SDA)
		{
		 	dat |= 0x01;
		}
			I2C_SCL = 0;
    }
	if(ack)
	{
	 	I2C_Ack();
	}
	else
	{
	 	I2C_Nak();
	}
    return dat;
}

