/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name     : tutorial_main.c
* Version       : 1.0
* Device(s)     : RX63N
* Tool-Chain    : Renesas RX Standard Toolchain 1.0.0
* H/W Platform  : YRDKRX63N
* Description   : This tutorial sample will demonstrate basic use of the YRDK
*                 hardware and the J-Link debugger. 
* Operation     : 1.  Build and download the tutorial project to the YRDK.
*
*                 2.  Click 'Reset Go' to start the software.
*         
*                 3.  "Renesas RX63N" will be displayed on the debug LCD,
*                     and the user LEDs will flash.
*          
*                 4.  The user LEDs will flash at a fixed rate until either a
*                     switch is pressed, or the LEDs have flashed 200 times.
*          
*                 5.  The software will then vary the rate in which the LEDs flash
*                     by the position of the potentiometer, VR1. Turn the pot in
*                     both directions, and observe the change in flash rate.
*          
*                 6.  While the LEDs flash at a varying rate, the second line of
*                     the debug LCD will show " STATIC ". The second LCD line will
*                     slowly be replaced, letter by letter, with the string 
*                     "TEST TEST".
*          
*                 7.  Once the second line of the debug LCD shows "TEST TEST"
*                     fully, it will return back to showing "RX63N". The LEDs will
*                     continue to flash at a varying rate until the tutorial is
*                     stopped.
*          
*                 8.  In order to repeat the tutorial, click 'Reset Go'.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 24.02.2012     1.00        First release              
*******************************************************************************/

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "platform.h" 
#include "r_switches.h"
#include "cmt_periodic_multi.h"
#include "timer_adc.h"
#include "flash_led.h"
#include "customADC.h"

/*******************************************************************************
Macro Definitions
*******************************************************************************/
#define TIMER_COUNT_600MS 56250  /* 600mS with 48MHz pclk/512 */
#define MCU_NAME "   RX    "
#define CHANNEL_0   0
#define		AN3  0x0008
#define		AN2  0x0004

/*******************************************************************************
External functions and public global variables. 
*******************************************************************************/
/* Statics test replacement variable */
uint8_t g_working_string[13] = "   STATIC   "; /* 12 characters plus NULL terminator. */

/* Statics test const variable */
const uint8_t g_replacement_str[] = "TEST TEST"; /* Must be 12 chars or less. */

volatile bool g_sw1_press = false;
volatile bool g_sw2_press = false;
volatile bool g_sw3_press = false;


