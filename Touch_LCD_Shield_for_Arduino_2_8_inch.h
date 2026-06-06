/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef YSS_MOD_SPI_TFT_LCD_TOUCH_LCD_SHIELD_FOR_ARDUINO_2_8_INCH__H_
#define YSS_MOD_SPI_TFT_LCD_TOUCH_LCD_SHIELD_FOR_ARDUINO_2_8_INCH__H_

#include "ST7789V/ST7789V_spi_with_Brush_RGB565.h"

// 구매처 : https://www.eleparts.co.kr/goods/view?no=3216739
// 구매처 : https://www.waveshare.com/2.8inch-TFT-Touch-Shield.htm

class Touch_LCD_Shield_for_Arduino_2_8_inch : public ST7789V_spi_with_Brush_RGB565
{
  public:
	Touch_LCD_Shield_for_Arduino_2_8_inch(void);
	
	// TftLcdDriver
	error_t initialize(config_t config) override;

	Size getLcdSize(void) override;

	Size getCanvasSize(void) override;
};

#endif

