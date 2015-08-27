/*
** store.c head file
** author moonyong
** date 9/17/2013 */
#include "stm32f10x.h"

/*
** LCD sotore coord`s length 8 bit 16 bit 32 bit */
typedef unsigned char  lcda8;   
typedef unsigned short lcda16;  
typedef unsigned int   lcda32;

/*
** store LCD coord by two variables, 8bit = 256 points > lcd y-axis 
   16bit = 65536 pints > lcd x-axis */
typedef struct __recordscrcoo
{
	struct __recordscrcoo *link;
	lcda16 Xcoord;    
	lcda8  Ycoord;
	
} __RecordScrCoo;


int record_screen_coord( __RecordScrCoo*, lcda16, lcda8 );

