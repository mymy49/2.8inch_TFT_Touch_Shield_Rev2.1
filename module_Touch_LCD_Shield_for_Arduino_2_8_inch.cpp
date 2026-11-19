/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file module_Touch_LCD_Shield_for_Arduino_2_8_inch.cpp
 * @brief Implementation of the Touch_LCD_Shield_for_Arduino_2_8_inch LCD driver.
 * @author Yoon-Ki Hong
 * @date 2015
 */

#include <config.h>
#include <yss/debug.h>

#include "Touch_LCD_Shield_for_Arduino_2_8_inch.h"

#if !defined(YSS_DRV_SPI_UNSUPPORTED) && !defined(YSS_DRV_GPIO_UNSUPPORTED)

#include <std_ext/string.h>

/**
 * @brief SPI specification used when sending commands and register parameters (8-bit, mode 0, 36 MHz).
 */
static const Spi::specification_t gLcdRegSpec =
{
	Spi::CLOCK_MODE_MODE0,	//uint8_t mode;
	36000000,				//uint32_t maxFreq;
	Spi::BIT_BIT8			//uint8_t bit;
};

/**
 * @brief SPI specification used when sending RGB565 pixel data (16-bit, mode 0, 36 MHz).
 */
static const Spi::specification_t gLcdDataSpec =
{
	Spi::CLOCK_MODE_MODE0,	//uint8_t mode;
	36000000,				//uint32_t maxFreq;
	Spi::BIT_BIT16			//uint8_t bit;
};

/**
 * @details Empty constructor. All hardware configuration is performed in initialize().
 * @see Touch_LCD_Shield_for_Arduino_2_8_inch::initialize()
 * @todo None.
 * @bug None.
 */
Touch_LCD_Shield_for_Arduino_2_8_inch::Touch_LCD_Shield_for_Arduino_2_8_inch(void)
{

}

/**
 * @details Stores the SPI/GPIO configuration, applies the SPI specifications for
 * register and pixel transfers, performs a hardware reset, and then sends the
 * panel-specific ST7789V initialization sequence:
 * -# Software reset
 * -# Memory access control and 16-bit RGB565 pixel format
 * -# Gate, VCOM, and power supply voltage settings
 * -# Frame rate (60 Hz) and positive/negative gamma correction
 * -# Display inversion on, sleep out, and display on
 * @see ST7789V_spi_with_Brush_RGB565::initialize()
 * @todo None.
 * @bug None.
 */
error_t Touch_LCD_Shield_for_Arduino_2_8_inch::initialize(config_t config)
{
	Color color;

	// Store SPI and GPIO pin assignments (CS, DC, RESET)
	setConfig(config);

	// Apply 36 MHz Mode 0 SPI profiles for 8-bit register and 16-bit pixel transfers
	setSpiSpecification(gLcdRegSpec, gLcdDataSpec);

	// Pulse hardware reset pin if connected and wait 50 ms for controller power-up
	reset();
	
	thread::delay(50);

	// Lock SPI bus in 8-bit register command mode
	enable(TYPE_REG);

	uint8_t des;
	//read(0x04, des);
	// Software reset (SWRESET)
	sendReg((cmd_t)0x01, 0x01);

	// Memory data access control: normal scan direction, RGB order
	sendReg(MADCTL, 0x00);

	// Interface pixel format: 16 bits/pixel (RGB565)
	sendReg(COLMOD, 0x55);

	// Gate control: VGH / VGL voltage level
	sendReg(GATE_CTRL, 0x35);

	// VCOM voltage setting
	sendReg(VCOMS, 0x2B);

	// VRH voltage setting
	sendReg(VRHS, 0x11);
	
	// VDV voltage setting
	sendReg(VDVS, 0x20);
	
	// Frame rate control in normal mode (0x0F = 60 Hz)
	sendReg(FRCTRL2, 0x0F);

	// Power control 1: AVDD, AVCL, VDS voltage levels
	const uint8_t pwctrl1[] = {0xA4, 0xA1};
	sendReg(PWCTRL1, (uint8_t *)pwctrl1, sizeof(pwctrl1));

	// Positive voltage gamma control
	const uint8_t pvgamctrl[] = {0xD0, 0x01, 0x08, 0x0F, 0x11, 0x2A, 0x36, 0x55, 0x44, 0x3A, 0x0B, 0x06, 0x11, 0x20};
	sendReg(PVGAMCTRL, (uint8_t *)pvgamctrl, sizeof(pvgamctrl));
	
	// Negative voltage gamma control
	const uint8_t nvgamctrl[] = {0xD0, 0x02, 0x07, 0x0A, 0x0B, 0x18, 0x34, 0x43, 0x4A, 0x2B, 0x1B, 0x1C, 0x22, 0x1F};
	sendReg(NVGAMCTRL, (uint8_t *)nvgamctrl, sizeof(nvgamctrl));
	
	// Content adaptive brightness control and color enhancement
	sendReg(WRCACE, 0xB0);
	
	// Display inversion on (required for correct colors on this panel)
	sendReg(DISP_INVERSION_ON);
	thread::delay(50);

	// Sleep out
	sendReg(SLPOUT);
	thread::delay(50);

	// Display on
	sendReg(DISPON);
	thread::delay(50);

	// Release SPI bus lock after initialization sequence completes
	disable();

	return error_t::ERROR_NONE;
}

/**
 * @details Returns the native panel resolution. The width and height are swapped
 * when the rotation flag (mRotateFlag) is set.
 * @see Touch_LCD_Shield_for_Arduino_2_8_inch::getCanvasSize()
 * @todo None.
 * @bug None.
 */
Size Touch_LCD_Shield_for_Arduino_2_8_inch::getLcdSize(void)
{
	// Return 320x240 in landscape (rotated) mode or 240x320 in portrait mode
	if(mRotateFlag)
		return Size{320, 240};
	else
		return Size{240, 320};
}

/**
 * @details Returns the drawable canvas size, which is identical to the panel
 * resolution for this LCD. The width and height are swapped when the rotation
 * flag (mRotateFlag) is set.
 * @see Touch_LCD_Shield_for_Arduino_2_8_inch::getLcdSize()
 * @todo None.
 * @bug None.
 */
Size Touch_LCD_Shield_for_Arduino_2_8_inch::getCanvasSize(void)
{
	// Return 320x240 in landscape (rotated) mode or 240x320 in portrait mode
	if(mRotateFlag)
		return Size{320, 240};
	else
		return Size{240, 320};
}

#endif

