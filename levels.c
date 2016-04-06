#include "graphics.h"
#include "levels.h"

// Game splash screens
#include "startsplashsized.h"
#include "techringsized.h"
#include "buzz.h"
#include "florida.h"
#include "gameoversized.h"
#include "you_win.h"

// Ball and platform, respectively
#include "footballsized3.h"
#include "GTsized2.h"

#include "blackBlock.h"
#include "blueBlock.h"
#include "goldBlock.h"
#include "greenBlock.h"
#include "lightBlueBlock.h"
#include "maroonBlock.h"
#include "orangeBlock.h"
#include "redBlock.h"
#include "whiteBlock.h"

// Draws a block beginning at the specified row and column
#define DRAW_BLACK_BLOCK(r, c) drawImage3(r, c, 16, 8, blackBlock)
#define DRAW_BLUE_BLOCK(r, c) drawImage3(r, c, 16, 8, blueBlock)
#define DRAW_GOLD_BLOCK(r, c) drawImage3(r, c, 16, 8, goldBlock)
#define DRAW_GREEN_BLOCK(r, c) drawImage3(r, c, 16, 8, greenBlock)
#define DRAW_LIGHT_BLUE_BLOCK(r, c) drawImage3(r, c, 16, 8, lightBlueBlock)
#define DRAW_MAROON_BLOCK(r, c) drawImage3(r, c, 16, 8, maroonBlock)
#define DRAW_ORANGE_BLOCK(r, c) drawImage3(r, c, 16, 8, orangeBlock)
#define DRAW_RED_BLOCK(r, c) drawImage3(r, c, 16, 8, redBlock)
#define DRAW_WHITE_BLOCK(r, c) drawImage3(r, c, 16, 8, whiteBlock)

// Draws num blocks beginning at the specified row and column
#define DRAW_BLACK_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_BLACK_BLOCK(r, i)
#define DRAW_BLUE_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_BLUE_BLOCK(r, i)
#define DRAW_GOLD_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_GOLD_BLOCK(r, i)
#define DRAW_GREEN_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_GREEN_BLOCK(r, i)
#define DRAW_LIGHT_BLUE_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_LIGHT_BLUE_BLOCK(r, i)
#define DRAW_MAROON_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_MAROON_BLOCK(r, i)
#define DRAW_ORANGE_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_ORANGE_BLOCK(r, i)
#define DRAW_RED_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_RED_BLOCK(r, i)
#define DRAW_WHITE_BLOCKS(r, c, num) for (int i = c; i < c + 16 * num; i += 16) DRAW_WHITE_BLOCK(r, i)

// blocks are 16 pixels wide and 8 pixels high
// actual game screen starts 10 rows down at column 0

// Each level has 165 total blocks, 15 wide, 11 high

// Each blocks of DRAWS is going to correspond to a row in the game

