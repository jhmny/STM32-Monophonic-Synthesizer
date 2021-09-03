/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stddef.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"

//_BEGIN_STD_C


#include "ssd1306_fonts.h"

/* vvv I2C config vvv */

#ifndef SSD1306_I2C_PORT
#define SSD1306_I2C_PORT		hi2c1
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR        0x78
#endif

/* ^^^ I2C config ^^^ */

extern I2C_HandleTypeDef SSD1306_I2C_PORT;

typedef enum {
	Sym_Wifi,
	Sym_Arrow,
	Sym_Server	
}Symbol;

static const uint16_t Symbols[] = {
0x7800, 0x0400, 0x7200, 0x0900, 0x6500, 0x1500, 0xD500, 0xC000, // Wifi symbol	
0x0000, 0x1000, 0x0800, 0x0400, 0xfe00, 0x0400, 0x0800, 0x1000, // Right Arrow symbol
0x0000, 0x3e00, 0x4600, 0xfa00, 0x8e00, 0xfa00, 0x8C00, 0xf800 // Server symbol
};

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

// some LEDs don't display anything in first two columns
// #define SSD1306_WIDTH           130

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1306_t;

// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteSymbol(Symbol sym, SSD1306_COLOR color);
char ssd1306_WriteSymbolSpace(void);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size);

//_END_STD_C

#endif // __SSD1306_H__
