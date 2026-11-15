/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file Touch_LCD_Shield_for_Arduino_2_8_inch.h
 * @brief Board-level driver for the Waveshare 2.8inch TFT Touch Shield (Rev 2.1) with an ST7789V LCD controller.
 */

#ifndef YSS_MOD_SPI_TFT_LCD_TOUCH_LCD_SHIELD_FOR_ARDUINO_2_8_INCH__H_
#define YSS_MOD_SPI_TFT_LCD_TOUCH_LCD_SHIELD_FOR_ARDUINO_2_8_INCH__H_

#include "ST7789V/ST7789V_spi_with_Brush_RGB565.h"

// Purchase: https://www.eleparts.co.kr/goods/view?no=3216739
// Purchase: https://www.waveshare.com/2.8inch-TFT-Touch-Shield.htm

/**
 * @class Touch_LCD_Shield_for_Arduino_2_8_inch
 * @brief LCD driver for the Waveshare 2.8inch TFT Touch Shield (240 x 320, RGB565, SPI interface).
 *
 * @details
 * This class specializes `ST7789V_spi_with_Brush_RGB565` for the Waveshare 2.8inch
 * Arduino-compatible TFT Touch Shield. It provides the panel-specific power, gamma,
 * and display initialization sequence for the on-board ST7789V controller, and
 * reports the physical resolution of the panel.
 *
 * ### Panel Specification
 * - Controller : ST7789V
 * - Resolution : 240 x 320 pixels (portrait), 320 x 240 pixels (rotated)
 * - Color depth: 16-bit RGB565
 * - Interface  : 4-wire SPI (CS, D/C, RESET, SCK/MOSI)
 *
 * @note The touch controller (XPT2046) on the shield is not handled by this class.
 *
 * ### Example Usage
 * @code
 * #include <2.8inch_TFT_Touch_Shield_Rev2.1/Touch_LCD_Shield_for_Arduino_2_8_inch.h>
 *
 * Touch_LCD_Shield_for_Arduino_2_8_inch lcd;
 *
 * void initLcd(void)
 * {
 *     // SPI peripheral and GPIO output pins must be initialized beforehand.
 *     Touch_LCD_Shield_for_Arduino_2_8_inch::config_t lcdConfig =
 *     {
 *         spi0,           // Spi &spi;
 *         {&gpioA, 3},    // pin_t chipSelect;
 *         {&gpioA, 6},    // pin_t dataCommand;
 *         {0, 0}          // pin_t reset; (not connected)
 *     };
 *
 *     brush.malloc(5000);
 *
 *     lcd.initialize(lcdConfig);
 *     lcd.setFrameBuffer(brush);
 *     lcd.setBackgroundColor({0xFF, 0xFF, 0xFF});
 *     lcd.clear();
 * }
 * @endcode
 */
class Touch_LCD_Shield_for_Arduino_2_8_inch : public ST7789V_spi_with_Brush_RGB565
{
  public:
	/**
	 * @brief Constructs a new Touch_LCD_Shield_for_Arduino_2_8_inch object.
	 * @author Yoon-Ki Hong
	 * @date 2015
	 * @warning None.
	 * @note None.
	 * @pre None.
	 * @post Instance is constructed.
	 * @deprecated None.
	 */
	Touch_LCD_Shield_for_Arduino_2_8_inch(void);
	
	// TftLcdDriver
	/**
	 * @brief Initializes the LCD panel with the shield-specific ST7789V register sequence.
	 * @param[in] config SPI peripheral and control pins (CS, D/C, RESET) connected to the LCD.
	 * @return `error_t::ERROR_NONE` on success.
	 * @author Yoon-Ki Hong
	 * @date 2015
	 * @warning Overrides `ST7789V_spi_with_Brush_RGB565::initialize()`.
	 * @note Transmits panel-specific gamma, power, and display on sequences.
	 * @pre SPI and GPIO peripherals must be clock-enabled.
	 * @post LCD panel display is active and clear for drawing.
	 * @deprecated None.
	 */
	error_t initialize(config_t config) override;

	/**
	 * @brief Gets the physical resolution of the LCD panel.
	 * @return 240 x 320 in portrait mode, or 320 x 240 when rotated.
	 * @author Yoon-Ki Hong
	 * @date 2015
	 * @warning Overrides `TftLcdDriver::getLcdSize()`.
	 * @note Reflects `mRotateFlag` state.
	 * @pre None.
	 * @post None.
	 * @deprecated None.
	 */
	Size getLcdSize(void) override;

	/**
	 * @brief Gets the drawable canvas size of the LCD.
	 * @return 240 x 320 in portrait mode, or 320 x 240 when rotated.
	 * @author Yoon-Ki Hong
	 * @date 2015
	 * @warning Overrides `TftLcdDriver::getCanvasSize()`.
	 * @note Identical to `getLcdSize()` for direct hardware panels.
	 * @pre None.
	 * @post None.
	 * @deprecated None.
	 */
	Size getCanvasSize(void) override;
};

#endif
