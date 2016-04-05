#include "graphics.h"
#include "levels.h"

#include "startsplashsized.h"
#include "techringsized.h"
#include "gameoversized.h"

#include "footballsized3.h"
#include "GTsized2.h"

#include "redBlock.h"
#include "whiteBlock.h"

#define DRAW_BLACK_BLOCK(r, c) drawRect(r, c, 16, 8, BLACK)
#define DRAW_RED_BLOCK(r, c) drawImage3(r, c, 16, 8, redBlock)
#define DRAW_WHITE_BLOCK(r, c) drawImage3(r, c, 16, 8, whiteBlock)

#define DRAW_BLACK_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_BLACK_BLOCK(r, i)
#define DRAW_RED_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_RED_BLOCK(r, i)
#define DRAW_WHITE_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_WHITE_BLOCK(r, i)

//blocks are 16 pixels wide and 8 pixels high
//actual game screen starts 10 rows down at column 0

//Level 1 has 165 total blocks, 15 wide, 11 high
void createLevel1(unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball) {

  *blockCounter = L1_NUMBLOCKS;

  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 15; j++) {
      blocks[(i * 15) + j].row = 10 + (i * 8);
      blocks[(i * 15) + j].col = (j * 16);
    }
  }

  platform -> row = 140;
  platform -> col = 105;
  platform -> rdel = 0;
  platform -> cdel = 0;

  ball -> row = 105;
  ball -> col = 110;
  ball -> rdel = 1;
  ball -> cdel = 0;

  drawImage3(10, 0, 240, 150, techringsized);

  drawSprite(platform -> row, platform -> col, 30, 15, GTsized2);

  drawSprite(ball -> row, ball -> col, 10, 8, footballsized3);

  DRAW_RED_BLOCKS(10, 0, 6);
  DRAW_WHITE_BLOCKS(10, 96, 3);
  DRAW_RED_BLOCKS(10, 144, 6);

  DRAW_RED_BLOCKS(18, 0, 5);
  DRAW_WHITE_BLOCK(18, 80);
  DRAW_BLACK_BLOCKS(18, 96, 3);
  DRAW_WHITE_BLOCK(18, 144);
  DRAW_RED_BLOCKS(18, 160, 5);

  DRAW_RED_BLOCKS(26, 0, 4);
  DRAW_WHITE_BLOCK(26, 64);
  DRAW_BLACK_BLOCKS(26, 80, 5);
  DRAW_WHITE_BLOCK(26, 160);
  DRAW_RED_BLOCKS(26, 176, 4);

  DRAW_RED_BLOCKS(34, 0, 3);
  DRAW_WHITE_BLOCK(34, 48);
  DRAW_BLACK_BLOCKS(34, 64, 2);
  DRAW_WHITE_BLOCKS(34, 96, 4);
  DRAW_BLACK_BLOCK(34, 160);
  DRAW_WHITE_BLOCK(34, 176);
  DRAW_RED_BLOCKS(34, 192, 3);;

  DRAW_RED_BLOCKS(42, 0, 3);
  DRAW_WHITE_BLOCK(42, 48);
  DRAW_BLACK_BLOCK(42, 64);
  DRAW_WHITE_BLOCKS(42, 80, 7);
  DRAW_RED_BLOCKS(42, 192, 3);

  DRAW_RED_BLOCKS(50, 0, 3);
  DRAW_WHITE_BLOCK(50, 48);
  DRAW_BLACK_BLOCK(50, 64);
  DRAW_WHITE_BLOCKS(50, 80, 2);
  DRAW_BLACK_BLOCKS(50, 112, 4);
  DRAW_WHITE_BLOCK(50, 176);
  DRAW_RED_BLOCKS(50, 192, 3);

  DRAW_RED_BLOCKS(58, 0, 3);
  DRAW_WHITE_BLOCK(58, 48);
  DRAW_BLACK_BLOCK(58, 64);
  DRAW_WHITE_BLOCKS(58, 80, 5);
  DRAW_BLACK_BLOCK(58, 160);
  DRAW_WHITE_BLOCK(58, 176);
  DRAW_RED_BLOCKS(58, 192, 3);

  DRAW_RED_BLOCKS(66, 0, 3);
  DRAW_WHITE_BLOCK(66, 48);
  DRAW_BLACK_BLOCKS(66, 64, 2);
  DRAW_WHITE_BLOCKS(66, 96, 4);
  DRAW_BLACK_BLOCK(66, 160);
  DRAW_WHITE_BLOCK(66, 176);
  DRAW_RED_BLOCKS(66, 192, 3);

  DRAW_RED_BLOCKS(74, 0, 4);
  DRAW_WHITE_BLOCK(74, 64);
  DRAW_BLACK_BLOCKS(74, 80, 5);
  DRAW_WHITE_BLOCK(74, 160);
  DRAW_RED_BLOCKS(74, 176, 4);

  DRAW_RED_BLOCKS(82, 0, 5);
  DRAW_WHITE_BLOCK(82, 80);
  DRAW_BLACK_BLOCKS(82, 96, 3);
  DRAW_WHITE_BLOCK(82, 144);
  DRAW_RED_BLOCKS(82, 160, 5);

  DRAW_RED_BLOCKS(90, 0, 6);
  DRAW_WHITE_BLOCKS(90, 96, 3);
  DRAW_RED_BLOCKS(90, 144, 6);
}
