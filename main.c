#include<AT89X51.h>
#include "Clock_Function.h"
#include "Seg_Display_Function.h"
#include "Buzzer_Function.h"
#include "Button_Function.h"
#include "Key_Function.h"
#define Key_Add 0x01					
#define Key_Sub 0x02
#define Key_7seg_pos 0x03
#define Key_Ent 0x04
unsigned char KeyCode = 0;
unsigned char KeyRam = 0;				
unsigned char PreKeyRam = 0;		
unsigned char KeyCnt = 0;				
unsigned char NoKeyCnt = 0;			
unsigned char Key_Value = 0;
unsigned char pos=0 , T1000ms_cnt=200 , T20ms_cnt=4 , T25ms_cnt=5 , T10ms_cnt=2 , T5ms_cnt=1;
unsigned char Time_Mode=0;	
unsigned char seg_pos=0;
unsigned char second=0;
char minute_low=0;
char minute_high=0;
char hour_low=0;
char hour_high=0;
char Alarm_minute_low=0;
char Alarm_minute_high=0;
char Alarm_hour_low=0;
char Alarm_hour_high=0;
unsigned char SetAlarm=0;
sbit SEG_DP = P0^7;
sbit SW_1 = P3^2;
sbit SW_2 = P3^3;
sbit SW_3 = P3^4;
sbit SW_4 = P3^5;
sbit seg_pos_1 = P2^3;
sbit seg_pos_2 = P2^2;
sbit seg_pos_3 = P2^1;
sbit seg_pos_4 = P2^0;
sbit buzzer = P3^6;
/////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	TMOD = 0x10;																									
	EA = 1;														
	TL0 = (8196 - 4600) % 32;
	TH0 = (8196 - 4600) / 32;
	TR0 = 1;
	ET0 = 1;
	while(1)
	{
		if(Time_Mode == 0)
		{
			if(SW_1 == 0 && SW_4 == 0 && seg_pos == 0)
			{
				Time_Mode = 1;
			}
			if(SetAlarm == 1 && seg_pos == 0)
			{
				if((Alarm_minute_low == minute_low) && (Alarm_minute_high == Alarm_minute_high) && (Alarm_hour_low == Alarm_hour_low) && (Alarm_hour_high == Alarm_hour_high))
				{
					is_align(&SetAlarm);
				}
			}
		}
		if(Time_Mode == 1)
		{
			if(SW_1 == 0 && SW_2 == 0 && seg_pos == 0)
			{
				Time_Mode = 0;
				SetAlarm = 1;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void timer0_isr() interrupt 1   																
{
	TL0 = (8196 - 4600) % 32;
	TH0 = (8196 - 4600) / 32;

	if(Time_Mode == 0)
	{
		switch(pos)
		{
			case 0:
				if(seg_pos == 1 )
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(minute_low,&pos,&Time_Mode);
						seg_pos_1 = 0;
						seg_pos_2 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;
					}
				}
				else
				{
					Display(minute_low,&pos,&Time_Mode);
					seg_pos_1 = 0;
					seg_pos_2 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;	
				}
				break;
			case 1:
				if(seg_pos == 2)
				{
					if(--T25ms_cnt == 0)
					{ 
						T25ms_cnt = 5;
						Display(minute_high,&pos,&Time_Mode);
						seg_pos_2 = 0;
						seg_pos_1 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;	
					}
				}
				else
				{
					Display(minute_high,&pos,&Time_Mode);
					seg_pos_2 = 0;
					seg_pos_1 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;	
				}				
				break;
			case 3:
				if(seg_pos == 3)
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(hour_low,&pos,&Time_Mode);
						seg_pos_3 = 0;
						seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_4 = 1;	
					}
				}
				else
				{
					Display(hour_low,&pos,&Time_Mode);
					seg_pos_3 = 0;
					seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_4 = 1;	
				}				
				break;
			case 2:
				if(seg_pos == 4)
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(hour_high,&pos,&Time_Mode);
						seg_pos_4 = 0;
						seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_3 = 1;	
					}
				}
				else
				{
					Display(hour_high,&pos,&Time_Mode);
					seg_pos_4 = 0;
					seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_3 = 1;		
				}				
				break;
			default:
				break;
		}
		pos++;
		if(pos==4)
		{
			pos=0;
		}
		if(--T20ms_cnt == 0)
		{
			T20ms_cnt = 4;
			ReadKey(&KeyRam);
			Key_Value = GetKey(&KeyCode,&KeyRam,&PreKeyRam,&KeyCnt,&NoKeyCnt);
			switch(Key_Value)
			{
				case Key_Add:
					seg_pos_add(&minute_low,&minute_high,&hour_low,&hour_high,&seg_pos);
					Modify_Time(&minute_low,&minute_high,&hour_low,&hour_high,&seg_pos);
					KeyCode = 0;
					break;		
									
				case Key_Sub:
					seg_pos_sub(&minute_low,&minute_high,&hour_low,&hour_high,&seg_pos);
					Modify_Time(&minute_low,&minute_high,&hour_low,&hour_high,&seg_pos);
					KeyCode = 0;
					break;
					
				case Key_7seg_pos:
					seg_pos++;
					if(seg_pos > 4)
					{
						seg_pos = 1;
					}
					KeyCode = 0;
					break;
					
				case Key_Ent:
					seg_pos = 0;
					KeyCode = 0;
					break;

				default:
					KeyCode = 0;
					break;
			}
		}
	}
	if(Time_Mode == 1)
	{
		switch(pos)
		{
			case 0:
				if(seg_pos == 1 )
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(Alarm_minute_low,&pos,&Time_Mode);
						seg_pos_1 = 0;
						seg_pos_2 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;
					}
				}
				else
				{
					Display(Alarm_minute_low,&pos,&Time_Mode);
					seg_pos_1 = 0;
					seg_pos_2 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;
				}
				break;
			case 1:
				if(seg_pos == 2)
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(Alarm_minute_high,&pos,&Time_Mode);
						seg_pos_2 = 0;
						seg_pos_1 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;
					}
				}
				else
				{
					Display(Alarm_minute_high,&pos,&Time_Mode);
					seg_pos_2 = 0;
					seg_pos_1 = 1 , seg_pos_3 = 1 , seg_pos_4 = 1;
				}				
				break;
			case 2:
				if(seg_pos == 3)
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(Alarm_hour_low,&pos,&Time_Mode);
						seg_pos_3 = 0;
						seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_4 = 1;
					}
				}
				else
				{
					Display(Alarm_hour_low,&pos,&Time_Mode);
					seg_pos_3 = 0;
					seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_4 = 1;
				}				
				break;
			case 3:
				if(seg_pos == 4)
				{
					if(--T25ms_cnt == 0)
					{
						T25ms_cnt = 5;
						Display(Alarm_hour_high,&pos,&Time_Mode);
						seg_pos_4 = 0;
						seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_3 = 1;
					}
				}
				else
				{
					Display(Alarm_hour_high,&pos,&Time_Mode);
					seg_pos_4 = 0;
					seg_pos_1 = 1 , seg_pos_2 = 1 , seg_pos_3 = 1;
				}				
				break;
			default:
				break;
		}
		pos++;
		if(pos==4)
		{
			pos=0;
		}
		if(--T20ms_cnt == 0)
		{
			T20ms_cnt = 4;
			ReadKey(&KeyRam);
			Key_Value = GetKey(&KeyCode,&KeyRam,&PreKeyRam,&KeyCnt,&NoKeyCnt);
			if(Time_Mode == 1)
			{
				switch(Key_Value)
				{
					case Key_Add:
						seg_pos_add(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&seg_pos);
						Modify_Time(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&seg_pos);
						Time_Clock(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&second);
						KeyCode = 0;
						break;		
										
					case Key_Sub:
						seg_pos_sub(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&seg_pos);
						Modify_Time(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&seg_pos);
						Time_Clock(&Alarm_minute_low,&Alarm_minute_high,&Alarm_hour_low,&Alarm_hour_high,&second);
						KeyCode = 0;
						break;
						
					case Key_7seg_pos:
						seg_pos++;
						if(seg_pos > 4)
						{
							seg_pos = 1;
						}
						KeyCode = 0;
						break;
						
					case Key_Ent:
						seg_pos = 0;
						KeyCode = 0;
						break;			

					default:
						KeyCode = 0;
						break;
				}
			}
		}			
	}
	if(--T1000ms_cnt == 0)
	{
		second++;
		if(Time_Mode == 0)
		{
			SEG_DP = 0;
		}
		T1000ms_cnt = 200;
		Time_Clock(&minute_low,&minute_high,&hour_low,&hour_high,&second);
	}
}
  

