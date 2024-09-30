#include <REGX52.H>
#include "intrins.h"
#include "Delay.h"

sbit DHT11 = P3^0;

void delay_40us()
{
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
	_nop_ (); _nop_ (); _nop_ (); _nop_ (); _nop_ ();
}

void Request()
{
	DHT11 = 0;
	Delay_ms(20);
	DHT11 = 1;
}

void Response()
{
	while(DHT11==1);
	while(DHT11==0);
	while(DHT11==1);
}

int Receive_data()
{
	int i, dataD=0;
	for(i=0; i<8;i++)
	{
		while(DHT11==0);
		delay_40us();
		if(DHT11==1)
			dataD=(dataD<<1)|(0x01);
		else
			dataD=(dataD<<1);
		while(DHT11==1);
	}
	return dataD;
}

/* Example
	while(1)
	{
		Request();
		Response();
		I_RH=Receive_data();
		D_RH=Receive_data();
		I_TEMP=Receive_data();
		D_TEMP=Receive_data();
		Checksum=Receive_data();
		
		if((I_RH + D_RH + I_TEMP + D_TEMP) != Checksum)
		{
			Lcd_Out(1,1,"Error!");
		}
*/