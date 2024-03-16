
#define  F_CPU   8000000
#include <util/delay.h>
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Int.h"
#include "Stepper.h"
#include "LCD_Int.h"
#include "KeyPad_Int.h"


#define SEGMENT_PORT  PORTA
void segment_display_mlx(char n){
	const char arr[10]={0x3f<<1,0x06<<1,0x5b<<1,0x4f<<1,0x66<<1,0x6d<<1,0x7d<<1,0x07<<1,0x7f<<1,0x4f<<1};
	SET_BIT(PORTC,6);
	PORTA=arr[n%10];
	CLR_BIT(PORTC,7);
	_delay_ms(10);
	SET_BIT(PORTC,7);
	PORTA = arr[n/10];
	
	CLR_BIT(PORTC,6);
	_delay_ms(10);
}

void segment_display_bcd(char n){
	char d0=n%10;
	char d1=n/10;
	PORTC =d1<<4|d0 ;
}

void segment_display_hex(char n){
	char d0=n;
	PORTC=d0;
}

void unit_dispaly(char n){
	char d0=n++;
	PORTC=d0;
}



int main(void)
{
   
 DIO_Init();
 LCD_Init();
 KEYPAD_int();
 
 
 u8 flag=0;
 u8 sum=0;
 u8 sub=0;
 u8 mult=0;
 u8 divide=0;
 
 s32 num;
 s32 num1;
 s32 final;
 
 
  while (1)
  {

	   u8 k=KEYPAD_Getkey();

	 if (k!='t')
	 {
 
		 if (k>='0'&&k<='9')
		 {
			 
			 if (flag==0)
			 {
				 
				 LCD_SetCursor(1,1);
				 LCD_WriteString("        ");
				 LCD_SetCursor(1,1);
				 flag=1;
			 }
			 if(k>='0'&&k<='9'){
				 num=num*10+k-'0';
			 }
			 
			 LCD_WriteChar(k);
	 
		 }
		 
		 
		 if (k=='+')
		 {
			 if (flag==0)
			 {
				 LCD_SetCursor(1,1);
				 LCD_WriteString("        ");
				 LCD_SetCursor(1,1);
				 flag=1;
			 }
			 
			  num1=num;
			  LCD_WriteChar(k);
			  sum=1;
			  num=0;
			   }
			   
		 
		  if (k=='-')
		  {
			  
			  if (flag==0)
			  {
				  LCD_SetCursor(1,1);
				  LCD_WriteString("        ");
				  LCD_SetCursor(1,1);
				  flag=1;
			  }

			 num1=num;
			 LCD_WriteChar(k);
			 sub=1;
			 num=0;
		  }
		  
		   if (k=='*')
		   {
			   
			   if (flag==0)
			   {
				   LCD_SetCursor(1,1);
				   LCD_WriteString("        ");
				   LCD_SetCursor(1,1);
				   flag=1;
			   }
			   num1=num;
			   LCD_WriteChar(k);
			   mult=1;
			   num=0;
		   }
		   
		    if (k=='/')
		    {
				
				if (flag==0)
				{
					LCD_SetCursor(1,1);
					LCD_WriteString("        ");
					LCD_SetCursor(1,1);
					flag=1;
				}
				
			    num1=num;
			    LCD_WriteChar(k);
			    divide=1;
			    num=0;
		    }
		 
		 
		 // SHOW RESULT
		 
		 else if(k=='='){
			 
		// ADD WITH NEGATIVE NUMBER
			 
			 if (sum==1 && sub==1)
			 {
				  LCD_SetCursor(2,1);
				  LCD_WriteString("       ");
				  LCD_SetCursor(2,1);
				  LCD_WriteString("DEC:");
				  LCD_WriteNumber(-num1+num);
				  LCD_SetCursor(2,11);
				  LCD_WriteString("HEX:");
				  LCD_WriteHex(-num1+num);

				  
			 }
			 
			 
			 
			 // MUTIPLY WITH NEGATIVE NUMBER
			 
			 else if (mult==1 && sub==1)
			 {
				 LCD_SetCursor(2,1);
				 LCD_WriteString("       ");
				 LCD_SetCursor(2,1);
				 LCD_WriteString("DEC:");
				 LCD_WriteNumber(-num1*num);
				 LCD_SetCursor(2,11);
				 LCD_WriteString("HEX:");
				 LCD_WriteHex(-num1*num);
				 
				 
				 
			 }
			 
		 //ADDITION
			 
			 else if (sum==1)
			 {
				 LCD_SetCursor(2,1);
				 LCD_WriteString("      ");
				 LCD_SetCursor(2,1);
				 LCD_WriteString("DEC:");
				 LCD_WriteNumber(num+num1);
				 LCD_SetCursor(2,11);
				  LCD_WriteString("HEX:");
				 LCD_WriteHex(num1+num);
				 final=num+num1;
				  
				   
				  

			 }
			 
		 //SUBTRACTION
			 
			 else if (sub==1)
			 {
				  LCD_SetCursor(2,1);
				  LCD_WriteString("       ");
				  LCD_SetCursor(2,1);
				  LCD_WriteString("DEC:");
				  LCD_WriteNumber(num1-num);
				  LCD_SetCursor(2,11);
				   LCD_WriteString("HEX:");
				  LCD_WriteHex(num1-num);
				 
			 }
			 
		//DIVISION
			 
			  else if (divide==1)
			  {
				   LCD_SetCursor(2,1);
				   LCD_WriteString("       ");
				  LCD_SetCursor(2,1);
				  LCD_WriteString("DEC:");
				  LCD_WriteNumber(num1/num);
				  LCD_SetCursor(2,11);
				   LCD_WriteString("HEX:");
				  LCD_WriteHex(num1/num);
				 
			  }
			  
		 //MULTIPLY
			  
			   else if (mult==1)
			   {
				    LCD_SetCursor(2,1);
				    LCD_WriteString("       ");
				   LCD_SetCursor(2,1); 
				   LCD_WriteString("DEC:");
				   LCD_WriteNumber(num1*num);
				   LCD_SetCursor(2,11);
				   LCD_WriteString("HEX:");
				   LCD_WriteHex(num1*num);
				   
				   
		 // NO SIGNS
				   
			   }else{
				     LCD_SetCursor(2,1);
				     LCD_WriteString("        ");
				LCD_SetCursor(2,1);
				LCD_WriteString("DEC:");
				LCD_WriteNumber(num);
				LCD_SetCursor(2,11);
				 LCD_WriteString("HEX:");
				LCD_WriteHex(num);
				 num=0;
			   }
			   
		
			   
	    num1=0;   
		num=0;
		flag=0;
		sum=0;
		sub=0;
		mult=0;
		divide=0;
	
		 }
	 
	 else if (k=='c')
	 {
		LCD_Clear();
			  LCD_SetCursor(1,5);
			  
			  LCD_WriteString("CALCULATOR");
			  _delay_ms(1000);
			 
			  LCD_Clear();
			  num=0;
			  flag=0;
			  sum=0;
			  sub=0;
			  mult=0;
			  divide=0;
			 
		 
		
		 
	 }
	 
	
	 
		}
  }
 }
	
