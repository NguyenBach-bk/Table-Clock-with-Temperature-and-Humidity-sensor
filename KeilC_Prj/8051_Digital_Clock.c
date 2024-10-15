#include <REGX52.H>
#include "..\Lib\Delay.h"
#include "..\Lib\Lcd_16_2.h"
#include "..\Lib\I2C.h"
#include "..\Lib\DS1307.h"
#include "..\Lib\DHT11.h"

unsigned char hour, minute, second, old_sec = 60;
unsigned char day, date, month, year;
unsigned char I_RH, D_RH, I_TEMP, D_TEMP, checksum;
unsigned char set_hr, set_min, set_sec;
unsigned char set_day, set_date, set_mon, set_yr;
unsigned char mode = 0, clear_scr = 0, update_scr = 0;

sbit MODE = P1^4;
sbit BTN1 = P1^5;
sbit BTN2 = P1^6;
sbit BTN3 = P1^7;

void MODE_BTN()
{
	if(MODE == 0)
		{
			Delay_ms(20);
			if(MODE == 1)
			{
				clear_scr = 0;
				mode++;
				if(mode == 1)
					update_scr = 0;
				if(mode == 2)
					update_scr = 2;
			}
			
			if(mode >= 3)
			{
				clear_scr = 0;
				update_scr = 0;
				mode = 0;
			}
		}
}

void SET_TIME()
{
	if(BTN1 == 0)
		{
			Delay_ms(20);
			if(BTN1 == 1)
				{
				 set_hr++;
				 update_scr--;
				}
		}
	
	if(set_hr >= 24)
		{
			set_hr = 0;
		}
				
	if(BTN2 == 0)
		{
			Delay_ms(20);
			if(BTN2 == 1)
				{
				 set_min++;
				 update_scr--;
				}
		}
	
	if(set_min >= 60)
		{
			set_min = 0;
		}
		
}

void SET_CAL() 
{
    unsigned char days_in_month;

    if (set_mon == 2) 
		{ 
        if ((set_yr % 4 == 0) && (set_yr != 0)) 
				{
            days_in_month = 29;
        } else 
			  {
            days_in_month = 28;
        }
    } 
		else if (set_mon == 4 || set_mon == 6 || set_mon == 9 || set_mon == 11) 
		{
        days_in_month = 30;
    } 
		else 
		{
        days_in_month = 31;
    }

    if (BTN1 == 0) 
		{
        Delay_ms(20);
        if (BTN1 == 1) 
				{
            set_date++;
						update_scr--;
            if (set_date > days_in_month) 
						{
                set_date = 1;
            }
        }
    }

    if (BTN2 == 0) 
		{
        Delay_ms(20);
        if (BTN2 == 1)
				{
            set_mon++;
					  update_scr--;
            if (set_mon > 12) 
						{
                set_mon = 1;
            }
 				}
    }

    if (BTN3 == 0) 
		{
        Delay_ms(20);
        if (BTN3 == 1) 
				{
            set_yr++;
					  update_scr--;
            if (set_yr > 99) 
						{
                set_yr = 0;
            }
        }
    }
}

void RETURN()
{
	if(BTN3 == 0)
		{
			Delay_ms(20);
			if(BTN3 == 1)
			{
				clear_scr = 0;
				update_scr = 0;
				mode = 0;
			}
		}
}

