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

// 先定义缩写:
#define        UCHAR unsigned char
#define        UINT unsigned int
#define		   xdata unsigned char

//定义数据结构, GPRMC 语句中能解析的数据
typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
        UCHAR UTCTime[10];        //hhmmss.mmm
        UCHAR Status;         //A- 有效定位 V-无效定位
        UCHAR Latitude[9];        //ddmm.mmmm
        UCHAR NS;                //N/S
        UCHAR Longitude[10];        //dddmm.mmmm
        UCHAR EW;                //E/W
        UCHAR Speed[5];        //速率000.0~999.9节
        UCHAR Course[5];        //航向000.0~359.9度
        UCHAR UTCDate[6];        //ddmmyy
}stru_GPSRMC;

typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
//        UCHAR UTCTime[10];        //hhmmss.mmm RMC中已有, 所以不解析
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
        UCHAR Mode;        //A-自动 /M-手动
        UCHAR Mode2;        //0,1,2,3
        UCHAR SateUsed[12][2];         
        UCHAR PDOP[4];
        UCHAR HDOP[4];
        UCHAR VDOP[4];
}stru_GPSGSA;

typedef struct
{
        UCHAR SatelliteID[2];//卫星编号
//        UCHAR Elevation[2]; //0-90 degree //不显示GPS卫星的方位图, 所以不解析, 节省 5*12 RAM
//        UCHAR Azimuth[3];        //0-359 degree//需要解析时去除注释'//'和解析前的'//'即可
        UCHAR SNR[2];        //0-99 dbHz
}stru_SatelliteInfo;

typedef struct
{
        UCHAR Block;
        UCHAR BlockIndex;
        UCHAR SateInView[2];
        UCHAR GSVID;//当前 GSV语句编号
        stru_SatelliteInfo SatelliteInfo[12];
}stru_GPSGSV;

//--------------------------------------------------------------
#define GPS_NULL     0x00                        //GPS语句类型
#define GPS_GPGGA    0x01
#define GPS_GPGSA    0x02
#define GPS_GPGSV    0x04
#define GPS_GPRMC    0x08
UCHAR    GPSDataType=GPS_NULL;                //GPS语句类型
UCHAR    GPSDataTypeStrBuff[]="$GPxxx,";        //GPS语句类型缓存, 判断类型时使用,
UCHAR    GPSDataTypeStrBuffIndex=0;                //GPS语句类型字符串的当前位置

UCHAR  MainDateTime[]="00/00/00 00:00:00\0";        //日期时间
UCHAR  MainDateTimeShort[]="00/00 00:00:00\0";        //日期时间
UCHAR  MainLatitude[]="N dd'mm'ss.ssss\"\0";        //纬度
UCHAR  MainLongitude[]="Eddd'mm'ss.ssss\"\0";        //经度



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