void createLevel1(unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball) {

    // Initializes a counter to determine level advancement or win conditions
    *blockCounter = L1_NUMBLOCKS;

    // Initializes the array of blocks that will be checked against for collision
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 15; j++) {
        blocks[(i * 15) + j].row = 10 + (i * 8);
        blocks[(i * 15) + j].col = (j * 16);
      }
    }

    // Initialize platform coordinates and speeds
    platform -> row = 140;
    platform -> col = 105;
    platform -> rdel = 0;
    platform -> cdel = 0;

    // Initialize ball coordinates and speeds
    ball -> row = 105;
    ball -> col = 110;
    ball -> rdel = 1;
    ball -> cdel = 0;

    // Draw the splash screen for this particular level
    drawImage3(10, 0, 240, 150, buzz);

    // Draw the Ramblin' Wreck platform
    drawSprite(platform -> row, platform -> col, 30, 15, GTsized2);

    // Draw the ball
    drawSprite(ball -> row, ball -> col, 10, 8, footballsized3);

    DRAW_WHITE_BLOCKS(10, 0, 2);
    DRAW_MAROON_BLOCK(10, 32);
    DRAW_WHITE_BLOCKS(10, 48, 5);
    DRAW_MAROON_BLOCKS(10, 128, 6);
    DRAW_WHITE_BLOCK(10, 224);

    DRAW_WHITE_BLOCKS(18, 0, 2);
    DRAW_MAROON_BLOCK(18, 32);
    DRAW_WHITE_BLOCKS(18, 48, 5);
    DRAW_MAROON_BLOCKS(18, 128, 6);
    DRAW_WHITE_BLOCK(18, 224);

    DRAW_WHITE_BLOCKS(26, 0, 2);
    DRAW_MAROON_BLOCKS(26, 32, 2);
    DRAW_WHITE_BLOCKS(26, 64, 3);
    DRAW_MAROON_BLOCKS(26, 112, 2);
    DRAW_WHITE_BLOCKS(26, 144, 2);
    DRAW_MAROON_BLOCK(26, 176);
    DRAW_WHITE_BLOCKS(26, 192, 3);

    DRAW_WHITE_BLOCKS(34, 0, 2);
    DRAW_MAROON_BLOCKS(34, 32, 2);
    DRAW_WHITE_BLOCKS(34, 64, 3);
    DRAW_MAROON_BLOCKS(34, 112, 2);
    DRAW_WHITE_BLOCKS(34, 144, 2);
    DRAW_MAROON_BLOCK(34, 176);
    DRAW_WHITE_BLOCKS(34, 192, 3);

    DRAW_WHITE_BLOCKS(42, 0, 3);
    DRAW_MAROON_BLOCK(42, 48);
    DRAW_WHITE_BLOCKS(42, 64, 3);
    DRAW_MAROON_BLOCK(42, 112);
    DRAW_WHITE_BLOCKS(42, 128, 3);
    DRAW_MAROON_BLOCK(42, 176);
    DRAW_WHITE_BLOCKS(42, 192, 3);

    DRAW_WHITE_BLOCKS(50, 0, 3);
    DRAW_MAROON_BLOCKS(50, 48, 2);
    DRAW_WHITE_BLOCK(50, 80);
    DRAW_MAROON_BLOCKS(50, 96, 2);
    DRAW_WHITE_BLOCKS(50, 128, 3);
    DRAW_MAROON_BLOCK(50, 176);
    DRAW_WHITE_BLOCKS(50, 192, 3);

    DRAW_WHITE_BLOCKS(58, 0, 3);
    DRAW_MAROON_BLOCKS(58, 48, 2);
    DRAW_WHITE_BLOCK(58, 80);
    DRAW_MAROON_BLOCKS(58, 96, 2);
    DRAW_WHITE_BLOCKS(58, 128, 3);
    DRAW_MAROON_BLOCK(58, 176);
    DRAW_WHITE_BLOCKS(58, 192, 3);

    DRAW_WHITE_BLOCKS(66, 0, 4);
    DRAW_MAROON_BLOCK(66, 64);
    DRAW_WHITE_BLOCK(66, 80);
    DRAW_MAROON_BLOCK(66, 96);
    DRAW_WHITE_BLOCKS(66, 112, 4);
    DRAW_MAROON_BLOCK(66, 176);
    DRAW_WHITE_BLOCKS(66, 192, 3);

    DRAW_WHITE_BLOCKS(74, 0, 4);
    DRAW_MAROON_BLOCKS(74, 64, 3);
    DRAW_WHITE_BLOCKS(74, 112, 4);
    DRAW_MAROON_BLOCK(74, 176);
    DRAW_WHITE_BLOCKS(74, 192, 3);

    DRAW_WHITE_BLOCKS(82, 0, 4);
    DRAW_MAROON_BLOCKS(82, 64, 3);
    DRAW_WHITE_BLOCKS(82, 112, 4);
    DRAW_MAROON_BLOCK(82, 176);
    DRAW_WHITE_BLOCKS(82, 192, 3);

    DRAW_WHITE_BLOCKS(90, 0, 5);
    DRAW_MAROON_BLOCKS(90, 80, 1);
    DRAW_WHITE_BLOCKS(90, 96, 5);
    DRAW_MAROON_BLOCK(90, 176);
    DRAW_WHITE_BLOCKS(90, 192, 3);
}

