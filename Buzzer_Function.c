#include<AT89X51.h>
#include "Buzzer_Function.h"
sbit SW_1 = P3^2;
sbit SW_2 = P3^3;
sbit SW_3 = P3^4;
sbit SW_4 = P3^5;
sbit buzzer = P3^6;
unsigned char code song[]={1, 1, 2, 1, 4, 3, 1, 1, 2, 1, 5, 4, 1, 1, 8, 6, 4, 3, 2, 11, 11, 6, 4, 5, 4, 15};            
unsigned char code beat[]={4, 4, 8, 8, 8, 16, 4, 4, 8, 8, 8, 16, 4, 4, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 16};                  
unsigned int code tone[]={1012, 956, 852, 759, 716, 638, 568, 506, 478, 426, 379, 536, 10};
unsigned char  i=0;                                                                     
unsigned char  tone_H, tone_L;                                                         

void is_align(unsigned char* SetAlarm)
{
		ET1 = 1;
		buzzer = 1;   
		while(song[i] != 15)                                                                   
		{
			if(SW_1 == 0 || SW_2 == 0 || SW_3 == 0 || SW_4 == 0 || ET1 == 0)
			{
				buzzer = 0;
				ET1 = 0;
				(*SetAlarm) = 0;
				i = 0;
				break;
			}
			TH1 = tone_H= (65536 - tone[song[i]]) / 256;                                         
			TL1 = tone_L = (65536 - tone[song[i]]) % 256;                                       
			TR1 = 1;                                                                       
			Beat(beat[i]);                                                          
			i++;                                                                       
			TR1 = 0;
			buzzer = 1;
		}
		i = 0;
}

void Beat(unsigned char x)                                                         
{ 
	unsigned char  i,j,k;                                                                
  for(i=0;i<x;i++)
	{
			if(SW_1 == 0 || SW_2 == 0 || SW_3 == 0 || SW_4 == 0 || ET1 == 0)
			{
				buzzer = 0;
				ET1 = 0;
				break;
			}
      for(j=0;j<50;j++)
			{
					if(SW_1 == 0 || SW_2 == 0 || SW_3 == 0 || SW_4 == 0 || ET1 == 0)
					{
						buzzer = 0;
						ET1 = 0;
						break;
					}
          for(k=0;k<40;k++)
					{
							if(SW_1 == 0 || SW_2 == 0 || SW_3 == 0 || SW_4 == 0 || ET1 == 0)
							{
								buzzer = 0;
								ET1 = 0;
								break;
							}
					}
			}
	}
}

void timer1_isr() interrupt 3                                                    
{
	TH1 = tone_H;                                                                          
  TL1 = tone_L;                                                                           
  buzzer = ~buzzer;                                                                     
} 