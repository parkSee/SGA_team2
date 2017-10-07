#pragma once
#include "gameNode.h"

#define TILESIZE 32

#define TILENUMX 20
#define TILENUMY 20

enum ATTRIBUTE
{
	ATTR_UNMOVE,
	ATTR_NORMAL,
	ATTR_SWAMP,
	ATTR_POISON,
	ATTR_FROST
};

enum OBJECT
{
	OBJ_NONE,
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//�ѹ� ������ �ǰ����� ���� ~ 3��, �Ȼǰ���
	OBJ_FLAG1, OBJ_FLAG2,				//1����, 2����
	OBJ_TANK1, OBJ_TANK2				//1p��ũ ������, 2p��ũ ����������
};


class myTile : public gameNode
{
private:
	int _idX, _idY;
	int _frameX, _frameY;

	RECT _rc;
	ATTRIBUTE _attr;
	OBJECT _obj;
	bool _isUnmovable;

public:
	myTile();
	~myTile();

	HRESULT init(int idX, int idY);
	void release(void);
	void update(void);
	void render(void);

	bool getIsPtInIt(POINT pt);


	inline int getIdX() { return _idX; }
	inline int getIdY() { return _idY; }
	inline RECT getRect() { return _rc; }

	inline int getFrameX() { return _frameX; }
	inline int getFrameY() { return _frameY; }
	inline void setFrameX(int frameX) { _frameX = frameX; }
	inline void setFrameY(int frameY) { _frameY = frameY; }

	inline bool getIsUnmovable() { return _isUnmovable; }
	inline void setIsUnmovable(bool boolValue) { _isUnmovable = boolValue; }

	inline ATTRIBUTE getAttribute() { return _attr; }
};
