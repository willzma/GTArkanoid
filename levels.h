typedef struct {
  int row;
  int col;
  u16 oldBlockPixels[128];
} BLOCK;

#define L1_NUMBLOCKS 165

//Prototypes
void createLevel1();
