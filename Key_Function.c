#include<AT89X51.h>
void seg_pos_add(char*A,char*B,char*C,char*D,unsigned char*seg_pos)
{
	switch((*seg_pos))
	{
		case 1:
			(*A)++;			
			break;
		case 2:
			(*B)++;
			break;
		case 3:
			(*C)++;
			break;
		case 4:
			(*D)++;
			break;
		default:
			break;
	}
}
void seg_pos_sub(char*A,char*B,char*C,char*D,unsigned char*seg_pos)
{
	switch((*seg_pos))
	{
		case 1:
			(*A)--;			
			break;
		case 2:
			(*B)--;
			break;
		case 3:
			(*C)--;
			break;
		case 4:
			(*D)--;
			break;
		default:
			break;
	}
}  