#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "input.h"

#include "levels.h"

#include "startsplashsized.h"
#include "techringsized.h"
#include "buzz.h"
#include "florida.h"
#include "gameoversized.h"
#include "you_win.h"

#include "footballsized3.h"
#include "GTsized2.h"

// Enumeration of gameState machine
enum gameState {
  START,
  START_NODRAW,
  LEVEL1,
  LEVEL1_NODRAW,
  LEVEL2,
  LEVEL2_NODRAW,
  LEVEL3,
  LEVEL3_NODRAW,
  YOU_WIN,
  GAME_OVER,
  GAME_OVER_NODRAW
};

// gameState prototypes
void handlePlayerPlatformInput(PLATFORM* plat);
void handleGameState(enum gameState* state, unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball, unsigned int* score, char scoreBuffer[], const u16* splash);

int main() {

  // Initialize graphics on screen
  INIT_MODE_3;
	enum gameState state = START;

  PLATFORM platform;
  platform.image = GTsized2;

  BALL ball;
  ball.image = footballsized3;

  // Allocate spaces for block structs for each level
  BLOCK L1_BLOCKS[L1_NUMBLOCKS];
  BLOCK L2_BLOCKS[L2_NUMBLOCKS];
  BLOCK L3_BLOCKS[L3_NUMBLOCKS];

  // Allocate space for block counter
  unsigned int numBlocks = 0;

  // Initialize button listeners
  unsigned int aPressed = 0;
  unsigned int selectPressed = 0;

  // Score counters
  unsigned int score = 0;
  unsigned int highScore = 0;

  // Strings to write scores to for later update onscreen
  char scoreBuffer[sizeof(unsigned int) * 3 + 2];
  char highScoreBuffer[sizeof(unsigned int) * 3 + 2];

  while (1) {
    waitForVBlank();
    switch(state) {
      case START: {
        DRAW_START_SPLASH;
        drawString(0, 0, "SCORE", WHITE);
        score = 0;
        drawRect(0, 40, 40, 10, BLACK);
        sprintf(scoreBuffer, "%d", score);
        drawString(0, 40, scoreBuffer, WHITE);
        drawString(0, 140, "HI-SCORE", WHITE);
        drawRect(0, 200, 40, 10, BLACK);
        sprintf(highScoreBuffer, "%d", highScore);
        drawString(0, 200, highScoreBuffer, WHITE);
        state = START_NODRAW;
      }break; case START_NODRAW: {
        if (KEY_DOWN_NOW(BUTTON_A) && !aPressed) {
          aPressed = 1;
          state = LEVEL1;
        } else if (!KEY_DOWN_NOW(BUTTON_A)){
          aPressed = 0;
        }
      }break; case LEVEL1: {
          createLevel1(&numBlocks, L1_BLOCKS, &platform, &ball);
          state = LEVEL1_NODRAW;
      }break; case LEVEL1_NODRAW: {
        handleGameState(&state, &numBlocks, L1_BLOCKS, &platform, &ball, &score, scoreBuffer, buzz);
      }break; case LEVEL2: {
          createLevel2(&numBlocks, L2_BLOCKS, &platform, &ball);
          state = LEVEL2_NODRAW;
      }break; case LEVEL2_NODRAW: {
        handleGameState(&state, &numBlocks, L2_BLOCKS, &platform, &ball, &score, scoreBuffer, florida);
      }break;case LEVEL3: {
          createLevel3(&numBlocks, L3_BLOCKS, &platform, &ball);
          state = LEVEL3_NODRAW;
      }break; case LEVEL3_NODRAW: {
        handleGameState(&state, &numBlocks, L3_BLOCKS, &platform, &ball, &score, scoreBuffer, techringsized);
      }break;case YOU_WIN: {
          DRAW_YOU_WIN_SPLASH;

          if (score > highScore) {
            highScore = score;
            drawRect(0, 200, 40, 10, BLACK);
            sprintf(highScoreBuffer, "%d", highScore);
            drawString(0, 200, highScoreBuffer, WHITE);
          }
      }break; case GAME_OVER: {
          DRAW_GAME_OVER_SPLASH;

          if (score > highScore) {
            highScore = score;
            drawRect(0, 200, 40, 10, BLACK);
            sprintf(highScoreBuffer, "%d", highScore);
            drawString(0, 200, highScoreBuffer, WHITE);
          }

          score = 0;
          drawRect(0, 40, 40, 10, BLACK);
          sprintf(scoreBuffer, "%d", score);
          drawString(0, 40, scoreBuffer, WHITE);
          state = GAME_OVER_NODRAW;
      }break; case GAME_OVER_NODRAW: {
        if (KEY_DOWN_NOW(BUTTON_A) && !aPressed) {
          aPressed = 1;
          state = START;
        } else if (!KEY_DOWN_NOW(BUTTON_A)){
          aPressed = 0;
        }
      }break;
    }

    if (KEY_DOWN_NOW(BUTTON_SELECT) && !selectPressed) {
      selectPressed = -1;
      state = START;
    } else if (!KEY_DOWN_NOW(BUTTON_SELECT)) {
      selectPressed = 0;
    }

  }

  return 0;
}

