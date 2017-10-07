#include "stdafx.h"
#include "myTileMap.h"

myTileMap::myTileMap() {}
myTileMap::~myTileMap() {}


HRESULT myTileMap::init(void)
{
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			myTile* tile1 = new myTile;
			tile1->init(i, j);
			_vTile.push_back(tile1);
			_pTile[i][j] = tile1;
		}
	}

	return S_OK;
}
void myTileMap::release(void)
{

}
void myTileMap::update(void)
{
	
}
void myTileMap::render(void)
{
	for (int i = 0; i < _vTile.size(); ++i)
	{
		_vTile[i]->render();
	}
}


void myTileMap::leftClickInput(POINT pt)
{
	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (_vTile[i]->getIsPtInIt(pt))
		{
			_vTile[i]->setIsUnmovable(true);
		}
	}
}
void myTileMap::rightClickInput(POINT pt)
{
	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (_vTile[i]->getIsPtInIt(pt))
		{
			_vTile[i]->setIsUnmovable(false);
		}
	}
}
