#include<AT89X51.h>
void Time_Clock(char*minute_low,char*minute_high,char*hour_low,char*hour_high,char*second)
{
	if((*second) == 60)
	{
		(*minute_low)++;
		(*second) = 0;
	}
	if((*minute_low) == 10)
	{
		(*minute_high)++;
		(*minute_low) = 0;
	}
	if((*minute_high) == 6)
	{
		(*hour_low)++;
		(*minute_high) = 0;
	}
	if((*hour_high) < 2 && (*hour_low) == 10)
	{
		(*hour_low) = 0;
		(*hour_high)++;
	}
	if((*hour_high) == 2 && (*hour_low) == 4)
	{
		(*hour_low) = 0;
		(*hour_high) = 0;
	}
	if( (((*hour_low) + ((*hour_high) * 10)) ) >= 24)
	{
		(*hour_low) = 0;
		(*hour_high) = 0;			
	}
}
void Modify_Time(char*minute_low,char*minute_high,char*hour_low,char*hour_high,char*seg_pos)
{
	if((*minute_low) < 0 || (*minute_low) >= 10)
	{
		if((*minute_low) < 0)
		{
			(*minute_low) = 9;
		}
		else
		{
			(*minute_low) =0;		
		}
	}
	if((*minute_high) < 0 || (*minute_high) >= 6)
	{
		if((*minute_high) < 0)
		{
			(*minute_high) = 5;
		}
		else
		{
			(*minute_high) =0;		
		}
	}
	if((*hour_low) < 0)
	{
		if((*hour_high) < 2)
		{
			(*hour_low) = 9;
		}
		if((*hour_high) == 2)
		{
			(*hour_low) =3;		
		}
	}	
	if((*hour_low) > 9)
	{
		if((*hour_high) < 2)
		{
			(*hour_low) = 0;
		}
	}
	if((*hour_high) < 0)
	{
		if((*hour_low) > 3)
		{
			(*hour_high) = 1;
		}
		else
		{
			(*hour_high) = 2;		
		}		
	}
	if((*hour_high) > 1)
	{
		if((*hour_low) > 3)
		{
			(*hour_high) = 0;
		}		
	}
	if((*hour_high) > 2)
	{
		(*hour_high) = 0;
	}	
	if(((*hour_high) * 10) + (*hour_low) == 24)
	{
		if(seg_pos == 4)
		{
			(*hour_high) = 0;	
		}
		if(seg_pos == 3)
		{
			(*hour_low) = 0;
		}		
	}
}
  

