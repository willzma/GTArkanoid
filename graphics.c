#include "graphics.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

// Outdated and unused, but sets an individual pixel in the videoBuffer
void setPixel(int r, int c, unsigned short color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

// Outdated and unused, but creates a flat color rectangle
void drawRect(int row, int col, int width, int height, unsigned short color) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = &color;
		DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

// Unused delayer of UI thread
void delay(int n) {
	volatile int x = 0;
	for(int i = 0; i < n * 10000; i++) {
		x++;
	}
}

// Tries to keep frame times consistent
void waitForVBlank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

// Outdated and unused, but fills the screen with a single color
void fillScreen(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

// Fairly fast DMA method to draw an image beginning at the specified row and col
void drawImage3(int row, int col, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = image + (r * width);
		DMA[DMA_CHANNEL_3].dst = videoBuffer + ((row + r) * 240) + col;
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
	}
}

// Fast DMA method that takes in a row and col, and a width and height, creating
// a rectangle at the specified coordinates, replacing the pixels in the specified
// rectangle with the equivalent pixels in a 240x150 full splash screen,
// used for quickly replacing previously occupied pixels for moving objects
void replace(int row, int col, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = image + ((row + r - 10) * 240) + col;
		DMA[DMA_CHANNEL_3].dst = videoBuffer + ((row + r) * 240) + col;
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON;
	}
}

// Compromise to draw non-rectangular shapes, namely the Ramblin' Wreck platform
// and the football ball, both of which would not look too good otherwise;
// this doesn't draw the magenta color that is in those pictures, creating a sort of sprite
void drawSprite(int r, int c, int width, int height, const u16* image) {
  for (int j = r; j < height + r; j++) {		// for sprites, i.e. non-rectangular
    for (int i = c; i < width + c; i++) {		// looking shapes
      if (image[(j - r) * width + (i - c)] != 31775) {
        videoBuffer[j * 240 + i] = image[(j - r) * width + (i - c)];
      }
    }
  }
}

// Draws a character as specified in font.c at the specified row and col
void drawChar(int row, int col, char ch, u16 color) {
	for(int r = 0; r < 8; r++) {
		for(int c = 0; c < 6; c++) {
			if(fontdata_6x8[OFFSET(r, c, 6) + ch * 48]) {
				setPixel(row + r, col + c, color);
			}
		}
	}
}

// Draws a String using characters as specified in font.c
void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}
