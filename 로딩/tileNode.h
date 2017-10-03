#include "stdafx.h"

//타일의 규격 == 32
#define TILESIZE 32

//타일의 갯수 (X 방향 20, Y 방향 20)
#define TILEX 20
#define TILEY 20

//타일의 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋의 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//비.트.필드~~
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISON		0x00000004
#define ATTR_FROST		0x00000008

//지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//한방 맞으면 뽀개지는 벽돌 ~ 3방, 안뽀개짐
	OBJ_FLAG1, OBJ_FLAG2,				//1진영, 2진영
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE		//1p탱크 리스폰, 2p탱크 리스폰지역
};

enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};