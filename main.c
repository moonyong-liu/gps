#include "stm32f10x.h"
#include "stdio.h"	 
#include <stdlib.h>

//unsigned char *top;
//unsigned char *temp;
float latitude;
extern unsigned char Buffer_Remessage[100];
unsigned char Flag_one_message;
S_T_I_TYPE second, second_longi;
static __RecordScrCoo Head;      // record lcd coord root-node
unsigned short base_x, base_y;
u16 current_x = BASE_X; 
u16 current_y = BASE_Y;
int pointer;
u16 buffer[100][2];
int main(void)
{  	
	u8 x,y,i;
	RCC_INIT();
	NVIC_INIT();
	GPIO_INIT();
	LCD_Init();
	UARTForGPS_INIT();
	EXTI_INIT();	
	ili9320_Clear(BLACK); 	
	InitMapInterface();
	Timer1Init();
	GPIO_ResetBits( GPIOB, GPIO_Pin_1 );
	GPIO_SetBits( GPIOB, GPIO_Pin_1 );
	#if 0
	while( x<200 ){
		for( y=0;y<10;y++ ){
			buffer[x][0] = BASE_X+x;
			buffer[x][1] = BASE_Y+x;
			DrowWalkLine( buffer[x][0], buffer[x][1] );
			x++;
		}
	}
	
	zoom_in( buffer );
	for( i=0; i<100; i++ ){
			DrowWalkLine( buffer[i][0], buffer[i][1] );
	}
	#endif
	while(1)
	{

		if( Flag_one_message ){
			Flag_one_message = 0;
			
			switch( Buffer_Remessage[5] ) {
				case 'A':break;
				case 'B':break;
 				case 'L': ShowGPGLL();break;
				case 'V':break;
				case 'C': GPRMC();break;
				case 'G':break;				
			}
		}
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	}
}

/* give value of need to drow */
void GPRMC(void)
{
  
  int *walkpoint = &pointer;
	uint8_t space_full;
  str_GPRMC *struction_gprmc;	
  // a function  DrowPoint( x, y )  x y from below return ;
	walkpoint = WalkWalkPoint();
	struction_gprmc = SendStruct();
	// calculate x and y transmit to function to drow the line
	if( walkpoint != NULL ){
		current_x += *walkpoint;
		current_y += *(walkpoint+1);
		space_full = record_screen_coord( &Head, current_x, current_y );	
		PrintLatiLongi( struction_gprmc );
	  DrowWalkLine( current_x, current_y );
		if( space_full == ERROR ){	
			free_space( &Head );
		}	
	}

}
/* brief    : when the flash space is full need free them
** parameter: need free root node
** return   : 0
** priority :  */

uint8_t free_space( __RecordScrCoo* Head )
{
	while( Head->link != NULL ){
		free_space( Head );
	}
	free( &Head );
	return 0;
}
	
/* A string value transition to int
** parmeter1: a pointer of sting
** parmeter2: how many amount need transition
** return: a pointer of int
*/  
int *StrToInt( const GPSU8 *string,unsigned char i )  	
{
	static int temp_sti = 0;
	
	while( i-- ) {
		temp_sti = temp_sti * 10 + (*string++ - '0');
	}
	return &temp_sti;
}
// unsigned int *
// IntToStr( S_T_I_TYPE integer )
// {
// 	
// }




// latitude and longitude value view 
void Print_lati_longi(void)
{
	
}

// convert the UTC+0 time to UTC+8 time and Print
void Convert_UTCto8(void)
{
	u32 i;
	i = *(StrToInt( &Buffer_Remessage[7], 2 )) + 8;
	if ( i > 24 ){
		i -= 24;
	}
	Buffer_Remessage[7] = i / 10;
	Buffer_Remessage[8] = i % 10;
	Disp_Draw7X12( UTC_H, Buffer_Remessage[7], 0 );
	Disp_Draw7X12( UTC_H+7, Buffer_Remessage[8], 0 );
	Disp_Draw7X12( UTC_M, Buffer_Remessage[9] - '0', 0 );
	Disp_Draw7X12( UTC_M+7, Buffer_Remessage[10] - '0', 0 );
	Disp_Draw7X12( UTC_S, Buffer_Remessage[11] - '0', 0 );
	Disp_Draw7X12( UTC_S+7, Buffer_Remessage[12] - '0', 0);
}

// Print the coord to TFT
void 
Print_coord( double *lati_now, double *longi_now )
{

}
// calculate coord for draw point
double 
Calculate_coordfordraw( const GPSU8 *integer, unsigned char i, const GPSU8 *decimals ,unsigned char j )
{
	return *(StrToInt( integer, i ))*60 + *(StrToInt( decimals, j ))/10000 ;	
}


