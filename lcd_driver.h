#include "stm32f10x.h"

#define uint unsigned int
#define uchar unsigned char
#define U16 unsigned short


#define   BLACK		0x0000      /* 黑色：    0,   0,   0 */
#define   WHITE		0xFFFF      /* 白色：  255, 255, 255 */
#define   DGRAY		0x8410    	/* 深灰色：128, 128, 128 */
#define   LGRAY		0xEF5b	    /* 灰白色：192, 192, 192 */
#define   MAROON	0x8000		/* 深红色：128,   0,   0 */
#define   RED		0xF800		/* 红色：  255,   0,   0 */
#define   OLIVE		0x8400 	    /* 橄榄绿：128, 128,   0 */
#define   YELLOW	0xFFE0		/* 黄色：  255, 255, 0   */
#define   DGREEN	0X0480		/* 深绿色：  0, 128,   0 */
#define   GREEN		0x07E0		/* 绿色：    0, 255,   0 */
#define   DCYAN		0x0410		/* 深青色：  0, 128, 128 */
#define   CYAN	    0x07FF 		/* 青色：    0, 255, 255 */
#define   NAVY		0x0011      /* 深蓝色：  0,   0, 128 */
#define   BLUE		0x001F		/* 蓝色：    0,   0, 255 */
#define   PURPLE	0x8010		/* 紫色：  128,   0, 128 */
#define   MAGENTA	0xF81F		/* 品红：  255,   0, 255 */

#define   COL_A    	0x9492	   //  148,  144,   150  屏幕上显示字和图形的颜色 
#define   COL_B    	0x07BF	   //  0,  247,   255  桌面图标的背景颜色 
#define   COL_C		0x055D     //     0, 168, 236  屏幕软键背景色
#define   COL_D     0xA7FF     //显示框未被选种的颜色
#define   COL_E     0x6D5F     //SC2背景框兰色
#define   COL_F     0xFFE0	   //  255,  252,   0  菜单黄色 


#define CS_TFT_H()  GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define CS_TFT_L()  GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#define RS_TFT_H() GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define RS_TFT_L() GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define WR_TFT_H() GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define WR_TFT_L() GPIO_ResetBits(GPIOB,GPIO_Pin_2)

#define RD_TFT_H() GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define RD_TFT_L() GPIO_ResetBits(GPIOD,GPIO_Pin_2)


#define LCD_Light_ON() GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define LCD_Light_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_1)


#define  HZ_X   70
#define  HZ_Y	20

#define  KEY_X	8
#define  KEY_Y	285

#define  PIC_X	24
#define  PIC_Y	100

#define	 DEGREE  24
#define  MINUTE  44
#define  SECOND	 64

#define  DEGREE_Longi  122
#define  MINUTE_Longi  151
#define  SECOND_Longi  173

#define  UTC_H  203
#define  UTC_M  218
#define  UTC_S  232
 
extern void ili9320_Reset(void);
extern void LCD_Init(void);
extern void ili9320_WriteRegister(u16 index,u16 dat);
extern u16 ili9320_ReadRegister(u16 index);
extern u16 ili9320_ReadData(void);
extern void ili9320_WriteData(u16 data);
extern void ili9320_WriteIndex(u16 idx);
extern void ili9320_SetCursor(u16 x,u16 y);
extern void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
extern void ili9320_Clear(u16 dat);
extern void ili9320_Delay(vu32 nCount);
extern void LCD_Draw_Point(U16 x,U16 y,u16 colour);//在指定的坐标处画点函数
extern void LCD_DispBase(u16 x, u16 y, u16 w, u16 h,u16 colour, u8 const * address);
extern void Disp_Draw8X13(u32 x, u32 y,u16 colour, const u8 num); 
extern void Disp_PrintStr8X13(u32 x, u32 y,u16 colour, const u8 *cword);
extern void LCD_DrawHLine(u16 x, u16 y, u16 l,u16 colour);
extern void LCD_DrawLLine(U16 x, U16 y, u16 l,U16 colour);
extern void LCD_DrawRectbar(u16 x, u16 y, u16 w, u16 h,u16 colour);
extern void Draw_Bmp(u16 x,u16 y,u16 w,char *p);
extern void Disp_Draw24X24(u16 x, u16 y,u16 colour, u16 num);
extern void Disp_Draw12X12(u16 x, u16 y,u16 colour, u16 num);
extern void Disp_Draw4XLine_H(u16 x, u16 y, u8 w, u8 h);
extern void Disp_Draw4XLine_L(u16 x, u16 y, u8 w, u8 h);
extern void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
extern u16 LCD_RD_REG(u8 LCD_Reg);
extern void Disp_Draw7X12(u16 unit, u16 num, u8 lal);
void Refresh_Part( unsigned int bx, unsigned int by, unsigned int ex, unsigned int ey );

extern u8 const  Disp_TabFont8x13[];
extern u8 const  Disp_TabFont24x24[];
extern u8 const  Disp_TabFont12x12[];
extern u8 const  NumberLib7x12[];
void DrowWalkLine( u16, u16 );
void Refersh_need_position(void);
void InitMapInterface(void);
void PrintLatiLongi( str_GPRMC *struction );
void zoom_in( u16 buffer[100][2] );
void zoom_out( u16 buffer[100][2] );


