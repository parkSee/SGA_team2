#include "stdafx.h"

//Ÿ���� �԰� == 32
#define TILESIZE 32

//Ÿ���� ���� (X ���� 20, Y ���� 20)
#define TILEX 20
#define TILEY 20

//Ÿ���� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ��� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//��.Ʈ.�ʵ�~~
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISON		0x00000004
#define ATTR_FROST		0x00000008

//����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//�ѹ� ������ �ǰ����� ���� ~ 3��, �Ȼǰ���
	OBJ_FLAG1, OBJ_FLAG2,				//1����, 2����
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE		//1p��ũ ������, 2p��ũ ����������
};

enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

//Ÿ�� ����ü
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