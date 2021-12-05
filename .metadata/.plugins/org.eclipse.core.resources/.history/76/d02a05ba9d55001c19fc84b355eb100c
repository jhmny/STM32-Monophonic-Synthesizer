/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for STM32f10x: Alexander Lutsai<s.lyra@ya.ru>

   ----------------------------------------------------------------------
   	Copyright (C) Alexander Lutsai, 2016
    Copyright (C) Tilen Majerle, 2015

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */
#include "ssd1306.h"
//#include "sine_animation.h"
extern I2C_HandleTypeDef hi2c2;
extern wave1;
/* Write command */
#define SSD1306_WRITECOMMAND(command)      ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define SSD1306_WRITEDATA(data)            ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))

/* SSD1306 data buffer */
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

/* Private SSD1306 structure */
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

/* Private variable */
static SSD1306_t SSD1306;


#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range

#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7


void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_RIGHT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}


void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_LEFT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}


void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}


void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}


void SSD1306_Stopscroll(void)
{
	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
}



void SSD1306_InvertDisplay (int i)
{
  if (i) SSD1306_WRITECOMMAND (SSD1306_INVERTDISPLAY);

  else SSD1306_WRITECOMMAND (SSD1306_NORMALDISPLAY);

}


void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color)
{

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for(int16_t j=0; j<h; j++, y++)
    {
        for(int16_t i=0; i<w; i++)
        {
            if(i & 7)
            {
               byte <<= 1;
            }
            else
            {
               byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }
            if(byte & 0x80) SSD1306_DrawPixel(x+i, y, color);
        }
    }
}








uint8_t SSD1306_Init(void) {

	/* Init I2C */
	ssd1306_I2C_Init();
	
	/* Check if LCD connected to I2C */
	if (HAL_I2C_IsDeviceReady(&hi2c2, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK) {
		/* Return false */
		return 0;
	}
	
	/* A little delay */
	uint32_t p = 2500;
	while(p>0)
		p--;
	
	/* Init LCD */
	SSD1306_WRITECOMMAND(0xAE); //display off
	SSD1306_WRITECOMMAND(0x20); //Set Memory Addressing Mode   
	SSD1306_WRITECOMMAND(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	SSD1306_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	SSD1306_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
	SSD1306_WRITECOMMAND(0x00); //---set low column address
	SSD1306_WRITECOMMAND(0x10); //---set high column address
	SSD1306_WRITECOMMAND(0x40); //--set start line address
	SSD1306_WRITECOMMAND(0x81); //--set contrast control register
	SSD1306_WRITECOMMAND(0xFF);
	SSD1306_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127
	SSD1306_WRITECOMMAND(0xA6); //--set normal display
	SSD1306_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
	SSD1306_WRITECOMMAND(0x3F); //
	SSD1306_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	SSD1306_WRITECOMMAND(0xD3); //-set display offset
	SSD1306_WRITECOMMAND(0x00); //-not offset
	SSD1306_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
	SSD1306_WRITECOMMAND(0xF0); //--set divide ratio
	SSD1306_WRITECOMMAND(0xD9); //--set pre-charge period
	SSD1306_WRITECOMMAND(0x22); //
	SSD1306_WRITECOMMAND(0xDA); //--set com pins hardware configuration
	SSD1306_WRITECOMMAND(0x12);
	SSD1306_WRITECOMMAND(0xDB); //--set vcomh
	SSD1306_WRITECOMMAND(0x20); //0x20,0.77xVcc
	SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
	SSD1306_WRITECOMMAND(0x14); //
	SSD1306_WRITECOMMAND(0xAF); //--turn on SSD1306 panel
	

	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);

	/* Clear screen */
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	
	/* Update screen */
	SSD1306_UpdateScreen();
	
	/* Set default values */
	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;
	
	/* Initialized OK */
	SSD1306.Initialized = 1;
	
	/* Return OK */
	return 1;
}

void SSD1306_UpdateScreen(void) {
	uint8_t m;
	
	for (m = 0; m < 8; m++) {
		SSD1306_WRITECOMMAND(0xB0 + m);
		SSD1306_WRITECOMMAND(0x00);
		SSD1306_WRITECOMMAND(0x10);
		
		/* Write multi data */
		ssd1306_I2C_WriteMulti(SSD1306_I2C_ADDR, 0x40, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
	}
}

void SSD1306_ToggleInvert(void) {
	uint16_t i;
	
	/* Toggle invert */
	SSD1306.Inverted = !SSD1306.Inverted;
	
	/* Do memory toggle */
	for (i = 0; i < sizeof(SSD1306_Buffer); i++) {
		SSD1306_Buffer[i] = ~SSD1306_Buffer[i];
	}
}

void SSD1306_Fill(SSD1306_COLOR_t color) {
	/* Set memory */
	memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		/* Error */
		return;
	}
	
	/* Check if pixels are inverted */
	if (SSD1306.Inverted) {
		color = (SSD1306_COLOR_t)!color;
	}
	
	/* Set color */
	if (color == SSD1306_COLOR_WHITE) {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

void SSD1306_GotoXY(uint16_t x, uint16_t y) {
	/* Set write pointers */
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color) {
	uint32_t i, b, j;
	
	/* Check available space in LCD */
	if (
		SSD1306_WIDTH <= (SSD1306.CurrentX + Font->FontWidth) ||
		SSD1306_HEIGHT <= (SSD1306.CurrentY + Font->FontHeight)
	) {
		/* Error */
		return 0;
	}
	
	/* Go through font */
	for (i = 0; i < Font->FontHeight; i++) {
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t) color);
			} else {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);
			}
		}
	}
	
	/* Increase pointer */
	SSD1306.CurrentX += Font->FontWidth;
	
	/* Return character written */
	return ch;
}

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {
	/* Write characters */
	while (*str) {
		/* Write character by character */
		if (SSD1306_Putc(*str, Font, color) != *str) {
			/* Return error */
			return *str;
		}
		
		/* Increase string pointer */
		str++;
	}
	
	/* Everything OK, zero should be returned */
	return *str;
}
 

