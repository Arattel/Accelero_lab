/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_otg.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "stm32f411e_discovery_accelerometer.h"
#include <math.h>
#include "stm32f411e_discovery_gyroscope.h"
#include "lcd5110.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
double get_result_accelero(int16_t* buffer);
double get_result_gyro(float* buffer);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
double get_result_accelero(int16_t* buffer) {
	double numbers[3] = { (double) (buffer[0] / 16) / 1000.0,
			(double) (buffer[1] / 16) / 1000.0, (double) (buffer[2] / 16)
					/ 1000.0 };
	double result = sqrt(
			numbers[0] * numbers[0] + numbers[1] * numbers[1]
					+ numbers[2] * numbers[2]);
	return (result);
}
double get_result_gyro(float* buffer) {
	double numbers[3] = { (double) (buffer[0] / 1000), (double) (buffer[1]
			/ 1000), (double) (buffer[2]) / 1000.0 };
	double result = sqrt(
			numbers[0] * numbers[0] + numbers[1] * numbers[1]
					+ numbers[2] * numbers[2]);
	return (result);
}
LCD5110_display lcd1;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *
 * @retval None
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

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
	MX_I2C1_Init();
	MX_I2S2_Init();
	MX_I2S3_Init();
	MX_SPI1_Init();
	MX_USB_OTG_FS_HCD_Init();
	MX_SPI5_Init();
	/* USER CODE BEGIN 2 */
	if (BSP_ACCELERO_Init() != HAL_OK) {
		/* Initialization Error */
		printf("Error initializing Accelero.");
		while (1) {
		}
	}
	if (BSP_GYRO_Init() != HAL_OK) {
		/* Initialization Error */
		printf("Error initializing Gyro.");
		while (1) {
		}
	}
	lcd1.hw_conf.spi_handle = &hspi5;
	lcd1.hw_conf.spi_cs_pin = LCD1_CS_Pin;
	lcd1.hw_conf.spi_cs_port = LCD1_CS_GPIO_Port;
	lcd1.hw_conf.rst_pin = LCD1_RST_Pin;
	lcd1.hw_conf.rst_port = LCD1_RST_GPIO_Port;
	lcd1.hw_conf.dc_pin = LCD1_DC_Pin;
	lcd1.hw_conf.dc_port = LCD1_DC_GPIO_Port;
	lcd1.def_scr = lcd5110_def_scr;
	LCD5110_init(&lcd1.hw_conf, LCD5110_NORMAL_MODE, 0x40, 2, 3);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	int16_t buffer_acc[3];
	float buffer_gyr[3];
	BSP_ACCELERO_GetXYZ(buffer_acc);
	BSP_GYRO_GetXYZ(buffer_gyr);
	double max_result_acc = get_result_accelero(buffer_acc);
	double cur_result_acc;
	double max_result_gyr = get_result_gyro(buffer_gyr);
	double cur_result_gyr;
	while (1)

	{
		BSP_ACCELERO_GetXYZ(buffer_acc);
		BSP_GYRO_GetXYZ(buffer_gyr);
		cur_result_acc = get_result_accelero(buffer_acc);
		if (cur_result_acc > max_result_acc) {
			max_result_acc = cur_result_acc;
		}
		cur_result_gyr = get_result_gyro(buffer_gyr);
		if (cur_result_gyr > max_result_gyr) {
			max_result_gyr = cur_result_gyr;
		}
		char* xyz_acc[38];
		LCD5110_clear_scr(&lcd1);
		LCD5110_set_cursor(0, 0, &lcd1);
		sprintf(xyz_acc, "Acc: %g,%g,%g \n",
				(double) (buffer_acc[0] / 16) / 1000.0,
				(double) (buffer_acc[1] / 16) / 1000.0,
				(double) (buffer_acc[2] / 16) / 1000.0);
		LCD5110_print(xyz_acc, BLACK, &lcd1);
		LCD5110_clear_scr(&lcd1);
		LCD5110_set_cursor(0, 0, &lcd1);
		HAL_Delay(1500);
		char* acc_res[11];
		char* max_res[11];
		char* xyz_gyr[38];
		sprintf(acc_res, "Accelero result: %g\n", cur_result_acc);
		LCD5110_print(acc_res, BLACK, &lcd1);
		sprintf(max_res, "Max accelero result: %g\n", max_result_acc);
		LCD5110_print(max_res, BLACK, &lcd1);
		HAL_Delay(1500);
		LCD5110_clear_scr(&lcd1);
		LCD5110_set_cursor(0, 0, &lcd1);
		sprintf(xyz_gyr, "Gyr: %g %g %g \n", (double) (buffer_gyr[0] / 1000),
				(double) (buffer_gyr[1] / 1000),
				(double) (buffer_gyr[2]/ 1000.0));
		LCD5110_print(xyz_gyr, BLACK, &lcd1);
		LCD5110_clear_scr(&lcd1);
		HAL_Delay(1500);
		LCD5110_set_cursor(0, 0, &lcd1);
		sprintf(acc_res, "Gyro result: %g\n", cur_result_gyr);
		LCD5110_print(acc_res, BLACK, &lcd1);
		sprintf(max_res, "Max gyro result: %g\n", max_result_gyr);
		LCD5110_print(max_res, BLACK, &lcd1);
		HAL_Delay(1500);
		/*
		 printf("Gyro result: %g\n", cur_result_gyr);
		 printf("Max gyro result: %g\n", max_result_gyr);
		 */
		/* USER CODE END WHILE */
	}
	/* USER CODE BEGIN 3 */
	/* USER CODE END 3 */

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 192;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 8;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
	PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
	PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
	PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @retval None
 */
void _Error_Handler(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
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
void assert_failed(uint8_t* file, uint32_t line) {
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
