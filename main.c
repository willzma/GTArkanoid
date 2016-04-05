#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "input.h"

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
  YOU_WIN,
  GAME_OVER,
  GAME_OVER_NODRAW
};

void handlePlayerPlatformInput(PLATFORM* plat);
void handleGameState(enum gameState* state, unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball, unsigned int* score, char scoreBuffer[]);

int main() {
  INIT_MODE_3;
	enum gameState state = START;

  PLATFORM platform;
  platform.image = GTsized2;

  BALL ball;
  ball.image = footballsized3;

  BLOCK L1_BLOCKS[L1_NUMBLOCKS];

  unsigned int numBlocks = 0;

  unsigned int aPressed = 0;
  unsigned int selectPressed = 0;
  unsigned int score = 0;
  unsigned int highScore = 0;

  char scoreBuffer[sizeof(unsigned int) * 3 + 2];
  char highScoreBuffer[sizeof(unsigned int) * 3 + 2];

  while (1) {
    waitForVBlank();
    switch(state) {
      case START: {
        DRAW_START_SPLASH;
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
        } else if (!KEY_DOWN_NOW(BUTTON_A)){
          aPressed = 0;
        }
      }break; case LEVEL1: {
          createLevel1(&numBlocks, L1_BLOCKS, &platform, &ball);
          state = LEVEL1_NODRAW;
      }break; case LEVEL1_NODRAW: {

        handleGameState(&state, &numBlocks, L1_BLOCKS, &platform, &ball, &score, scoreBuffer);


          /*if (!numBlocks) {
              state = YOU_WIN;
          }

          handlePlayerPlatformInput(&platform);

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

            if (ball.row + 7 >= platform.row && ball.row + 7 <= platform.row + 15) {
              if (ball.col + 6 >= platform.col && ball.col <= platform.col + 26) {
                ball.rdel = -1;
                ball.cdel = 1 * (platform.cdel / 2);
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
              } else if (ball.row + 8 >= L1_BLOCKS[i].row && ball.row <= L1_BLOCKS[i].row + 8) {
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
            }*/

      }break; case YOU_WIN: {
          drawImage3(10, 0, 240, 150, techringsized);
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

void handleGameState(enum gameState* state, unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball, unsigned int* score, char scoreBuffer[]) {

    if (!*blockCounter) {
        *state = YOU_WIN;
    }

    handlePlayerPlatformInput(platform);

    if (platform -> cdel != 0) {
        platform -> col += platform -> cdel;

        replace(platform -> row, platform -> col - platform -> cdel, 30, 15, techringsized);

        drawSprite(platform -> row,
          platform -> col, 30, 15, GTsized2);
    }

    ball -> col += ball -> cdel;
    ball -> row += ball -> rdel;

    replace(ball -> row - ball -> rdel, ball -> col - ball -> cdel, 10, 8, techringsized);

    drawSprite(ball -> row,
      ball -> col, 10, 8, footballsized3);

      if (ball -> row + 7 >= platform -> row && ball -> row + 7 <= platform -> row + 15) {
        if (ball -> col + 6 >= platform -> col && ball -> col <= platform -> col + 26) {
          ball -> rdel = -1;
          ball -> cdel = 1 * (platform -> cdel / 2);
        }
      } /*else if (ball.row + 7 >= platform.row && ball.row <= platform.row + 8) {
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
      }*/

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

      for (int i = 0; i < L1_NUMBLOCKS; i++) {
        if (ball -> row == blocks[i].row + 8) {
          if (ball -> col + 5 >= blocks[i].col && ball -> col <= blocks[i].col + 16) {
            ball -> rdel = 1;

            *score += 20;
            drawRect(0, 40, 40, 10, BLACK);
            sprintf(scoreBuffer, "%d", *score);
            drawString(0, 40, scoreBuffer, WHITE);

            *blockCounter = *blockCounter - 1;

            replace(blocks[i].row, blocks[i].col, 16, 8, techringsized);

            blocks[i].col = -100;
            blocks[i].row = -100;
          }
        } else if (ball -> row + 8 == blocks[i].row) {
            if (ball -> col + 5 >= blocks[i].col && ball -> col <= blocks[i].col + 16) {
              ball -> rdel = -1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, techringsized);

              blocks[i].col = -100;
              blocks[i].row = -100;
            }
        } else if (ball -> row + 8 >= blocks[i].row && ball -> row <= blocks[i].row + 8) {
            if (ball -> col == blocks[i].col + 16) {
              ball -> cdel = 1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, techringsized);

              blocks[i].col = -100;
              blocks[i].row = -100;
            } else if (ball -> col + 10 == blocks[i].col) {
              ball -> cdel = -1;

              *score += 20;
              drawRect(0, 40, 40, 10, BLACK);
              sprintf(scoreBuffer, "%d", *score);
              drawString(0, 40, scoreBuffer, WHITE);

              *blockCounter = *blockCounter - 1;

              replace(blocks[i].row, blocks[i].col, 16, 8, techringsized);

              blocks[i].col = -100;
              blocks[i].row = -100;
            }
        }
      }
}

void handlePlayerPlatformInput(PLATFORM* platform) {
  if (KEY_DOWN_NOW(BUTTON_LEFT) && !(platform -> col <= 0)) {
    platform -> cdel = -2;
  } else if (KEY_DOWN_NOW(BUTTON_RIGHT) && !(platform -> col >= 210)) {
    platform -> cdel = 2;
  } else {
    platform -> cdel = 0;
  }
}
