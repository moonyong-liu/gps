#include "stm32f10x.h"
#include "float.h"

#define VALID 17   // Buffer_Remessage NO.17 data  VALID OR WORRNING
extern unsigned char Buffer_Remessage[100];
unsigned int longi_last, lati_last;
str_GPRMC gprmc_struct;

void
CodeStart(void)
{
	//$PSRF101,0,0,0,000,0,0,12,4*10
	USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );
	USART_SendData(USART1, '$');
	USART_SendData(USART1, 'P');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'F');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '4');
	USART_SendData(USART1, '*');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '0');	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );
}

void
WarmStart(void)
{
	//$PSRF101,0,0,0,000,0,0,12,2*16
	USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );
	USART_SendData(USART1, '$');
	USART_SendData(USART1, 'P');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'F');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, '*');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '6');	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );

}

void
HotStart(void)
{
	//$PSRF101,0,0,0,000,0,0,12,1*15
	USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );
	USART_SendData(USART1, '$');
	USART_SendData(USART1, 'P');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'F');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '*');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '5');	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );

}


// Serial Interface Setting 
// Factory reset
void
FactoryReset(void)
{
	//$PSRF101,0,0,0,000,0,0,12,8*1C
	USART_ITConfig( USART1, USART_IT_RXNE, DISABLE );
	USART_SendData(USART1, '$');
	USART_SendData(USART1, 'P');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'F');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, ',');
	USART_SendData(USART1, '8');
	USART_SendData(USART1, '*');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, 'C');	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );
	
}


// Customer Define Message Setting Command

