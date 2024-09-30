#ifndef _I2C_H_
#define _I2C_H_

void I2C_Delay();
void I2C_Init();
void I2C_Start();
void I2C_Stop();
bit I2C_Get_Ack();
bit I2C_Write(unsigned char dat);
void I2C_Ack();
void I2C_Nak();
unsigned char I2C_Read(bit ack);	

