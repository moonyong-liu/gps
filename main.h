#ifndef __main_h
#define __main_h

#include "stm32f10x.h"
// S_T_I_TYPE is "string to integer" type define
#define  S_T_I_TYPE   unsigned long
#define  DISTANCE_PARTMETER    30
#define  BASE_X 159   // 原点X值
#define  BASE_Y 119   // 原点Y值
typedef unsigned char GPSU8;
typedef unsigned int GPSU32;
int *StrToInt( const GPSU8 *string,unsigned char i );
void Print_lati_longi(void);
void Convert_UTCto8(void);
void GPRMC(void);


#endif /*__main_h*/