void 
MessageSet(void)
{
	USART_SendData(USART1, '$');
	USART_SendData(USART1, 'P');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'F');
	USART_SendData(USART1, '2');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'N');
	USART_SendData(USART1, 'M');
	USART_SendData(USART1, 'E');
	USART_SendData(USART1, 'A');
	USART_SendData(USART1, '9');
	USART_SendData(USART1, '6');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'N');
	USART_SendData(USART1, 'U');
	USART_SendData(USART1, 'L');
	USART_SendData(USART1, 'L');
	USART_SendData(USART1, '3');
	USART_SendData(USART1, '8');
	USART_SendData(USART1, '4');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, 'A');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, 'L');
	USART_SendData(USART1, 'L');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'A');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'V');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, 'M');
	USART_SendData(USART1, 'C');
	USART_SendData(USART1, '1');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'V');
	USART_SendData(USART1, 'T');
	USART_SendData(USART1, 'G');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, ',');
	
	USART_SendData(USART1, 'U');
	USART_SendData(USART1, 'S');
	USART_SendData(USART1, 'E');
	USART_SendData(USART1, 'R');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, '*');
	USART_SendData(USART1, '0');
	USART_SendData(USART1, 'D');
}
/* GPRMC message store function */
void store_gprmc( str_GPRMC* struction )
{
	uint8_t cmp = 0;
	uint8_t point = 0;
	uint8_t i=0;
	while( Buffer_Remessage[cmp] != '*' ){
		if( Buffer_Remessage[cmp] != ',' && point == 0 ){
			struction->MessageID[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 1 ){
			struction->UTCTime[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 2 ){
			struction->Status = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 3){
			struction->Latitude[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 4){
			struction->NSIndicator = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 5){
			struction->Longitude[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 6){
			struction->EWIndicator = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 7){
			struction->Speed[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 8){
			struction->Course[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 9){
			struction->Data[i++] = Buffer_Remessage[cmp];
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 10){	
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 1l){	
		}
		else if( Buffer_Remessage[cmp] != ',' && point == 12){
			struction->Mode = Buffer_Remessage[cmp];
		}
		else{
			point +=1;
			i=0;
		}
		cmp += 1;
	}
	struction->PointStatus = Buffer_Remessage[cmp];
	struction->Checksum[0] = Buffer_Remessage[cmp+1];
	struction->Checksum[1] = Buffer_Remessage[cmp+2];
}



/* store and show GPRMC message 
** return a pointer (buffer) 
*/
int *WalkWalkPoint(void)
{
	
	static int buffer[2];
	unsigned int longi_now, lati_now;
	
	store_gprmc( &gprmc_struct );
	if( gprmc_struct.Status == 'V' ){
		return 0;
	}
	longi_now = *(TranStrToInt( &(gprmc_struct.Longitude[6]), 5 )) / 1000; // 6 is longitude[11] number 6 value, the first of mmmm 
	lati_now = *(TranStrToInt( &(gprmc_struct.Latitude[5]), 5 )) / 1000;  // same as above
  buffer[0] = longi_last - longi_now;
	buffer[1] = lati_last - lati_now;
	if( buffer[0] > 10 || buffer[0] < -10 ){
	  longi_last = longi_now;
	  lati_last = lati_now;
		return 0;
	}
	longi_last = longi_now;
	lati_last = lati_now;
	
	return buffer;
	


	// calculate coord to int		
	// UTC TIME 	
	//Convert_UTCto8();
}
/* return a pointer by gprmc_struct */
str_GPRMC *SendStruct(void)
{
	return &gprmc_struct;
}

/* transition string to float 
	 parmater 1: *str     A string  pointer 
   parmater 2: quantity How many character need transition
   return:     a float value 
*/
float *TranStrToFloat( const GPSU8 *str, unsigned char quantity )
{
	static float temp = 0;
	while( quantity-- ){
		temp = temp*10 + (*str++ - '0');
	}
	return &temp;
}
/* transition string to int 
	 parmater 1: *str     A string  pointer 
   parmater 2: quantity How many character need transition
   return:     a int value 
*/
int *TranStrToInt( const GPSU8 *str, unsigned char quantity )
{
  static int temp = 0;
	while( quantity-- ){
		temp = temp*10 + (*str++ - '0');
	}
	return &temp;
}

/* store and show GPGLL message */
void ShowGPGLL(void)
{
	str_GPGLL gpgll_struct;
	StoreGPGLL( &gpgll_struct );
	CalcPainGPGLL( &gpgll_struct );
}
/* GPGLL struct store function */
char StoreGPGLL( str_GPGLL *struction )
{
	unsigned char count_cmooa = 0;
	unsigned char cursor = 0;
	unsigned char i;
	while( Buffer_Remessage[cursor] != '*' ){
		if( Buffer_Remessage[cursor] != ',' ){
			switch( count_cmooa ){
				case 0: for(i=0;i<6;i++){ struction->MessageID[i] = Buffer_Remessage[cursor++];}break;
				case 1: for(i=0;i<10;i++){ struction->Latitude[i] = Buffer_Remessage[cursor++];}break;
				case 2: struction->NSIndicator = Buffer_Remessage[cursor++];break;
				case 3: for(i=0;i<11;i++){ struction->Longitude[i] = Buffer_Remessage[cursor++];}break;
				case 4: struction->EWIndicator = Buffer_Remessage[cursor++];break;
				case 5: for(i=0;i<9;i++){ struction->UTCTime[i] = Buffer_Remessage[cursor++];}break;
				case 6: struction->Status = Buffer_Remessage[cursor++];break;
				case 7: struction->Mode = Buffer_Remessage[cursor++];break;
			}
		}
		else{
		  count_cmooa += 1;
			cursor += 1;
	  }
  }
	struction->PointStatus = Buffer_Remessage[cursor++];
	struction->Checksum[0] = Buffer_Remessage[cursor++];
	struction->Checksum[1] = Buffer_Remessage[cursor];

  
	return 0;
}
/* calcultion and painting GLL */
int CalcPainGPGLL( str_GPGLL *struction )
{
	volatile float longi_now, lati_now;
	volatile float longi_last, lati_last;
	longi_now = *(TranStrToFloat( struction->Longitude, 3 )) + ( *(TranStrToFloat( &(struction->Longitude[6]), 5))/100000 + *(TranStrToFloat( &(struction->Longitude[3]), 2)))/60;
	lati_now = *(TranStrToFloat( struction->Latitude, 2 )) + ( *(TranStrToFloat( &(struction->Latitude[2]),2)) + *(TranStrToFloat( &(struction->Latitude[5]), 5))/100000 )/60; 
	return 0;
}