void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp; 
	
	/* Check for overflow */
	if (x0 >= SSD1306_WIDTH) {
		x0 = SSD1306_WIDTH - 1;
	}
	if (x1 >= SSD1306_WIDTH) {
		x1 = SSD1306_WIDTH - 1;
	}
	if (y0 >= SSD1306_HEIGHT) {
		y0 = SSD1306_HEIGHT - 1;
	}
	if (y1 >= SSD1306_HEIGHT) {
		y1 = SSD1306_HEIGHT - 1;
	}
	
	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1); 
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1); 
	sx = (x0 < x1) ? 1 : -1; 
	sy = (y0 < y1) ? 1 : -1; 
	err = ((dx > dy) ? dx : -dy) / 2; 

	if (dx == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		
		/* Vertical line */
		for (i = y0; i <= y1; i++) {
			SSD1306_DrawPixel(x0, i, c);
		}
		
		/* Return from function */
		return;
	}
	
	if (dy == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		
		/* Horizontal line */
		for (i = x0; i <= x1; i++) {
			SSD1306_DrawPixel(i, y0, c);
		}
		
		/* Return from function */
		return;
	}
	
	while (1) {
		SSD1306_DrawPixel(x0, y0, c);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err; 
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		} 
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		} 
	}
}

void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c) {
	/* Check input parameters */
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		/* Return error */
		return;
	}
	
	/* Check width and height */
	if ((x + w) >= SSD1306_WIDTH) {
		w = SSD1306_WIDTH - x;
	}
	if ((y + h) >= SSD1306_HEIGHT) {
		h = SSD1306_HEIGHT - y;
	}
	
	/* Draw 4 lines */
	SSD1306_DrawLine(x, y, x + w, y, c);         /* Top line */
	SSD1306_DrawLine(x, y + h, x + w, y + h, c); /* Bottom line */
	SSD1306_DrawLine(x, y, x, y + h, c);         /* Left line */
	SSD1306_DrawLine(x + w, y, x + w, y + h, c); /* Right line */
}

void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c) {
	uint8_t i;
	
	/* Check input parameters */
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		/* Return error */
		return;
	}
	
	/* Check width and height */
	if ((x + w) >= SSD1306_WIDTH) {
		w = SSD1306_WIDTH - x;
	}
	if ((y + h) >= SSD1306_HEIGHT) {
		h = SSD1306_HEIGHT - y;
	}
	
	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
		SSD1306_DrawLine(x, y + i, x + w, y + i, c);
	}
}

void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color) {
	/* Draw lines */
	SSD1306_DrawLine(x1, y1, x2, y2, color);
	SSD1306_DrawLine(x2, y2, x3, y3, color);
	SSD1306_DrawLine(x3, y3, x1, y1, color);
}


