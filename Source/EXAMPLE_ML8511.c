/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: ML8511 UV light sensor
     File Name		: EXAMPLE_ML8511.c
     Function		: EXAMPLE_ML8511
     Create Date	: 2017/12/31
---------------------------------------------------------------------- */

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include "alcd.h"
#include "SENSOR_ML8511.h"

void EXAMPLE_ML8511(void);


/* This input use ADC channel */
void EXAMPLE_ML8511(void)
{
          
	FLOAT ml8511_raw_data=0.0, uv_data=0.0;
	FLOAT get_data=uv_data;	
	INT32U data[3]={0};
	CHAR8U lcd_char_data[5]={0};

	
		printf("--------------------UV light sensor ML8511 --------------------\r\n");

		/* initial EN pin IO */
		ML8511_INIT();

		while(1)
		{
				
			/* Read ADC value */
			ML8511_GET_RAW_DATA(&ml8511_raw_data);

			/* Calculate The UV value */
			ML8511_GET_UV_VALUE(ml8511_raw_data,&uv_data);

			/* print the UV data */
			data[0]= (INT32U)(uv_data);
			data[1]= (INT32U)(uv_data*10) %10;   
			data[2]= (INT32U)(uv_data*100) %10;   	  				
			printf("ML8511 UV Level = %d.%d%d UV mW/cm2\r\n",data[0],data[1],data[2]);	/*unit: mW/cm2 */


			lcd_char_data[0] = (CHAR8U)(uv_data/100)%10;     
			lcd_char_data[1] = (CHAR8U)(uv_data/10)%10;
			lcd_char_data[2] = (CHAR8U)(uv_data)%10;  
			lcd_char_data[3] = (CHAR8U)(uv_data*10)%10;   
			lcd_char_data[4] = (CHAR8U)(uv_data*100)%10;   	  


			/* show data */
			lcd_gotoxy(0,0);
			lcd_putsf("UV:");
				  
			lcd_putchar(48+lcd_char_data[0]);
			lcd_putchar(48+lcd_char_data[1]);
			lcd_putchar(48+lcd_char_data[2]); 
			lcd_putchar(46);    /* print "."  */ 
			lcd_putchar(48+lcd_char_data[3]);  
			lcd_putchar(48+lcd_char_data[4]); 

			/* show unit */
			lcd_gotoxy(5,1);
			lcd_putsf("mW/cm2");	/*unit: mW/cm2 */

			/*Show IC ID */
			lcd_gotoxy(0,2);
			lcd_putsf("ML8511");	

				  
			delay_ms(300); /* tiny delay */
		}


		printf("-------------------- UV light sensor ML8511 --------------------\r\n");
}