void createLevel2(unsigned int* blockCounter, BLOCK blocks[L2_NUMBLOCKS],
  PLATFORM* platform, BALL* ball) {

    // Initializes a counter to determine level advancement or win conditions
    *blockCounter = L1_NUMBLOCKS;

    // Initializes the array of blocks that will be checked against for collision
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 15; j++) {
        blocks[(i * 15) + j].row = 10 + (i * 8);
        blocks[(i * 15) + j].col = (j * 16);
      }
    }

    // Initialize platform coordinates and speeds
    platform -> row = 140;
    platform -> col = 105;
    platform -> rdel = 0;
    platform -> cdel = 0;

    // Initialize ball coordinates and speeds
    ball -> row = 105;
    ball -> col = 110;
    ball -> rdel = 1;
    ball -> cdel = 0;

    // Draw the splash screen for this particular level
    drawImage3(10, 0, 240, 150, florida);

    // Draw the Ramblin' Wreck platform
    drawSprite(platform -> row, platform -> col, 30, 15, GTsized2);

    // Draw the ball
    drawSprite(ball -> row, ball -> col, 10, 8, footballsized3);

    DRAW_WHITE_BLOCKS(10, 0, 3);
    DRAW_ORANGE_BLOCKS(10, 48, 2);
    DRAW_WHITE_BLOCKS(10, 80, 5);
    DRAW_GREEN_BLOCKS(10, 160, 2);
    DRAW_WHITE_BLOCKS(10, 192, 3);

    DRAW_WHITE_BLOCKS(18, 0, 3);
    DRAW_ORANGE_BLOCKS(18, 48, 2);
    DRAW_WHITE_BLOCKS(18, 80, 5);
    DRAW_GREEN_BLOCKS(18, 160, 2);
    DRAW_WHITE_BLOCKS(18, 192, 3);

    DRAW_WHITE_BLOCKS(26, 0, 3);
    DRAW_ORANGE_BLOCKS(26, 48, 2);
    DRAW_WHITE_BLOCKS(26, 80, 5);
    DRAW_GREEN_BLOCKS(26, 160, 2);
    DRAW_WHITE_BLOCKS(26, 192, 3);

    DRAW_WHITE_BLOCKS(34, 0, 3);
    DRAW_ORANGE_BLOCKS(34, 48, 2);
    DRAW_WHITE_BLOCKS(34, 80, 5);
    DRAW_GREEN_BLOCKS(34, 160, 2);
    DRAW_WHITE_BLOCKS(34, 192, 3);

    DRAW_WHITE_BLOCKS(42, 0, 3);
    DRAW_ORANGE_BLOCKS(42, 48, 2);
    DRAW_WHITE_BLOCKS(42, 80, 5);
    DRAW_GREEN_BLOCKS(42, 160, 2);
    DRAW_WHITE_BLOCKS(42, 192, 3);

    DRAW_WHITE_BLOCKS(50, 0, 3);
    DRAW_ORANGE_BLOCKS(50, 48, 2);
    DRAW_WHITE_BLOCKS(50, 80, 5);
    DRAW_GREEN_BLOCKS(50, 160, 2);
    DRAW_WHITE_BLOCKS(50, 192, 3);

    DRAW_WHITE_BLOCKS(58, 0, 3);
    DRAW_ORANGE_BLOCKS(58, 48, 2);
    DRAW_WHITE_BLOCKS(58, 80, 5);
    DRAW_GREEN_BLOCKS(58, 160, 2);
    DRAW_WHITE_BLOCKS(58, 192, 3);

    DRAW_WHITE_BLOCKS(66, 0, 3);
    DRAW_ORANGE_BLOCKS(66, 48, 3);
    DRAW_WHITE_BLOCKS(66, 96, 3);
    DRAW_GREEN_BLOCKS(66, 144, 3);
    DRAW_WHITE_BLOCKS(66, 192, 3);

    DRAW_WHITE_BLOCKS(74, 0, 4);
    DRAW_ORANGE_BLOCKS(74, 64, 2);
    DRAW_WHITE_BLOCKS(74, 96, 3);
    DRAW_GREEN_BLOCKS(74, 144, 2);
    DRAW_WHITE_BLOCKS(74, 176, 4);

    DRAW_WHITE_BLOCKS(82, 0, 4);
    DRAW_ORANGE_BLOCKS(82, 64, 3);
    DRAW_WHITE_BLOCKS(82, 112, 1);
    DRAW_GREEN_BLOCKS(82, 128, 3);
    DRAW_WHITE_BLOCKS(82, 176, 4);

    DRAW_WHITE_BLOCKS(90, 0, 5);
    DRAW_ORANGE_BLOCKS(90, 80, 2);
    DRAW_WHITE_BLOCKS(90, 112, 1);
    DRAW_GREEN_BLOCKS(90, 128, 2);
    DRAW_WHITE_BLOCKS(90, 160, 5);
}

void createLevel3(unsigned int* blockCounter, BLOCK blocks[L3_NUMBLOCKS],
  PLATFORM* platform, BALL* ball) {

    // Initializes a counter to determine level advancement or win conditions
    *blockCounter = L1_NUMBLOCKS;

    // Initializes the array of blocks that will be checked against for collision
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 15; j++) {
        blocks[(i * 15) + j].row = 10 + (i * 8);
        blocks[(i * 15) + j].col = (j * 16);
      }
    }

    // Initialize platform coordinates and speeds
    platform -> row = 140;
    platform -> col = 105;
    platform -> rdel = 0;
    platform -> cdel = 0;

    // Initialize ball coordinates and speeds
    ball -> row = 105;
    ball -> col = 110;
    ball -> rdel = 1;
    ball -> cdel = 0;

    // Draw the splash screen for this particular level
    drawImage3(10, 0, 240, 150, techringsized);

    // Draw the Ramblin' Wreck platform
    drawSprite(platform -> row, platform -> col, 30, 15, GTsized2);

    // Draw the ball
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
