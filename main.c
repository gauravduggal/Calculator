/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    26-December-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_io.h"
#include "stm32f429i_discovery_gyroscope.h"
#include "string.h"
#include "stdlib.h"
#define box_edge_d 10
#define box_box_d 5
#define box_size 50
#define LCD_H 240
#define LCD_V 320

/* Size of Transmission buffer */
#define TXBUFFERSIZE                     (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                     TXBUFFERSIZE

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

TS_StateTypeDef TsState;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling **** ";

/* Buffer used for reception */
uint8_t aRxBuffer[100];
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to 180 MHz */
  SystemClock_Config();

 
  /* Add your application code here
     */
BSP_GYRO_Init();
BSP_LED_Init(LED3);	
while (TS_OK != BSP_TS_Init(LCD_H,LCD_V));
BSP_LCD_Init();
BSP_LCD_LayerDefaultInit(0, (uint32_t) LCD_FRAME_BUFFER);
BSP_LCD_SetLayerVisible(0, ENABLE);
BSP_LCD_SelectLayer(0);
BSP_LCD_Clear(LCD_COLOR_BLUE);
BSP_LCD_DisplayOn();
//Initialising Layout of calculator  
BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-box_size,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+box_size+box_box_d,LCD_V-box_edge_d-box_size,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+2*(box_size+box_box_d),LCD_V-box_edge_d-box_size,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+3*(box_size+box_box_d),LCD_V-box_edge_d-box_size,box_size,box_size);

BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-2*box_size-box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+box_size+box_box_d,LCD_V-box_edge_d-2*box_size-box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+2*(box_size+box_box_d),LCD_V-box_edge_d-2*box_size-box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+3*(box_size+box_box_d),LCD_V-box_edge_d-2*box_size-box_box_d,box_size,box_size);

BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-3*box_size-2*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+box_size+box_box_d,LCD_V-box_edge_d-3*box_size-2*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+2*(box_size+box_box_d),LCD_V-box_edge_d-3*box_size-2*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+3*(box_size+box_box_d),LCD_V-box_edge_d-3*box_size-2*box_box_d,box_size,box_size);

BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-4*box_size-3*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+box_size+box_box_d,LCD_V-box_edge_d-4*box_size-3*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+2*(box_size+box_box_d),LCD_V-box_edge_d-4*box_size-3*box_box_d,box_size,box_size);
BSP_LCD_FillRect(box_edge_d+3*(box_size+box_box_d),LCD_V-box_edge_d-4*box_size-3*box_box_d,box_size,box_size);

BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-5*box_size-9*box_box_d,4*box_size+3*box_box_d,1.5*box_size);

BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
BSP_LCD_DisplayStringAt(25, 270, "1", LEFT_MODE);
BSP_LCD_DisplayStringAt(80, 270, "2", LEFT_MODE);
BSP_LCD_DisplayStringAt(135, 270, "3", LEFT_MODE);
BSP_LCD_DisplayStringAt(190, 270, "*", LEFT_MODE);

BSP_LCD_DisplayStringAt(25, 215, "4", LEFT_MODE);
BSP_LCD_DisplayStringAt(80, 215, "5", LEFT_MODE);
BSP_LCD_DisplayStringAt(135, 215, "6", LEFT_MODE);
BSP_LCD_DisplayStringAt(190, 215, "+", LEFT_MODE);

BSP_LCD_DisplayStringAt(25, 160, "7", LEFT_MODE);
BSP_LCD_DisplayStringAt(80, 160, "8", LEFT_MODE);
BSP_LCD_DisplayStringAt(135,160, "9", LEFT_MODE);
BSP_LCD_DisplayStringAt(190,160, "/", LEFT_MODE);

BSP_LCD_DisplayStringAt(25,105, "0", LEFT_MODE);
BSP_LCD_DisplayStringAt(80,105, ".", LEFT_MODE);
BSP_LCD_DisplayStringAt(135,105, "=", LEFT_MODE);
BSP_LCD_DisplayStringAt(190,105, "-", LEFT_MODE);


