/*
** This file include a class of store function also consist of dynamic memorry allocation
** Author:Moonyong 
** Date: 8/30/2013 */
#include <stdlib.h>
#include "stm32f10x.h"

/* record screen coord 
** parameter1: x coord 
** parameter2: y coord  
** return: CountCoordAmount/ERROR/ */
 
u16 CountCoordAmount;  // count how many x and y coord in the RAM now;
int record_screen_coord( __RecordScrCoo *Current, lcda16 Xcoord, lcda8 Ycoord )
{	
	__RecordScrCoo *newnode;
	
	while( Current->link != NULL ){                    // find a null node
		Current = Current->link;
	}
	newnode = ( __RecordScrCoo* )malloc( sizeof( __RecordScrCoo ) );
	if( newnode == NULL )
		return ERROR;
	newnode->Xcoord = Xcoord;
	newnode->Ycoord = Ycoord;
	Current->link = newnode;
	CountCoordAmount += 1;
	return CountCoordAmount;
}