void SSD1306_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
	curpixel = 0;
	
	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		SSD1306_DrawLine(x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    SSD1306_DrawPixel(x0, y0 + r, c);
    SSD1306_DrawPixel(x0, y0 - r, c);
    SSD1306_DrawPixel(x0 + r, y0, c);
    SSD1306_DrawPixel(x0 - r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SSD1306_DrawPixel(x0 + x, y0 + y, c);
        SSD1306_DrawPixel(x0 - x, y0 + y, c);
        SSD1306_DrawPixel(x0 + x, y0 - y, c);
        SSD1306_DrawPixel(x0 - x, y0 - y, c);

        SSD1306_DrawPixel(x0 + y, y0 + x, c);
        SSD1306_DrawPixel(x0 - y, y0 + x, c);
        SSD1306_DrawPixel(x0 + y, y0 - x, c);
        SSD1306_DrawPixel(x0 - y, y0 - x, c);
    }
}

void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    SSD1306_DrawPixel(x0, y0 + r, c);
    SSD1306_DrawPixel(x0, y0 - r, c);
    SSD1306_DrawPixel(x0 + r, y0, c);
    SSD1306_DrawPixel(x0 - r, y0, c);
    SSD1306_DrawLine(x0 - r, y0, x0 + r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        SSD1306_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, c);
        SSD1306_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, c);

        SSD1306_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, c);
        SSD1306_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}
 


void SSD1306_Clear (void)
{
	SSD1306_Fill (0);
    SSD1306_UpdateScreen();
}
void SSD1306_ON(void) {
	SSD1306_WRITECOMMAND(0x8D);  
	SSD1306_WRITECOMMAND(0x14);  
	SSD1306_WRITECOMMAND(0xAF);  
}
void SSD1306_OFF(void) {
	SSD1306_WRITECOMMAND(0x8D);  
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0xAE);  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____ ___   _____ 
// |_   _|__ \ / ____|
//   | |    ) | |     
//   | |   / /| |     
//  _| |_ / /_| |____ 
// |_____|____|\_____|
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void ssd1306_I2C_Init() {
	//MX_I2C1_Init();
	uint32_t p = 250000;
	while(p>0)
		p--;
	//HAL_I2C_DeInit(&hi2c2);
	//p = 250000;
	//while(p>0)
	//	p--;
	//MX_I2C1_Init();
}

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
uint8_t dt[256];
dt[0] = reg;
uint8_t i;
for(i = 0; i < count; i++)
dt[i+1] = data[i];
HAL_I2C_Master_Transmit(&hi2c2, address, dt, count+1, 10);
}


void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c2, address, dt, 2, 10);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// ________ _____  _____  _		 ___________	 ___			 ___________	 ________
// |   __  ||   |  |   | |_|    |	 ___	|	|	|			|	 _______|	|	 _	 \
// |  |__| ||   |  |   |	    |	|	|	|	|	|			|	|___		|	| \   |
// |  _____||   |  |   |		|	|	|	|	|	|			|	 ___|		|	|  |  |
// |  |		 \  \  /  /			|	|	|	|	|	|_______	|	|_______	|	|  |  |
// |  |		  \	 \/  /    _		|	|___|	|	|			|	|			|	|	|_/   |
// |__|		   \____/	 |_|	|___________|	|___________|	|___________|	|________/
//
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////[BASE MENU SCREEN]////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void SSD1306_Menu()
{
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0
	SSD1306_Puts ("Music Synth", &Font_11x18, 1); 	// print Music Synth
	SSD1306_GotoXY (0, 20); 						// go to 0, 20
	SSD1306_Puts ("By:", &Font_7x10, 1); 			// print by
	SSD1306_GotoXY (0, 30);							// go to 0, 30
	SSD1306_Puts ("Joshua Mendoza", &Font_7x10, 1);	// print group member 1
	SSD1306_GotoXY (0, 40);							// go to 0, 40
	SSD1306_Puts ("Megan Abundo", &Font_7x10, 1);	// print group member 2
	SSD1306_GotoXY (0, 50);							// go to 0,50
	SSD1306_Puts ("Paris Villarrial", &Font_7x10, 1);// print group member 3
	SSD1306_UpdateScreen(); 						// update screen with new input information

}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////[MUSIC FUNCTIONS]///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//	Octave #	Note Numbers
//		C	C#	D	D#	E	F	F#	G	G#	A	A#	B
//	-1	0	1	2	3	4	5	6	7	8	9	10	11
//	0	12	13	14	15	16	17	18	19	20	21	22	23
//	1	24	25	26	27	28	29	30	31	32	33	34	35
//	2	36	37	38	39	40	41	42	43	44	45	46	47
//	3	48	49	50	51	52	53	54	55	56	57	58	59
//	4	60	61	62	63	64	65	66	67	68	69	70	71
//	5	72	73	74	75	76	77	78	79	80	81	82	83
//	6	84	85	86	87	88	89	90	91	92	93	94	95
//	7	96	97	98	99	100	101	102	103	104	105	106	107
//	8	108	109	110	111	112	113	114	115	116	117	118	119
//	9	120	121	122	123	124	125	126	127


