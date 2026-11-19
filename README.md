# 2.8inch TFT Touch Shield Rev2.1

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Doxygen Build](https://github.com/mymy49/2.8inch_TFT_Touch_Shield_Rev2.1/actions/workflows/doxygen.yml/badge.svg)](https://github.com/mymy49/2.8inch_TFT_Touch_Shield_Rev2.1/actions)
[![Doxygen API Docs](https://img.shields.io/badge/docs-API%20Reference-brightgreen.svg)](https://mymy49.github.io/2.8inch_TFT_Touch_Shield_Rev2.1/)

Board-level driver for the **Waveshare 2.8inch TFT Touch Shield (Rev 2.1)** with an **ST7789V** LCD controller and **TurtleShip** 2D graphics support for the **yss OS** embedded framework.

---

## 1. Overview & Key Features

The **2.8inch_TFT_Touch_Shield_Rev2.1** module is a board-level hardware driver designed for Arduino UNO-compatible touch LCD shields featuring a Sitronix ST7789V display controller. It specializes the [ST7789V](https://github.com/mymy49/ST7789V) driver with panel-specific initialization, gamma curves, and power sequences, while leveraging the [TurtleShip](https://github.com/mymy49/TurtleShip) 2D graphics engine for high-speed rendering.

### Key Highlights
- **Shield Hardware Integration (`Touch_LCD_Shield_for_Arduino_2_8_inch`)**:
  - Full board support for the Waveshare 2.8inch TFT Touch Shield (Rev 2.1) in standard Arduino UNO form factor.
  - Native support for the 240x320 RGB565 TFT LCD panel driven by the ST7789V controller.
  - Dedicated initialization sequence including software reset, 60 Hz frame rate calibration, gate/VCOM voltage settings, and positive/negative gamma correction.
- **High-Speed Dual-Mode SPI Operation**:
  - 8-bit transfers for fast command and register parameter configuration (Mode 0, up to 36 MHz).
  - 16-bit transfers for high-throughput pixel GRAM streaming (Mode 0, up to 36 MHz).
- **RAM-Efficient 2D Graphics Engine**:
  - Inherits from `ST7789V_spi_with_Brush_RGB565` and `BrushTftLcdRgb565LE`.
  - Enables direct vector drawing (lines, circles, rectangles, text, fonts, bitmaps) straight into LCD GRAM without requiring a full 153.6 KB framebuffer in microcontroller SRAM.
  - Seamlessly integrates with partial off-screen working framebuffers (`setFrameBuffer()`) for flicker-free rendering.
- **Nested Submodule Architecture & Doxygen Cross-Referencing**:
  - Directly incorporates `ST7789V` and nested `TurtleShip` submodules.
  - Doxygen configuration links external APIs via tag files (`ST7789V.tag`, `TurtleShip.tag`), providing cross-referenced documentation across the entire graphics stack.

---

## 2. System Specifications & Hardware Environment

### Supported Targets & Tools
- **Target Microcontrollers & Development Boards**:
  - Nuvoton NuMicro® M251 series (e.g., **NuMaker-M251KG** / Cortex®-M23).
  - Any MCU board equipped with Arduino UNO R3-compatible shield headers.
- **Shield Hardware Specifications**:
  - Shield Model: [Waveshare 2.8inch TFT Touch Shield](https://www.waveshare.com/2.8inch-TFT-Touch-Shield.htm) / [Eleparts](https://www.eleparts.co.kr/goods/view?no=3216739)
  - LCD Controller: Sitronix ST7789V (240 x 320 pixels)
  - Color Depth: 16-bit RGB565
  - Touch Controller: XPT2046 4-wire resistive touch controller (supported via the companion [XPT2046](https://github.com/mymy49/XPT2046) module)
  - Storage: Onboard MicroSD card slot
- **Required Software & Toolchains**:
  - Toolchain: CrossWorks for ARM (v5.x or higher).
    - **Note on CrossWorks for ARM**: CrossWorks for ARM does not natively support the Nuvoton M251 series. You must install the custom [CrossworksForARM_Nuvoton_M251 Support Package](https://github.com/mymy49/CrossworksForARM_Nuvoton_M251) before building M251 projects.
  - Operating System: [yss OS](https://github.com/mymy49/yss) (embedded RTOS & HAL).
  - Graphics Engine: [TurtleShip](https://github.com/mymy49/TurtleShip) (included as nested submodule).
  - Language: C++11 or higher.

### Pin Map & Hardware Connections
The table below illustrates the pin mappings between the Arduino UNO header on the **NuMaker-M251KG** and the shield's onboard LCD and Touch controllers:

| Arduino Pin | Shield Signal | NuMaker-M251KG Pin | MCU Function / Peripheral | Description |
| :--- | :--- | :--- | :--- | :--- |
| **D11** | MOSI | `PA.0` | `Gpio::PA0_SPI0_MOSI` | SPI Master Output / Slave Input |
| **D12** | MISO | `PA.1` | `Gpio::PA1_SPI0_MISO` | SPI Master Input / Slave Output |
| **D13** | SCK | `PA.2` | `Gpio::PA2_SPI0_CLK` | SPI Serial Clock |
| **D10** | LCD_CS | `PA.3` | GPIO Output (Active Low) | LCD Controller Chip Select |
| **D9** | LCD_BL | `PA.4` | GPIO Output (Active High) | Display Backlight Control (High: ON) |
| **D8** | LCD_DC | `PA.6` | GPIO Output (Data/Command) | LCD Command / Data Select (Low: Reg, High: Data) |
| **D7** | TP_CS | `PC.3` | GPIO Output (Active Low) | Touch Controller (XPT2046) Chip Select |
| **D4** | TP_IRQ | `PC.5` | GPIO External Interrupt | Touch Interrupt Pin (PENIRQ, Falling Edge) |
| **RESET** | LCD_RST | `NC` | Unused (`{0, 0}`) | Hardware Reset (Tied high on shield) |

---

## 3. Installation & Project Setup

### Cloning with Nested Submodules
To clone a project containing this shield driver along with all nested submodules (`ST7789V` and `TurtleShip`):
```bash
git clone --recursive https://github.com/mymy49/NuMaker-M251KG_example.git
```

To add this repository as a submodule into your project:
```bash
git submodule add --recursive https://github.com/mymy49/2.8inch_TFT_Touch_Shield_Rev2.1.git module/2.8inch_TFT_Touch_Shield_Rev2.1
```

### Prerequisites: Nuvoton M251 Support Package for CrossWorks for ARM
CrossWorks for ARM does not natively provide device support for Nuvoton NuMicro® M251 microcontrollers in its default package manager. A custom device support package must be installed beforehand:

1. Clone or download the [CrossworksForARM_Nuvoton_M251](https://github.com/mymy49/CrossworksForARM_Nuvoton_M251) repository.
2. Open the package project file (`.hzp`) in CrossWorks for ARM and build it (`F7` or `Build -> Build Project`) to generate the package file (`.hzq`).
3. In CrossWorks for ARM, navigate to **Tools -> Packages -> Manually Install Packages...** and select the generated `.hzq` package file.
4. Once installed, M251 target device definitions, CMSIS headers, and project templates will be fully available in CrossWorks for ARM.

### Build and Firmware Flashing
- **CrossWorks for ARM**:
  1. Ensure the [CrossworksForARM_Nuvoton_M251](https://github.com/mymy49/CrossworksForARM_Nuvoton_M251) package has been installed.
  2. Open the project solution file (e.g., `Example.hzp`).
  3. Select target configuration (`Example THUMB Release` or `Example THUMB Debug`).
  4. Build solution via `F7` or `Build -> Build Solution`.
  5. Connect the board via Nu-Link ICE and flash with `Ctrl+D` (`Target -> Download`).
- **Command Line (pyOCD / OpenOCD)**:
  ```bash
  # Flash prebuilt binary using pyocd
  pyocd flash -t m251kg firmware.bin
  ```

---

## 4. Quick Start & Example Code

Below is a complete, real-world example demonstrating how to configure the SPI0 peripheral, initialize the shield driver, and render graphics using both direct drawing and an off-screen brush under yss OS:

### 1. Hardware Initialization (`bsp.cpp`)
```cpp
#include <bsp.h>
#include <yss/instance.h>
#include <module/2.8inch_TFT_Touch_Shield_Rev2.1/Touch_LCD_Shield_for_Arduino_2_8_inch.h>
#include <TurtleShip.h>

// Global display and working brush instances
Touch_LCD_Shield_for_Arduino_2_8_inch lcd;
FrameBufferRgb565LE brush;

void initializeBoard(void)
{
    // 1. Configure SPI0 GPIO alternate functions
    gpioA.setAsAltFunc(0, Gpio::PA0_SPI0_MOSI);
    gpioA.setAsAltFunc(1, Gpio::PA1_SPI0_MISO);
    gpioA.setAsAltFunc(2, Gpio::PA2_SPI0_CLK);

    // 2. Initialize SPI0 peripheral in main mode
    Spi::config_t spi0Config = 
    {
        Spi::MODE_MAIN
    };

    spi0.enableClock();
    spi0.initialize(spi0Config);
    spi0.enableInterrupt();

    // 3. Configure GPIO control pins (CS, Backlight, DC)
    gpioA.setAsOutput(3); // CS
    gpioA.setAsOutput(4); // BL
    gpioA.setAsOutput(6); // DC

    // Turn on LCD backlight
    gpioA.setOutput(4, true);

    // 4. Configure shield LCD driver
    Touch_LCD_Shield_for_Arduino_2_8_inch::config_t lcdConfig =
    {
        spi0,           // Spi &spi;
        {&gpioA, 3},    // pin_t chipSelect;
        {&gpioA, 6},    // pin_t dataCommand;
        {0, 0}          // pin_t reset (unused / tied high);
    };

    // 5. Allocate off-screen brush memory and initialize panel
    brush.malloc(5000);
    lcd.initialize(lcdConfig);
    lcd.setFrameBuffer(brush);
    lcd.setBackgroundColor({0x00, 0x00, 0x00});
    lcd.clear();
}
```

### 2. Direct On-Screen Vector Drawing
Because `Touch_LCD_Shield_for_Arduino_2_8_inch` inherits `Brush`, graphics can be rendered directly to the screen:
```cpp
void drawDirectDemo(void)
{
    lcd.lock();

    // Clear background
    lcd.setBackgroundColor({0x00, 0x00, 0x20});
    lcd.clear();

    // Direct line, circle, and rectangle rendering
    lcd.setBrushColor({0xFF, 0x00, 0x00}); // Red
    lcd.drawLine({10, 10}, {230, 10});

    lcd.setBrushColor({0x00, 0xFF, 0x00}); // Green
    lcd.drawCircle({120, 160}, 40);

    lcd.setBrushColor({0x00, 0x80, 0xFF}); // Blue
    lcd.fillRectangular({30, 240, 180, 40});

    lcd.unlock();
}
```

### 3. Off-Screen Rendering with Anti-Aliased Typography
```cpp
#include <font/Ubuntu_20_B.h>

void drawTextCard(Area area, const char *text)
{
    lcd.lock();

    // Set off-screen buffer size and clear
    brush.setSize(area);
    brush.setBackgroundColor(0x20, 0x20, 0x20);
    brush.clear();

    // Draw inner border
    brush.setBrushColor(0x50, 0x50, 0x50);
    brush.drawRectangular({1, 1, area.width - 2, area.height - 2});

    // Render anti-aliased font
    brush.setFont(Font_Ubuntu_20_B);
    brush.setBrushColor(0xFF, 0xFF, 0xFF);
    brush.drawString(Brush::ALIGN_CENTER_MID, text);

    // Blit rendered off-screen bitmap to the LCD
    lcd.drawBitmap(area.getPosition(), brush.getBitmap());

    lcd.unlock();
}
```

---

## 5. Documentation & References

- **Doxygen API Reference**: [https://mymy49.github.io/2.8inch_TFT_Touch_Shield_Rev2.1/](https://mymy49.github.io/2.8inch_TFT_Touch_Shield_Rev2.1/)
- **ST7789V Submodule Reference**: [https://mymy49.github.io/ST7789V/](https://mymy49.github.io/ST7789V/)
- **TurtleShip Submodule Reference**: [https://mymy49.github.io/TurtleShip/](https://mymy49.github.io/TurtleShip/)
- **XPT2046 Touch Driver Reference**: [https://mymy49.github.io/XPT2046/](https://mymy49.github.io/XPT2046/)
- **Hardware Schematic**: [2.8inch TFT Touch Shield Schematic](Documents/2.8inch_TFT_Touch_Shield_Schematic_update.pdf)
- **Doxygen Main Page**: This `README.md` file serves as the main page of the generated Doxygen documentation (`USE_MDFILE_AS_MAINPAGE = README.md`).

---

## 6. License & Author

- **Author**: Yoon-Ki Hong
- **License**: MIT License. See [LICENSE](LICENSE) for full terms and conditions.
