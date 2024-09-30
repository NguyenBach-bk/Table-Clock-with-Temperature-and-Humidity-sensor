#ifndef _DS1307_H_
#define _DS1307_H_

void DS1307_Write_Time(unsigned char hour, unsigned char minute, unsigned char second);
void DS1307_Read_Time(unsigned char *hour, unsigned char *minute, unsigned char *second);
void DS1307_Write_Date(unsigned char day, unsigned char date, unsigned char month, unsigned char year);
void DS1307_Read_Date(unsigned char * day, unsigned char * date, unsigned char * month, unsigned char * year);

#endif