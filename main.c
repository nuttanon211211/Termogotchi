/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Definitions for logic01 */
osThreadId_t logic01Handle;
const osThreadAttr_t logic01_attributes = {
  .name = "logic01",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for logic02 */
osThreadId_t logic02Handle;
const osThreadAttr_t logic02_attributes = {
  .name = "logic02",
  .priority = (osPriority_t) osPriorityBelowNormal7,
  .stack_size = 128 * 4
};
/* Definitions for logic03 */
osThreadId_t logic03Handle;
const osThreadAttr_t logic03_attributes = {
  .name = "logic03",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartLogic01(void *argument);
void StartLogic02(void *argument);
void StartLogic03(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Copyright (c) 2020 Nuttanon Muanphannarai.
   All rights reserved. */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of logic01 */
  logic01Handle = osThreadNew(StartLogic01, NULL, &logic01_attributes);

  /* creation of logic02 */
  logic02Handle = osThreadNew(StartLogic02, NULL, &logic02_attributes);

  /* creation of logic03 */
  logic03Handle = osThreadNew(StartLogic03, NULL, &logic03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
	int eat,play;
	int hp = 20;
	int count = 0;
	/* default : hp = 20,full = 300, happy = 300*/
	int happy = 300;
	int full = 300;
	int die = 0;
	char buf[30];
	char cat1[30] ="\t\t\t\t    ^      ^    \r\n";
	char cat2[30] ="\t\t\t\t   / \\    / \\   \r\n"   ;
	char cat3[30] ="\t\t\t\t  / A \\__/ A \\    \r\n"   ;
	char cat4[30] ="\t\t\t\t |            l \r\n"   ;
	char cat5[30] ="\t\t\t\t == <O> <O>  == \r\n"   ;
	char cat6[30] ="\t\t\t\t ==    Y     == \r\n"   ;
	char cat7[30] ="\t\t\t\t  \\   VV    / \r\n"   ;
	char cat8[30] ="\t\t\t\t  [---e----]   ##_  \r\n"   ;
	char cat9[30] ="\t\t\t\t   |  ___  \\  # \\_|  \r\n"   ;
	char cat10[30] ="\t\t\t\t   | |   |  \\#   \r\n"   ;
	char cat11[30] ="\t\t\t\t   | |   |   |    \r\n"   ;
	char cat12[30] ="\t\t\t\t   | \\__/ | ||   \r\n"   ;
	char cat13[30] ="\t\t\t\t   | |   || (/   \r\n"   ;
	char cat14[30] ="\t\t\t\t   (,,)_(,,)/    \r\n"   ;
	char cat15[30] ="\t\t\t\t[_______________] \r\n"   ;
	char cat16[30] ="\t\t\t\t[_______________] \r\n\n\n"   ;

	char begin_str[30] = "TERMOGOTCHI\tV1.2.0\r\n\r\n"; //21
	char hp_str[20]="HP: 000\r\n";
	char full_str[20]="FOOD: 000\r\n";
	char happy_str[30] = "HAPPINESS: 000\r\n";
	char time_str[30] = "You Survived for 0000 seconds."; //start ,17
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartLogic01 */
/**
  * @brief  Function implementing the logic01 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartLogic01 */
void StartLogic01(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {

	  char t;
	 	  if(HAL_UART_Receive(&huart2, &t, 1, 1000)==HAL_OK){
	 		  HAL_UART_Transmit(&huart2, &t, 1, 1000);
	 		  if(t == 'e') {
	 			  eat = 1;
	 			  play = 0;
	 		  } else if (t == 'a' && eat == 1){
	 			  eat = 2;
	 			  play = 0;
	 		  } else if (t == 't' && eat == 2){
	 			  eat = 3;
	 			  play = 0;
	 		  } else if (t == 'p'){
	 			  eat = 0;
	 			  play = 1;
	 		  } else if (t == 'l' && play == 1){
	 			  play = 2;
	 			  eat = 0;
	 		  }
	 		  else if (t == 'a' && play == 2){
	 			  play = 3;
	 			  eat = 0;
	 		  }
	 		  else if (t == 'y' && play == 3){
	 			  play = 4;
	 			  eat = 0;
	 		  }

	 		  else if (t == '\r' && eat == 3){
	 			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	 			  full += 15;
	 			  if(full > 999) full = 999;
	 		  } else if (t == '\r' && play == 4){
	 			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	 			  happy += 10;
	 			  if (happy > 999) happy = 999;
	 		  } else {
	 			  eat = 0;
	 			  play = 0;
	 		  }
	 	  }





	 	  //strcat(begin_str,hp_str);
	 	  //strcat(begin_str,full_str);
	 	  //strcat(begin_str,happy_str);
	 	  //strcat(begin_str,cat_str);




    osDelay(1);
  }

  osThreadTerminate(NULL);
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartLogic02 */
/**
* @brief Function implementing the logic02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLogic02 */
void StartLogic02(void *argument)
{
  /* USER CODE BEGIN StartLogic02 */
  /* Infinite loop */
  for(;;)
  {
	full -= 2;
	happy -= 1;
	if(full>800 && happy > 555){
		full-=50;
		happy-=50;
		hp+= 1;
	}
	if(happy<=0) {
		hp -= 1;
		happy = 0;
	}
	if(full<=0) {
		hp -= 1;
		full = 0;
	}
	if (hp<=0) {
		die = 1;
	}
	count += 1;
    osDelay(1000);
  }
  osThreadTerminate(NULL);
  /* USER CODE END StartLogic02 */
}

/* USER CODE BEGIN Header_StartLogic03 */
/**
* @brief Function implementing the logic03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLogic03 */
void StartLogic03(void *argument)
{
  /* USER CODE BEGIN StartLogic03 */
	int t = 4;
  /* Infinite loop */
  while(die == 0)
  {

	  char hp_str[20]="HP: 000\r\n"; //9
	  hp_str[4] += hp /100 % 10;
	  hp_str[5] += hp / 10 % 10;
	  hp_str[6] += hp%10;

	  char full_str[20]="FOOD: 000\r\n"; //11
	  full_str[6] += full /100 %10;
	  full_str[7] += full / 10 % 10;
	  full_str[8] += full%10;

	  char happy_str[30] = "HAPPINESS: 000\r\n"; //16
	  happy_str[11] += happy /100 %10;
	  happy_str[12] += happy /10 %10;
	  happy_str[13] += happy%10;


	  strcpy((char*)buf,begin_str);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

	  strcpy((char*)buf,hp_str);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

	  strcpy((char*)buf,full_str);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

	  strcpy((char*)buf,happy_str);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

	  strcpy((char*)buf,cat1);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat2);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat3);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat4);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat5);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat6);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat7);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat8);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat9);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat10);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat11);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat12);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat13);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat14);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat15);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
	  strcpy((char*)buf,cat16);
	  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

    osDelay(920);
  }
  strcpy((char*)buf,"your TERMAGOTCHI died.\r\n");
  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);

  time_str[17] += count /1000 %10;
  time_str[18] += count /100 %10;
  time_str[19] += count /10 %10;
  time_str[20] += count%10;
  strcpy((char*)buf,time_str);
  HAL_UART_Transmit(&huart2,buf,strlen((char*)buf),t);
  osThreadTerminate(NULL);
  /* USER CODE END StartLogic03 */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM10 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM10) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
