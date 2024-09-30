#include <REGX52.H>
#include "I2C.h"

void DS1307_Write_Time(unsigned char hour, unsigned char minute, unsigned char second) //24h 
{
	second = ((second/10)<<4)|(second%10);
	minute = ((minute/10)<<4)|(minute%10);
	hour   = ((hour  /10)<<4)|(hour  %10);
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x00);
	I2C_Write(second);
	I2C_Write(minute);
	I2C_Write(hour);
	I2C_Stop();
}

void DS1307_Read_Time(unsigned char *hour, unsigned char *minute, unsigned char *second)
{
	unsigned char tmp_h, tmp_m, tmp_s;
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write(0xD1);
	tmp_s = I2C_Read(1);
	tmp_m = I2C_Read(1);
	tmp_h = I2C_Read(0);
	I2C_Stop();
	*second   = ((tmp_s >> 4) & 0x0F) * 10 + (tmp_s & 0x0F);
	*minute = ((tmp_m >> 4) & 0x0F) * 10 + (tmp_m & 0x0F);
	*hour = ((tmp_h >> 4) & 0x0F) * 10 + (tmp_h & 0x0F);
}

void DS1307_Write_Date(unsigned char day, unsigned char date, unsigned char month, unsigned char year)
{
	date 	= ((date/10)<<4)  | (date%10);
	month = ((month/10)<<4) | (month%10);
	year	= ((year/10)<<4)  | (year%10);
	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x03); 
	I2C_Write(day); 
	I2C_Write(date);
	I2C_Write(month);
	I2C_Write(year);
	I2C_Stop();
}

void DS1307_Read_Date(unsigned char * day, unsigned char * date, unsigned char * month, unsigned char * year)
{
	I2C_Start();
	I2C_Write(0xD0); 
	I2C_Write(0x03);
	I2C_Start(); 
	I2C_Write(0xD1); 
	*day  = I2C_Read(1);
	*date = I2C_Read(1);
	*month= I2C_Read(1);
	*year = I2C_Read(0);
	I2C_Stop();
	*day &= 0x07;
	*date &= 0x3F;
	*date = (*date>>4)*10 + (*date & 0x0F);
	*month &= 0x1F;
	*month = (*month>>4)*10 + (*month & 0x0F);
	*year = (*year>>4)*10 + (*year & 0x0F);	
}

#endif