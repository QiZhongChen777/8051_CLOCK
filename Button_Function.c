#include<AT89X51.h>
#define Key_Add 0x01					
#define Key_Sub 0x02
#define Key_7seg_pos 0x03
#define Key_Ent 0x04		
sbit SW_1 = P3^2;
sbit SW_2 = P3^3;
sbit SW_3 = P3^4;
sbit SW_4 = P3^5;
void ReadKey(unsigned char* KeyRam)
{
	(*KeyRam) = 0;
	if(SW_1 == 0)
	{
		(*KeyRam) = 1;
	}
	else if(SW_2 == 0)
	{
		(*KeyRam) = 2;
	}
	else if(SW_3 == 0)
	{
		(*KeyRam) = 3;
	}
	else if(SW_4 == 0)
	{
		(*KeyRam) = 4;
	}	
}

unsigned char GetKey(unsigned char* KeyCode,unsigned char* KeyRam,unsigned char* PreKeyRam,unsigned char* KeyCnt,unsigned char* NoKeyCnt)	
{
	if((*KeyRam) != 0)
	{
		if((*KeyRam) == (*PreKeyRam))
		{
			(*NoKeyCnt) = 0;
			(*KeyCnt)++;
			if((*KeyCnt) == 1)
			{
				switch((*KeyRam))
				{
					case 0x01:	
						(*KeyCode) = Key_Add;	
						break;
					case 0x02:
						(*KeyCode) = Key_Sub;	
						break;
					case 0x03:	
						(*KeyCode) = Key_7seg_pos;	
						break;
					case 0x04:	
						(*KeyCode) = Key_Ent;		
						break;
					default:
						break;
				}
			}
			if((*KeyCnt) > 200)
			{
				(*KeyCnt) = 200;
			}
		}
		else
		{
			(*PreKeyRam)=(*KeyRam);			
		}		
	}
	else
	{
		(*NoKeyCnt)++;
		if((*NoKeyCnt) > 2)
		{
			(*PreKeyRam)=0;
			(*KeyCnt)=0;
			(*NoKeyCnt)=0;
			switch((*KeyCode))
			{
				case 0x01:	
					(*KeyCode) = Key_Add;
					(*NoKeyCnt)=5;
					break;
				case 0x02:
					(*KeyCode) = Key_Sub;
					(*NoKeyCnt)=5;
					break;
				case 0x03:	
					(*KeyCode) = Key_7seg_pos;
					(*NoKeyCnt)=5;
					break;
				case 0x04:	
					(*KeyCode) = Key_Ent;
					(*NoKeyCnt)=5;
					break;
				default:
					(*NoKeyCnt)=0;
					break;
			}
		}		
	}
	return (*KeyCode);
}
