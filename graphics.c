#include "graphics.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int r, int c, unsigned short color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int row, int col, int width, int height, unsigned short color) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = &color;
		DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void delay(int n) {
	volatile int x = 0;
	for(int i=0; i<n*10000; i++) {
		x++;
	}
}

void waitForVBlank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void fillScreen(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

void drawImage3(int row, int col, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = image + (r * width);
		DMA[DMA_CHANNEL_3].dst = videoBuffer + ((row + r) * 240) + col;
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
	}
}

void replaceBlock(int row, int col, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[DMA_CHANNEL_3].src = image + ((row + r - 10) * 240) + col;
		DMA[DMA_CHANNEL_3].dst = videoBuffer + ((row + r) * 240) + col;
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON;
	}
}

void drawSprite(int r, int c, int width, int height, const u16* image) {
  for (int j = r; j < height + r; j++) {		// for sprites, i.e. non-rectangular
    for (int i = c; i < width + c; i++) {		// looking shapes
      if (image[(j - r) * width + (i - c)] != 31775) {
        videoBuffer[j * 240 + i] = image[(j - r) * width + (i - c)];
      }
    }
  }
}

void drawChar(int row, int col, char ch, u16 color) {
	for(int r=0; r<8; r++) {
		for(int c=0; c<6; c++) {
			if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}
