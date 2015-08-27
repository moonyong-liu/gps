#ifndef __gps_h
#define __gps_h

#include "stm32f10x.h"

/* struct of GPRMC */
typedef struct  
{
	unsigned char MessageID[6];
	unsigned char UTCTime[9];					// hhmmss.sss
	unsigned char Status;								// V=Navigation receiver warning, A=valid
	unsigned char Latitude[10];					// ddmm.mmmm
	unsigned char NSIndicator;					// north or south
	unsigned char Longitude[11];				// dddmm.mmmm
	unsigned char EWIndicator;					// east or west
	unsigned char Speed[5];             // Speed over ground
	unsigned char Course[5];						// Course over ground
	unsigned char Data[6];							// day, month, year 
	unsigned char Mode; 								// 
	unsigned char PointStatus;          // one * indicate full message over
	unsigned char Checksum[2];							// hexadecimal
	
} str_GPRMC;
/* struct of GPGLL */

typedef struct
{
	unsigned char MessageID[6];
	unsigned char Latitude[10];  // ddmm.mmmmm
	unsigned char NSIndicator;		// N/S indicator 
	unsigned char Longitude[11];			// dddmm.mmmmm
	unsigned char EWIndicator;		// E/W indicator
	unsigned char UTCTime[9];			// hhmmss.ss UTC time current time
	unsigned char Status; 				// V = data invalid of receiver warning, A = data valid
	unsigned char Mode; 					// positioning mode
	unsigned char PointStatus;		// a  *
	unsigned char Checksum[2];		// hexadecimal , checksum
} str_GPGLL;

void CodeStart(void);
void FactoryReset(void);
void HotStart(void);
void WarmStart(void);
void MessageSet(void);
void store_gprmc( str_GPRMC *struction );
int *WalkWalkPoint(void);

float *TranStrToFloat( const u8 *str, unsigned char quantity );
char StoreGPGLL( str_GPGLL *struction );   
void ShowGPGLL(void);
int CalcPainGPGLL( str_GPGLL *struction );
int *TranStrToInt( const u8 *str, unsigned char quantity );
str_GPRMC *SendStruct(void);
uint8_t free_space( __RecordScrCoo* );


#endif /*__gps_h*/

