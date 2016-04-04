#include "graphics.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

#include "levels.h"

#include "startsplashsized.h"
#include "techringsized.h"
#include "gameoversized.h"

#include "footballsized3.h"
#include "GTsized2.h"

enum gameState {
  START,
  START_NODRAW,
  LEVEL1,
  LEVEL1_NODRAW,
  GAME_OVER,
  GAME_OVER_NODRAW
};

typedef struct {
  int row;
	int col;
	int rdel;
	int cdel;
	const u16* image;
} PLATFORM;

typedef struct {
  int row;
  int col;
  int rdel;
  int cdel;
  const u16* image;
} BALL;

int main() {
  REG_DISPCNT = MODE_3 | BG2_EN;
	enum gameState state = START;

  PLATFORM platform;
  platform.row = 140;
  platform.col = 105;
  platform.rdel = 0;
  platform.cdel = 0;
  platform.image = GTsized2;

  BALL ball;
  ball.row = 105;
  ball.col = 110;
  ball.rdel = 1;
  ball.cdel = 0;
  ball.image = footballsized3;

  BLOCK L1_BLOCKS[L1_NUMBLOCKS];

  int numBlocks = 0;

  unsigned int aPressed = 0;
  unsigned int score = 0;
  unsigned int highScore = 0;

  char scoreBuffer[sizeof(unsigned int) * 3 + 2];
  char highScoreBuffer[sizeof(unsigned int) * 3 + 2];

  while (1) {
    waitForVBlank();
    switch(state) {
      case START: {
        drawImage3(10, 0, 240, 150, startsplashsized);
        drawString(0, 0, "SCORE", WHITE);
        score = 0;
        sprintf(scoreBuffer, "%d", score);
        drawString(0, 40, scoreBuffer, WHITE);
        drawString(0, 140, "HI-SCORE", WHITE);
        sprintf(highScoreBuffer, "%d", highScore);
        drawString(0, 200, highScoreBuffer, WHITE);
        state = START_NODRAW;
      }break; case START_NODRAW: {
        if (KEY_DOWN_NOW(BUTTON_A) && !aPressed) {
          aPressed = 1;
          state = LEVEL1;
        }
      }break; case LEVEL1: {
          numBlocks = L1_NUMBLOCKS;

          drawImage3(10, 0, 240, 150, techringsized);

          drawSprite(platform.row, platform.col, 30, 15, GTsized2);

          for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 15; j++) {
              L1_BLOCKS[(i * 15) + j].row = 10 + (i * 8);
              L1_BLOCKS[(i * 15) + j].col = (j * 16);
            }
          }

          createLevel1();

          drawSprite(ball.row, ball.col, 10, 8, footballsized3);

          state = LEVEL1_NODRAW;
      }break; case LEVEL1_NODRAW: {
          if (KEY_DOWN_NOW(BUTTON_LEFT) && platform.col != 0) {
            platform.cdel = -1;
          } else if (KEY_DOWN_NOW(BUTTON_RIGHT) && platform.col != 210) {
            platform.cdel = 1;
          } else {
            platform.cdel = 0;
          }

          if (platform.cdel != 0) {
              platform.col += platform.cdel;

              replace(platform.row, platform.col - platform.cdel, 30, 15, techringsized);

              drawSprite(platform.row,
                platform.col, 30, 15, GTsized2);
          }

          ball.col += ball.cdel;
          ball.row += ball.rdel;

          replace(ball.row - ball.rdel, ball.col - ball.cdel, 10, 8, techringsized);

          drawSprite(ball.row,
            ball.col, 10, 8, footballsized3);

            if (ball.row == platform.row - 7) {
              if (ball.col >= platform.col - 6 && ball.col <= platform.col + 26) {
                ball.rdel = -1;
                ball.cdel = 1 * platform.cdel;
              }
            } else if (ball.row + 7 >= platform.row && ball.row <= platform.row + 8) {
              if (ball.col == platform.col - 7) {
                ball.rdel = -1;
                ball.cdel = -1;
              } else if (ball.col == platform.col + 26) {
                ball.rdel = -1;
                ball.cdel = 1;
              }
            } else if (ball.row + 7 >= platform.row && ball.row <= platform.row) {
              if (ball.col == platform.col - 7) {
                ball.cdel = -1;
              } else if (ball.col == platform.col + 26) {
                ball.cdel = 1;
              }
            }

            if (ball.row > 160) {
              state = GAME_OVER;
            }

            if (ball.row == 10) {
              ball.rdel = 1;
            }

            if (ball.col == 0) {
              ball.cdel = 1;
            }

            if (ball.col == 230) {
              ball.cdel = -1;
            }

            for (int i = 0; i < L1_NUMBLOCKS; i++) {
              if (ball.row == L1_BLOCKS[i].row + 8) {
                if (ball.col + 5 >= L1_BLOCKS[i].col && ball.col <= L1_BLOCKS[i].col + 16) {
                  ball.rdel = 1;

                  score += 20;
                  drawRect(0, 40, 40, 10, BLACK);
                  sprintf(scoreBuffer, "%d", score);
                  drawString(0, 40, scoreBuffer, WHITE);

                  numBlocks--;

                  replace(L1_BLOCKS[i].row, L1_BLOCKS[i].col, 16, 8, techringsized);

                  L1_BLOCKS[i].col = -100;
                  L1_BLOCKS[i].row = -100;
                }
              } else if (ball.row + 8 == L1_BLOCKS[i].row) {
                  if (ball.col + 5 >= L1_BLOCKS[i].col && ball.col <= L1_BLOCKS[i].col + 16) {
                    ball.rdel = -1;

                    score += 20;
                    drawRect(0, 40, 40, 10, BLACK);
                    sprintf(scoreBuffer, "%d", score);
                    drawString(0, 40, scoreBuffer, WHITE);

                    numBlocks--;

                    replace(L1_BLOCKS[i].row, L1_BLOCKS[i].col, 16, 8, techringsized);

                    L1_BLOCKS[i].col = -100;
                    L1_BLOCKS[i].row = -100;
                  }
              } else if (ball.row <= L1_BLOCKS[i].row + 8 && ball.row >= L1_BLOCKS[i].row) {
                  if (ball.col == L1_BLOCKS[i].col + 16) {
                    ball.cdel = 1;

                    score += 20;
                    drawRect(0, 40, 40, 10, BLACK);
                    sprintf(scoreBuffer, "%d", score);
                    drawString(0, 40, scoreBuffer, WHITE);

                    numBlocks--;

                    replace(L1_BLOCKS[i].row, L1_BLOCKS[i].col, 16, 8, techringsized);

                    L1_BLOCKS[i].col = -100;
                    L1_BLOCKS[i].row = -100;
                  } else if (ball.col + 10 == L1_BLOCKS[i].col) {
                    ball.cdel = -1;

                    score += 20;
                    drawRect(0, 40, 40, 10, BLACK);
                    sprintf(scoreBuffer, "%d", score);
                    drawString(0, 40, scoreBuffer, WHITE);

                    numBlocks--;

                    replace(L1_BLOCKS[i].row, L1_BLOCKS[i].col, 16, 8, techringsized);

                    L1_BLOCKS[i].col = -100;
                    L1_BLOCKS[i].row = -100;
                  }
              }
            }

      }break; case GAME_OVER: {
          drawImage3(10, 0, 240, 150, gameoversized);
          highScore = score;
          score = 0;
          drawRect(0, 40, 40, 10, BLACK);
          sprintf(scoreBuffer, "%d", score);
          drawString(0, 40, scoreBuffer, WHITE);
          drawRect(0, 200, 40, 10, BLACK);
          sprintf(highScoreBuffer, "%d", highScore);
          drawString(0, 200, highScoreBuffer, WHITE);
          state = GAME_OVER_NODRAW;
      }break; case GAME_OVER_NODRAW: {
        if (KEY_DOWN_NOW(BUTTON_A) && !aPressed) {
          aPressed = 1;
          state = START;
        }
      }break;

      if (!KEY_DOWN_NOW(BUTTON_A)) {
  			aPressed = 0;
  		}

    }
  }

  return 0;
}
