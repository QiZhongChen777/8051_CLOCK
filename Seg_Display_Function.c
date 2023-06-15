#include<AT89X51.h>
sbit SEG_A = P0^0;
sbit SEG_B = P0^1;
sbit SEG_C = P0^2;
sbit SEG_D = P0^3;
sbit SEG_E = P0^4;
sbit SEG_F = P0^5;
sbit SEG_G = P0^6;
sbit SEG_DP = P0^7;
void Display(char num,char* pos,char* Time_Mode)
{
	if(num >= 0)
	{
    switch(num%10)
		{
        case 0: 
            SEG_A = SEG_B = SEG_C = SEG_D = SEG_E = SEG_F = 0;
            SEG_G = SEG_DP = 1;
            break;
        case 1: 
            SEG_B = SEG_C = 0;
            SEG_A = SEG_D = SEG_E = SEG_F = SEG_G = SEG_DP = 1;
            break;
        case 2:
            SEG_A = SEG_B = SEG_D = SEG_E = SEG_G = 0;
            SEG_C = SEG_F = SEG_DP = 1;
            break;
        case 3:
            SEG_A = SEG_B = SEG_C = SEG_D = SEG_G = 0;
            SEG_E = SEG_F = SEG_DP = 1;
            break;
        case 4:
            SEG_B = SEG_C = SEG_F = SEG_G = 0;
            SEG_A = SEG_D = SEG_E = SEG_DP = 1;
            break;
        case 5:
            SEG_A = SEG_C = SEG_D = SEG_F = SEG_G = 0;
            SEG_B = SEG_E = SEG_DP = 1;
            break;
        case 6:
            SEG_A = SEG_C = SEG_D = SEG_E = SEG_F = SEG_G = 0;
            SEG_B = SEG_DP = 1;
            break;
        case 7:
            SEG_A = SEG_B = SEG_C = 0;
            SEG_D = SEG_E = SEG_F = SEG_G = SEG_DP = 1;
            break;
        case 8:
            SEG_A = SEG_B = SEG_C = SEG_D = SEG_E = SEG_F = SEG_G = 0;
            SEG_DP = 1;
            break;
        case 9:
            SEG_A = SEG_B = SEG_C = SEG_D = SEG_F = SEG_G = 0;
            SEG_E = SEG_DP = 1;
            break;
        default:
            break;
		}
		if((*pos) == 2 && (*Time_Mode) == 1)
		{
			SEG_DP = 0;			
		}
	}
}