/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */


/* Define to prevent recursive inclusion ----------------------------------- */
#ifndef __GPS_H__
#define __GPS_H__

/* Includes ---------------------------------------------------------------- */
/* Exported types ---------------------------------------------------------- */

typedef struct type_GPS_dat
{
	unsigned char	status;
	unsigned char	lat_ew;
	unsigned char	latitude[11];
	unsigned char	long_ns;
	unsigned char	longitude[12];
	unsigned char	altitude[6];
	unsigned char	date[7];
	unsigned char	time[11];
	unsigned char	satellites[3];
	unsigned char	satellites_inview[3];
	unsigned char	satellites_id[3];
	unsigned char	speed;
	//int		direction;
	float			hdop;
}t_GPS_data;

/* Exported constants ------------------------------------------------------ */
/* Exported macro ---------------------------------------------------------- */
/* Exported variables ------------------------------------------------------ */
extern unsigned char GPS_keyword[5];
extern unsigned char GPS_data_buff[80];
extern unsigned char *p_GPS_data_buff;
extern unsigned char *p_GPS_keyword;

extern t_GPS_data GPS_data;

extern unsigned char flag_GPS_data_updated;
extern unsigned char flag_GPS_data_processed;

/* Exported functions ------------------------------------------------------ */

void GPS_Test(void);

#endif

// �ȶ�����д:
#define        UCHAR unsigned char
#define        UINT unsigned int
#define		   xdata unsigned char

//�������ݽṹ, GPRMC ������ܽ���������
typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
        UCHAR UTCTime[10];        //hhmmss.mmm
        UCHAR Status;         //A- ��Ч��λ V-��Ч��λ
        UCHAR Latitude[9];        //ddmm.mmmm
        UCHAR NS;                //N/S
        UCHAR Longitude[10];        //dddmm.mmmm
        UCHAR EW;                //E/W
        UCHAR Speed[5];        //����000.0~999.9��
        UCHAR Course[5];        //����000.0~359.9��
        UCHAR UTCDate[6];        //ddmmyy
}stru_GPSRMC;

typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
//        UCHAR UTCTime[10];        //hhmmss.mmm RMC������, ���Բ�����
//        UCHAR Latitude[9];        //ddmm.mmmm
//        UCHAR NS;                //N/S
//        UCHAR Longitude[10];        //dddmm.mmmm
//        UCHAR EW;                //E/W
        UCHAR PositionFix;        //0,1,2,6
        UCHAR SateUsed[2];        //00~12
//        UCHAR HDOP[4];                //0.5~99.9
        UCHAR Altitude[7];        //-9999.9~99999.9
}stru_GPSGGA;

typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
        UCHAR Mode;        //A-�Զ� /M-�ֶ�
        UCHAR Mode2;        //0,1,2,3
        UCHAR SateUsed[12][2];         
        UCHAR PDOP[4];
        UCHAR HDOP[4];
        UCHAR VDOP[4];
}stru_GPSGSA;

typedef struct
{
        UCHAR SatelliteID[2];//���Ǳ��
//        UCHAR Elevation[2]; //0-90 degree //����ʾGPS���ǵķ�λͼ, ���Բ�����, ��ʡ 5*12 RAM
//        UCHAR Azimuth[3];        //0-359 degree//��Ҫ����ʱȥ��ע��'//'�ͽ���ǰ��'//'����
        UCHAR SNR[2];        //0-99 dbHz
}stru_SatelliteInfo;

typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
        UCHAR SateInView[2];
        UCHAR GSVID;//��ǰ GSV�����
        stru_SatelliteInfo SatelliteInfo[12];
}stru_GPSGSV;

//--------------------------------------------------------------
#define GPS_NULL     0x00                        //GPS�������
#define GPS_GPGGA    0x01
#define GPS_GPGSA    0x02
#define GPS_GPGSV    0x04
#define GPS_GPRMC    0x08
UCHAR    GPSDataType=GPS_NULL;                //GPS�������
UCHAR    GPSDataTypeStrBuff[]="$GPxxx,";        //GPS������ͻ���, �ж�����ʱʹ��,
UCHAR    GPSDataTypeStrBuffIndex=0;                //GPS��������ַ����ĵ�ǰλ��

UCHAR  MainDateTime[]="00/00/00 00:00:00\0";        //����ʱ��
UCHAR  MainDateTimeShort[]="00/00 00:00:00\0";        //����ʱ��
UCHAR  MainLatitude[]="N dd'mm'ss.ssss\"\0";        //γ��
UCHAR  MainLongitude[]="Eddd'mm'ss.ssss\"\0";        //����



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