//This table lists all MIDI Note Numbers by octave.
//The absolute octave number designations are based on Middle C = C4, which is an arbitrary but widely used assignment.

//NOTE:
//when changing the X and Y coordinates for text, make sure the font size is
//taken into account to keep all the proper spacing between rows and columns

////////////////////
////////////////////[OCTAVE -1]///////////////////////////
////////////////////

void SSD1306_Note0(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note1(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note2(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note3(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note4(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note5(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note6(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note7(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note8(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note9(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note10(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: -1", &Font_11x18, 1);  	// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note11(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

////////////////////
////////////////////[OCTAVE 0]///////////////////////////
///////////////////

void SSD1306_Note12(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note13(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note14(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note15(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note16(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note17(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note18(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note19(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note20(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note21(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note22(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note23(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 0", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

/////////////////////
////////////////////[OCTAVE 1]///////////////////////////
////////////////////

void SSD1306_Note24(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note25(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note26(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note27(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note28(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note29(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note30(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note31(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note32(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note33(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note34(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note35(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 1", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

/////////////////////
////////////////////[OCTAVE 2]///////////////////////////
////////////////////

void SSD1306_Note36(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note37(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note38(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note39(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note40(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note41(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note42(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note43(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note44(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note45(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note46(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note47(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 2", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

/////////////////////
////////////////////[OCTAVE 3]///////////////////////////
////////////////////

void SSD1306_Note48(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note49(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note50(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note51(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note52(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note53(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note54(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note55(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note56(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note57(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note58(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note59(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 3", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

/////////////////////
////////////////////[OCTAVE 4]///////////////////////////
////////////////////

void SSD1306_Note60(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note61(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note62(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note63(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note64(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note65(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note66(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note67(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note68(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note69(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note70(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note71(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 4", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


/////////////////////
////////////////////[OCTAVE 5]///////////////////////////
////////////////////

void SSD1306_Note72(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note73(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note74(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note75(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note76(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note77(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note78(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note79(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note80(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note81(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note82(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note83(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 5", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

/////////////////////
////////////////////[OCTAVE 6]///////////////////////////
////////////////////

void SSD1306_Note84(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note85(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note86(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note87(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note88(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note89(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note90(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note91(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note92(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note93(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note94(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note95(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 6", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


/////////////////////
////////////////////[OCTAVE 7]///////////////////////////
////////////////////

void SSD1306_Note96(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note97(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note98(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note99(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note100(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note101(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note102(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note103(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note104(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note105(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note106(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note107(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 7", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


/////////////////////
////////////////////[OCTAVE 8]///////////////////////////
////////////////////

void SSD1306_Note108(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note109(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note110(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note111(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note112(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note113(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note114(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note115(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note116(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note117(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note118(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: A#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note119(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: B", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 8", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


/////////////////////
////////////////////[OCTAVE 9]///////////////////////////
////////////////////

void SSD1306_Note120(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}


void SSD1306_Note121(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: C#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note122(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note123(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: D#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note124(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: E", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note125(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note126(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: F#", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}

void SSD1306_Note127(){
	SSD1306_Init (); 								// initialize the OLED screen
	SSD1306_Clear();								// clear screen of any previous input information
	SSD1306_GotoXY (0, 0); 							// go to 0, 0 (top left corner of the screen)
	SSD1306_Puts ("Wave: Sine", &Font_11x18, 1);	// display current wave
	SSD1306_GotoXY (0,20); 							// go to 0, 20 (dropping to a new row below)
	SSD1306_Puts ("Note: G", &Font_11x18, 1); 		// display current note
	SSD1306_GotoXY (0, 40); 						// go to 0, 40 (dropping to a new row below)
	SSD1306_Puts ("Octv: 9", &Font_11x18, 1);  		// display current octave
	SSD1306_UpdateScreen();							// update screen with new input information
}