// Complex method that handles transition between level states, increments and
// decrements the blockCounter, checking for win conditions, detects collisions within
// an array of blocks with the ball, as well as collisions between the platform
// and the ball, updates scores, and replaces drawn-over pixels from the platform, ball, and blocks
void handleGameState(enum gameState* state, unsigned int* blockCounter, BLOCK blocks[],
  PLATFORM* platform, BALL* ball, unsigned int* score, char scoreBuffer[], const u16* splash) {

    // Check the blockCounter for a win or advancement condition
    if (!*blockCounter) {
        switch(*state) {
          case START: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case START_NODRAW: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case LEVEL1: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case LEVEL1_NODRAW: {
             *state = LEVEL2;
             delay(1);
          } break; case LEVEL2: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case LEVEL2_NODRAW: {
             *state = LEVEL3;
             delay(1);
          } break; case LEVEL3: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case LEVEL3_NODRAW: {
             *state = YOU_WIN;
          } break; case YOU_WIN: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case GAME_OVER: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break; case GAME_OVER_NODRAW: {
              // THIS STATE HANDLED IN MAIN LOOP
          } break;
        }
    }

    handlePlayerPlatformInput(platform);

    // Only redraw the platform if we've moved
    if (platform -> cdel != 0) {

        // Update platform position
        platform -> col += platform -> cdel;

        // Replace the old platform drawing with the splash screen behind it
        replace(platform -> row, platform -> col - platform -> cdel, 30, 15, splash);

        // Draw the platform in its new position
        drawSprite(platform -> row,
          platform -> col, 30, 15, GTsized2);
    }

    // Update ball position
    ball -> col += ball -> cdel;
    ball -> row += ball -> rdel;

    // Replace the old ball drawing with the splash screen behind it
    replace(ball -> row - ball -> rdel, ball -> col - ball -> cdel, 10, 8, splash);

    // Draw the ball in its new position
    drawSprite(ball -> row,
      ball -> col, 10, 8, footballsized3);

      // Check if the ball has collided with the platform
      if (ball -> row + 7 >= platform -> row && ball -> row + 7 <= platform -> row + 15) {
        if (ball -> col + 6 >= platform -> col && ball -> col <= platform -> col + 26) {
          ball -> rdel = -1;
          ball -> cdel = 1 * (platform -> cdel / 2);
        }
      }

      // Check if the ball has collided with the bounds of the screen
      if (ball -> row > 160) {
        *state = GAME_OVER;
      }

      if (ball -> row == 10) {
        ball -> rdel = 1;
      }

      if (ball -> col == 0) {
        ball -> cdel = 1;
      }

      if (ball -> col == 230) {
        ball -> cdel = -1;
      }

      // Loop that checks if the ball has collided with any blocks
      for (int i = 0; i < L1_NUMBLOCKS; i++) {
         // Check bottom side of a block
        if (ball -> row == blocks[i].row + 8
          && (ball -> col + 10 >= blocks[i].col && ball -> col <= blocks[i].col + 16)) {
            ball -> rdel = 1;

            *score += 20;
            drawRect(0, 40, 40, 10, BLACK);
            sprintf(scoreBuffer, "%d", *score);
            drawString(0, 40, scoreBuffer, WHITE);

            *blockCounter = *blockCounter - 1;

            replace(blocks[i].row, blocks[i].col, 16, 8, splash);

            blocks[i].col = -100;
            blocks[i].row = -100;
        } else if (ball -> row + 8 == blocks[i].row
          && (ball -> col + 10 >= blocks[i].col && ball -> col <= blocks[i].col + 16)) { // Check top side of a block
              ball -> rdel = -1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, splash);

              blocks[i].col = -100;
              blocks[i].row = -100;
        } else if (ball -> row + 8 >= blocks[i].row && ball -> row <= blocks[i].row + 8
          && ball -> col == blocks[i].col + 16) { // Check left side of a block
              ball -> cdel = 1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, splash);

              blocks[i].col = -100;
              blocks[i].row = -100;
        } else if (ball -> row + 8 >= blocks[i].row && ball -> row <= blocks[i].row + 8
          && ball -> col + 10 == blocks[i].col) { // Check right side of a block
              ball -> cdel = -1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, splash);

              blocks[i].col = -100;
              blocks[i].row = -100;
        }
      }
}

// Method that handles player input, which moves the platform
void handlePlayerPlatformInput(PLATFORM* platform) {
  if (KEY_DOWN_NOW(BUTTON_LEFT) && !(platform -> col <= 0)) {
    platform -> cdel = -2;
  } else if (KEY_DOWN_NOW(BUTTON_RIGHT) && !(platform -> col >= 210)) {
    platform -> cdel = 2;
  } else {
    platform -> cdel = 0;
  }
}