char temp = 0;
char buf[20];
uint8_t buf_ctr = 0;
uint8_t number_flag = 0;
float number1 = 0;
float number2 = 0;
float result = 0;
char op;
float pfData[3];
/* Infinite loop */
while (1)
{
		//Reading Gyro
		BSP_GYRO_GetXYZ(pfData);
		if (pfData[0]>100000.0)
		{
			
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_FillRect(box_edge_d,LCD_V-box_edge_d-5*box_size-9*box_box_d,4*box_size+3*box_box_d,1.5*box_size);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

			buf_ctr = 0;
			number_flag = 0;
		}
		BSP_TS_GetState(&TsState);
		if (TsState.TouchDetected)
		{
			uint16_t x = TsState.X;
			uint16_t y = TsState.Y;
			//Number 1 detected
			if (x>10 & x < 60 & y<310 & y >260)
			temp = '1';
			//Number 2 detected
			if (x>65 & x < 125 & y<310 & y >260)
			temp = '2';
			//Number 3 detected
			if (x>120 & x<170 & y<310 & y>260)
			temp = '3';
			//Number 4 detected
			if (x>10 & x<60 & y<255 & y>205)
			temp = '4';
			//Number 5 detected
			if (x>65 & x<125 & y<255 & y>205)
			temp = '5';
			//Number 6 detected
			if (x>120 & x<170 & y<255 & y>205)
			temp = '6';
			//Number 7 detected
			if (x>10 & x<60 & y<200 & y>150)
			temp = '7';
			//Number 8 detected
			if (x>65 & x<125 & y<200 & y>150)
			temp = '8';
			//Number 9 detected
			if (x>120 & x<170 & y<200 & y>150)
			temp = '9';
			//Number 0 detected
			if (x>10 & x < 60 & y<145 & y >95)
			temp = '0';
			//.
			if (x>65 & x <115 & y<145 & y >95)
			temp = '.';
			
			
			//*
			if (x>175 & x<225 & y<310 & y>260)
			{
			temp = '*';
			BSP_LCD_DisplayStringAt(190,25,"*", LEFT_MODE);
			}
			//+
			if (x>175 & x<225 & y<255 & y>205)
			{
				temp = '+';
				BSP_LCD_DisplayStringAt(190,25,"+", LEFT_MODE);
			
			}
				///
			if (x>175 & x<225 & y<200 & y>150)
			{
				BSP_LCD_DisplayStringAt(190,25,"/", LEFT_MODE);
				temp = '/';
			}
			//-
			if (x>175 & x<225 & y<145 & y>95)
			{
				temp = '-';
				BSP_LCD_DisplayStringAt(190,25,"-", LEFT_MODE);
			
			}
			//=
			if (x>120 & x<170 & y<145 & y>95)
			{
				BSP_LCD_DisplayStringAt(190,25,"=", LEFT_MODE);
				temp = '=';
			}
			if (((temp >= '0') & (temp <= '9')) | (temp == '.'))
			{
			buf[buf_ctr++] = temp;
			while (buf_ctr>9)
			{
			BSP_LCD_DisplayStringAt(10,25,"          ", LEFT_MODE);	
			BSP_LCD_DisplayStringAt(10,25,"ER:<10dig", LEFT_MODE);
			HAL_Delay(1000);
			}
			char disp[10];
			int i = 0;
			for (i = 0; i < buf_ctr; i++)
				{
					disp[i] = buf[i];
				}
			disp[i] = '\0';
			BSP_LCD_DisplayStringAt(10,25,"          ", LEFT_MODE);	
			BSP_LCD_DisplayStringAt(10,25, disp, LEFT_MODE);
			}
			else
			{
				buf[buf_ctr++] = '\0';
				buf_ctr = 0;
				
				if (number_flag == 0)
				{
					number1 = atof(buf);
					number_flag = 1;
					op = temp;
				}
				if (number_flag == 1 & temp == '=')
				{
					number2 = atof(buf);
					number_flag = 0;
					
				if (op == '*')
				{
					result = number1*number2;
				}
				if (op == '/')
				{
					result = number1/number2;
				}
				if (op == '-')
				{
					result = number1-number2;
				}
				if (op == '+')
				{
					result = number1+number2;
				}
				char str[15];
				sprintf(str,"%.2f",result);
				while(strlen(str)>12)
				{
					BSP_LCD_DisplayStringAt(10,25,"          ", LEFT_MODE);	
					BSP_LCD_DisplayStringAt(10,25,"ER:>12dig", LEFT_MODE);
					HAL_Delay(1000);
				}
				//sprintf(str,"%d",strlen(str));
				int i=0;
				int j = strlen(str);
				for(;i<j; i++)
				{
					BSP_LCD_DisplayChar(200-18*i, 55, str[j-i-1]);
				}
				
				}
			
			}
		
		}
	
	
		//Debouncing	
		while(TsState.TouchDetected)
		{
			BSP_TS_GetState(&TsState);
			HAL_Delay(200);
		}
		
  
}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  //__HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /*
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    
    Error_Handler();
  }
  */
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
		BSP_LED_On(LED3);
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
