#pragma once
#include "gameNode.h"

class myTileMap;


class myTank : public gameNode
{
private:
	enum TANKDIRECTION
	{
		DIRECTION_LEFT,
		DIRECTION_UP,
		DIRECTION_RIGHT,
		DIRECTION_DOWN
	};
	
	enum LEVER
	{
		LEVER_LEFT_DOWN = 1, LEVER_DOWN, LEVER_RIGHT_DOWN,
		LEVER_LEFT, LEVER_IDLE, LEVER_RIGHT,
		LEVER_LEFT_UP, LEVER_UP, LEVER_RIGHT_UP
	};


	myTileMap* _tankMap;
	
	image* _image;
	float _x, _y;
	RECT _rc;
	
	float _speed;
	TANKDIRECTION _direction;
	LEVER _lever, _pastLever;
	
	bool _isPlayer;
	bool _isMove;

public:
	myTank();
	~myTank();

	HRESULT init(int left, int top);
	void release(void);
	void update(void);
	void render(void);


	void leverStateUpdate();
	void leverToDirection();
	void tankMove();
	void setTankPosition(int idX, int idY);
	void setTankLeftTop(int left, int top);
	void setTankCenter(float x, float y);
	void setTankImageDirection();
	
	
	inline void setTankMapAddressLink(myTileMap* tm) { _tankMap = tm; }
	inline RECT getRect() { return _rc; }
};
