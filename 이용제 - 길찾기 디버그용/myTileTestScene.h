#pragma once
#include "gameNode.h"

class myTileMap;
class myTank;


class myTileTestScene : public gameNode
{
private:
	myTileMap* _tileMap;
	myTank* _tank;

	int _startIdX, _startIdY, _endIdX, _endIdY;
	enum MODE
	{
		MODE_ASTAR,
		MODE_DIJKSTRA
	};
	MODE _mode;

public:
	myTileTestScene();
	~myTileTestScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};