void main()
{
	  P3_6 = 0;
		P3_7 = 0;
    LCD_Init(); // Move this outside the loop
    while(1)
    {
			while(mode == 0)
			{
				MODE_BTN();	
				
				if(P3_6 == 1)
					P3_7 = 1;
				else
					P3_7 = 0;
				
				MODE_BTN();	
				
				if(clear_scr == 0)
				{
					LCD_Clear();
					Delay_ms(10);
					clear_scr = 1;
				}
				
				MODE_BTN();	
				
				DS1307_Read_Time(&hour, &minute, &second); // Use pointers
				DS1307_Read_Date(&day, &date, &month, &year);
				
				MODE_BTN();	
				
				if(second != old_sec)
				{	
				MODE_BTN();	
				
				LCD_Gotoxy(0, 0);
				LCD_Puts("  ");
				LCD_Gotoxy(10, 0);
				LCD_Puts("  ");
				LCD_Gotoxy(15, 0);
				LCD_Puts(" ");
					
				MODE_BTN();	
					
				LCD_Gotoxy(0, 1);
				LCD_Puts("  ");
				LCD_Gotoxy(10, 1);
				LCD_Puts("  ");
				LCD_Gotoxy(15, 1);
				LCD_Puts(" ");
					
				MODE_BTN();
					
        LCD_Gotoxy(2, 0);
        LCD_PutChar(hour / 10 + '0'); // Convert to ASCII
        LCD_PutChar(hour % 10 + '0');
        LCD_PutChar(':');
        LCD_PutChar(minute / 10 + '0');
					
				MODE_BTN();
					
        LCD_PutChar(minute % 10 + '0');
        LCD_PutChar(':');
        LCD_PutChar(second / 10 + '0');
        LCD_PutChar(second % 10 + '0');
				
				MODE_BTN();
					
				LCD_Gotoxy(2, 1);
				LCD_PutChar(date / 10 + '0'); // Convert to ASCII
        LCD_PutChar(date % 10 + '0');
        LCD_PutChar('/');
        LCD_PutChar(month / 10 + '0');
				
				MODE_BTN();
				
        LCD_PutChar(month % 10 + '0');
        LCD_PutChar('/');
        LCD_PutChar(year / 10 + '0');
        LCD_PutChar(year % 10 + '0');
				
				MODE_BTN();
				
				Request();
				Response();
				I_RH     = Receive_data();
				D_RH     = Receive_data();
				I_TEMP   = Receive_data();
				D_TEMP   = Receive_data();
				checksum = Receive_data();
				
				MODE_BTN();
				
				LCD_Gotoxy(12, 0);
				LCD_PutChar(I_TEMP/10+48);
				LCD_PutChar(I_TEMP%10+48);
				LCD_PutChar('C');
				
				MODE_BTN();
				
				LCD_Gotoxy(12, 1);
				LCD_PutChar(I_RH/10+48);
				LCD_PutChar(I_RH%10+48);
				LCD_PutChar('%');
				
				set_hr = hour; set_min = minute; set_sec = second;
				set_day = day; set_date = date; set_mon = month; set_yr = year;
				
				old_sec = second;
				
				MODE_BTN();
			  }
			}
			
			while(mode == 1)
			{
				MODE_BTN();
				SET_TIME();
				RETURN();
				
				if(P3_6 == 1)
					P3_7 = 1;
				else
					P3_7 = 0;
				
				MODE_BTN();
				SET_TIME();
				RETURN();
				
				if(clear_scr == 0)
				{
					LCD_Clear();
					Delay_ms(10);
					clear_scr = 1;
				}
				
				MODE_BTN();
				SET_TIME();
				RETURN();
				
				while(update_scr == 0)
				{
					LCD_Gotoxy(4, 0);
					LCD_Puts("SET TIME");
					LCD_Gotoxy(2, 1);
					LCD_Puts("HR:");
					LCD_PutChar(set_hr / 10 + '0');
					LCD_PutChar(set_hr % 10 + '0');
					LCD_Gotoxy(9, 1);
					LCD_Puts("MN:");
					LCD_PutChar(set_min / 10 + '0');
					LCD_PutChar(set_min % 10 + '0');	
					DS1307_Write_Time(set_hr, set_min, 0);
					update_scr = 1;
				}
			}
			
			while(mode == 2)
			{
				MODE_BTN();
				SET_CAL();
				
				if(P3_6 == 1)
					P3_7 = 1;
				else
					P3_7 = 0;
				
				MODE_BTN();
				SET_CAL();
				
				if(clear_scr == 0)
				{
					LCD_Clear();
					Delay_ms(10);
					clear_scr = 1;
				}
				
				MODE_BTN();
				SET_CAL();
				
				while(update_scr == 2)
				{
					LCD_Gotoxy(1, 0);
					LCD_Puts("SET DATE");
					LCD_Gotoxy(11, 0);
					LCD_Puts("DY:");
					LCD_PutChar(set_date / 10 + '0');
					LCD_PutChar(set_date % 10 + '0');
					LCD_Gotoxy(3, 1);
					LCD_Puts("MT:");
					LCD_PutChar(set_mon / 10 + '0');
					LCD_PutChar(set_mon % 10 + '0');
					LCD_Gotoxy(10, 1);
					LCD_Puts("YR:");
					LCD_PutChar(set_yr / 10 + '0');
					LCD_PutChar(set_yr % 10 + '0');
					DS1307_Write_Date(1, set_date, set_mon, set_yr);
					update_scr = 3;
				}
			}
   }
}

#endif