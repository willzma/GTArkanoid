typedef struct {
  int row;
  int col;
  u16 oldBlockPixels[128];
} BLOCK;

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

#define L1_NUMBLOCKS 165

#define DRAW_START_SPLASH drawImage3(10, 0, 240, 150, startsplashsized)
#define DRAW_GAME_OVER_SPLASH drawImage3(10, 0, 240, 150, gameoversized)

//Prototypes
void createLevel1(unsigned int* blockCounter, BLOCK blocks[L1_NUMBLOCKS],
  PLATFORM* platform, BALL* ball);