/*******************************************************************************
Private function prototypes and global variables
*******************************************************************************/
static void statics_test(void);
static void timer_callback(void);
void osci(void);
void voldisplay(void);
volatile static bool g_delay_complete = false;
void osci1(void);
void osci2(void);
//int flag=0;
int column_array[96];
int i=0;
char stringa[30];
char stringb[30];
char stringc[30];
float adc_val,mv2;
int pause_status=1;
volatile bool toggle=false;
volatile bool flag1=false;
int k,j= -1,h,l=0;
/******************************************************************************
* Function name: main
* Description  : Main program function. The function first initialises the debug
*                LCD, and displays the splash screen on the LCD. The function
*                then calls the flash_led, timer_adc and statics_test functions. 
*                These start by flashing the LEDs at a fixed rate until a switch is
*                pressed, then the flash rate varies with the position of the   
*                pot, RV1. Finally, statics_test displays " STATICS " on the    
*                debug LCD, which is replaced with "TEST TEST" a letter at a 
*                time.
* Arguments    : none
* Return value : none
******************************************************************************/
void main(void)
{
	
	
    int a;
	/* Initialize the debug LCD on the RSPI bus. */
    lcd_initialize();
    
    /* Clear LCD */
    lcd_clear();
    
     

    R_SWITCHES_Init(); /* Prepare the board switches for use. */
    
	adcInit();
    /* Executes the initial LED flashing sequence */
    //flash_led();  
	initUART(4999,1,1,2);    
	cmt_init();					/* Initialize the CMT unit for application timing tasks. */
	cmt_callback_set(0,osci);	/* call back set for 1st CMT interrupt. */
	cmt_callback_set(1,osci1);	/* call back set for 2nd CMT interrupt. */
	cmt_start(0,1000);			/* Starting 1st CMT. */
	for(int f=0;f<96;f++)
	{
		column_array[f]=0;		/* Initializing the column array with zero to avoid junk values. */
	}	

    while (1)
    {
      
    }
} /* End of function main(). */
/******************************************************************************
* Function name: osci
* Description  : To display the signal when 1st switch is pressed and to display
				 the ADC value from external channel when third switch is .The 
				 switching between two switch press is using variable toggle1.
* Arguments    : none
* Return value : none
******************************************************************************/
void osci(void)
{		
		int ycord,refv,v,adcresult,resultinmv;
		int res,k;
		int m;	
		if(flag1==false)
		{
			if(toggle==false)
			{	
				Clear_Screen();
				adcRead(AN2);
				h = S12AD.ADDR2;
				res=h/60;		
				res=68-res;
				i++;
				column_array[i]=res;
				for(int k=95;k>0;k--)
				{
					column_array[k]=column_array[k-1];	/* Shifting the newly read values */
				}
				if(i==94)
				{		
					for(int k=0;k<96;k++)
					{
			  	 			m=column_array[k];			/* Positioning the voltage value and pring on screen */
				 			LCD_Set_Pixel(k,m);	
				 			Set_Font_Bitmap();
				 			Set_LCD_Pos(0,5);
				 			Set_LCD_Char(0);
					}	
				}
			}
			else if(toggle==true)
			{
					Clear_Screen();
					voldisplay();					/* For displaying the voltage value and voltage signal simultaneously on screen*/
					i++;
					if(i==95)
					i=0;	
					adcRead(AN2);
					h = S12AD.ADDR2;						
					res=h/60;		
					res=68-res;
					column_array[i]=res;
						for(int k=0;k<96;k++)
						{
				 				m=column_array[k];/* positioning and displaying the voltage signal */
				 				LCD_Set_Pixel(k,m);	
				 				Set_Font_Bitmap();
				 				Set_LCD_Pos(0,5);
				 				Set_LCD_Char(0);
						}	
			}
		}
		else if(flag1==true)
		{
			for(int i=0;i<1000000;i++)
			;
			lcd_clear();
			Set_Font_8_by_8();
			lcd_display(LCD_LINE2, "  ADC   ");			/* Reading and displaying the ADC value from external channel*/
			adcRead(AN3);
			h = S12AD.ADDR3;
			mv2=convertADC(h);		
			sprintf(stringc,"%f",mv2);
			lcd_display(LCD_LINE3,stringc);
		}	
					
}
 /*******************************************************************************
* Function name: osci1
* Description  : The CMT interrupt 2,which transmits the voltage value through UART to PC
*                at baud rate of 9600.
* Arguments    : none
* Return value : none
*******************************************************************************/
void osci1(void)
{
	int adcval;
	float mv;
	lcd_clear();
	Set_Font_8_by_8();
	lcd_display(LCD_LINE1, "  UART   ");		
	adcRead(AN2);						/* Reading ADC value from channel 2. */
	adcval = S12AD.ADDR2;
	mv=convertADC(adcval);
	sprintf(stringb, "%f", mv);
	lcd_display(LCD_LINE4, stringb );			
	j++;
	if(j==4)
	j=-1;
	tx_UART(stringb[j]);				/* Transmitting the values through UART to PC */
}


 /*******************************************************************************
* Function name: statics_test
* Description  : Static variable test routine. The function replaces the
*                contents of the string g_working_string with that of g_replacement_str, one
*                element at a time. Right-click the variable g_working_string, and select
*                instant watch - click add in the subsequent dialog. If you step
*                through the function, you can watch the string elements being
*                overwritten with the new data.
* Arguments    : none
* Return value : none
*******************************************************************************/
void statics_test(void)
{
    /* Declare loop count variable */
    uint8_t loop_counter;

    /* Write the initial contents of g_working_string to the debug LCD */
    lcd_display(LCD_LINE2, g_working_string);

    /* Set up the callback function on cmt channel 0 */   
    cmt_callback_set(CHANNEL_0, &timer_callback);
    
    /* Replace each element of g_working_string in each loop iteration with the contents 
       of g_replacement_str */
    for (loop_counter = 0; loop_counter < strlen((char*)g_replacement_str); loop_counter++)
    {
        /* Replace character from g_working_string with characer from g_replacement_str */
        g_working_string[loop_counter] = g_replacement_str[loop_counter];

        /* Write current contents of g_working_string to the debug LCD */
        lcd_display(LCD_LINE2, g_working_string);
   
        g_delay_complete = false; /* Clear this flag variable. */
        
        /* Use a timer to create the delay between each loop iteration */         
        cmt_start(CHANNEL_0, TIMER_COUNT_600MS); /* 600mS period. */
        
        while(!g_delay_complete)
        {
            /* wait until the delay has completed. */
        }               
    }

    /* Revert the debug LCD back to displaying the MCU_NAME */    
    lcd_display(LCD_LINE2, MCU_NAME);
    
} /* End of function statics_test(). */


/******************************************************************************
* Function name: timer_callback
* Description  : This function is called from the cmt_timer compare-match ISR.
*              : It sets a global flag that is polled for delay loop control.
* Arguments    : None
* Return value : None
******************************************************************************/
void timer_callback(void)
{

    g_delay_complete = true;
    
} /* End of function timer_callback() */



/******************************************************************************
* Function name: sw1_callback
* Description  : Callback function that is executed when SW1 is pressed.
*                Called by sw1_isr in r_switches.c
* Arguments    : none
* Return value : none
******************************************************************************/
void sw1_callback(void)
{
	for(int i=0;i<1000000;i++)	;	
		toggle=!toggle;				
		printf("%d\n",toggle);
		cmt_stop(1);				/* Stopping channel 1 */
		cmt_start(0,1000);			/* and starting channel 0. */	
							 /* The switch was pressed. */
} /* End of function sw1_callback() */


/******************************************************************************
* Function name: sw2_callback
* Description  : Callback function that is executed when SW2 is pressed.
*                Called by sw2_isr in r_switches.c
* Arguments    : none
* Return value : none
******************************************************************************/
void sw2_callback(void)
{
	for(int i=0;i<1000000;i++)	;
	cmt_stop(0);				/* Stopping channel 0 */
	cmt_start(1,6000);			/* and starting channel 1 */
    					/* The switch was pressed. */
} /* End of function sw2_callback() */


/******************************************************************************
* Function name: sw3_callback
* Description  : Callback function that is executed when SW3 is pressed.
*                Called by sw3_isr in r_switches.c
* Arguments    : none
* Return value : none
******************************************************************************/
void sw3_callback(void)
{
	for(int i=0;i<1000000;i++)	;
	flag1=!flag1;
	printf("%d\n",flag1);
						 /* The switch was pressed. */
} /* End of function sw3_callback() */
void voldisplay(void)
{
	int s;
	float mv1;
	Set_Font_8_by_8();		
	adcRead(AN2);
	s = S12AD.ADDR2;
	mv1=convertADC(s);
	sprintf(stringa, "%f", mv1);		/* To display voltage value on screen */
	lcd_display(LCD_LINE1, stringa);
}	