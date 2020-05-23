/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: ML8511 UV light sensor
     File Name		: SENSOR_ML8511.c
     Function		: SENSOR_ML8511
     Create Date	: 2017/12/31
---------------------------------------------------------------------- */


#include <stdio.h>
#include <math.h>
#include <delay.h>

#include "SENSOR_ML8511.h"

#define ML8511_DEBUG		1

/*** Note : ML8511 operation voltage -> 3.3V!*/
/*** read adc_data[0] -> ADC channel 0 -> PA_ 2 pin*/
extern unsigned int	adc_data[1];

/********************************************** SYSTEM **************************************************/
/*--------------------------------------------------------------------------------------------------*/
/* initial the IO pin to control ML8511 EN pin */
/* ML8511 EN pin : active high */
void ML8511_INIT(void)
{
	printf("ML8511_INIT initial \r\n");
	DDRB = (1<<0);  		/* SET PORTB.0*/
	PORTB.0=0;			/* SET low */	
}
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* read adc value & return ADC value ; note : adc -> 3V*/
void ML8511_GET_RAW_DATA(FLOAT *raw_data)
{
		
	#if ML8511_DEBUG	/* FOR DEBUG */
	INT32U data[3]={0};  
	#endif			
	
	FLOAT get_data=0.0,temp_data=0.0;	
	INT32U adc_raw_data=0;
	
		/* control ML8511 EN pin high[enable]  */
		PORTB.0=1;
		/* wait ML8511 stable */
		delay_ms(5);

		/*get adc sample */
		adc_raw_data=adc_data[0];
		temp_data=(FLOAT)adc_raw_data;
	
		/* control ML8511 EN pin low[disable] */
		PORTB.0=0;		
		delay_ms(5);		
		
		get_data =  temp_data/1023 *3.3 ;	/*3.3V*/		
		
	#if ML8511_DEBUG	/* FOR DEBUG */
		data[0]= (INT32U)(get_data);
	  	data[1]= (INT32U)(get_data*10) %10;   
	  	data[2]= (INT32U)(get_data*100) %10;   	  
		printf("ADC RAW DATA = %d \r\n",adc_raw_data);	 
		printf("ML8511 RAW DATA = %d.%d%d V\r\n",data[0],data[1],data[2]);	
	#endif	
	
		*raw_data =  get_data ;
		
}
/* --------------------------------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------------------------------*/
/*  calculate the raw data turn to UV Intensity */
void ML8511_GET_UV_VALUE(FLOAT raw_data,FLOAT *uv_data)
{ 

	#if ML8511_DEBUG	/* FOR DEBUG */
	INT32U data[3]={0};  
	#endif		
	
	FLOAT get_data=0.0,temp_data=0.0;

		if(raw_data<1) /* raw_data <1v */
		{
			get_data = 0;
		}
		else /* raw_data >1v */
		{
			get_data = 9.09*raw_data - 9.09 ;/* formula : x = 9.09y - 9.09 ; x-> UV  , y-> voltage */
		}
		
		*uv_data =  get_data ;

		#if ML8511_DEBUG	/* FOR DEBUG */
		data[0]= (INT32U)(get_data);
		  data[1]= (INT32U)(get_data*10) %10;   
		  data[2]= (INT32U)(get_data*100) %10;   	  
			 
		printf("ML8511 uv_data = %d.%d%d V\r\n",data[0],data[1],data[2]);	
		#endif	
	
}
/*--------------------------------------------------------------------------------------------------*/
/********************************************** SYSTEM **************************************************/

