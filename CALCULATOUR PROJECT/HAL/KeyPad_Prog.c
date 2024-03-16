#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "KeyPad_Int.h"
#include "KeyPad_Cfg.h"

#define  F_CPU   8000000
#include <util/delay.h>

u8 KeyArray[ROW][COL]={{'7','8','9','/' },
	                   {'4','5','6','*' },
		               {'1','2','3','-' },
			           {'c','0','=','+' } };


void KEYPAD_int(void){
	u8 r;
	
	for (r=0;r<ROW;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
}

u8 KEYPAD_Getkey(void){
	
	
	u8 r,c,key=NO_KEY;
	
	for (r=0;r<ROW;r++)
	{
	  DIO_WritePin(FIRST_OUTPUT+r,LOW);
	  
	  for (c=0;c<COL;c++)
	  {
		  if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
		  {
			 key=KeyArray[r][c];
			 _delay_ms(10);
			 while(DIO_ReadPin(FIRST_INPUT+c)==LOW); // busy wait MSH HYTL3 MN FUNCTION GHER LMA ASHEL EDE
			  _delay_ms(10);
		  }
	  }
	  DIO_WritePin(FIRST_OUTPUT+r,HIGH);  // to avoid garbage
	  	
	}
	
	return key;
}


