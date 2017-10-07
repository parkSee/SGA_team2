#include "stdafx.h"
#include "myTileTestScene.h"
#include "myTileMap.h"
#include "myTank.h"

myTileTestScene::myTileTestScene() {}
myTileTestScene::~myTileTestScene() {}


HRESULT myTileTestScene::init(void)
{
	_tileMap = new myTileMap;
	_tileMap->init();
	
	_tank = new myTank;
	_tank->setTankMapAddressLink(_tileMap);
	_tank->init(0, 0);

	_startIdX = _startIdY = _endIdX = _endIdY = 0;
	_tileMap->current = _tileMap->getTile(_startIdX, _startIdY);
	
	_mode = MODE_ASTAR;

	return S_OK;
}
void myTileTestScene::release(void)
{

}
void myTileTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_mode = MODE_ASTAR;
		_tileMap->AStarDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_mode = MODE_DIJKSTRA;
		_tileMap->dijkstraDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
	}
	if (KEYMANAGER->isOnceKeyDown('A') && KEYMANAGER->isStayKeyDown(VK_LCONTROL))
	{
		for (int j = 0; j < TILENUMY; ++j)
		{
			for (int i = 0; i < TILENUMX; ++i)
			{
				KEYMANAGER->isStayKeyDown(VK_LSHIFT) ?
					_tileMap->getTile(i, j)->setIsUnmovable(false) :
					_tileMap->getTile(i, j)->setIsUnmovable(true);
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_tileMap->leftClickInput(_ptMouse);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_tileMap->rightClickInput(_ptMouse);
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_startIdX = _ptMouse.x / TILESIZE;
		_startIdY = _ptMouse.y / TILESIZE;
		_tileMap->AStarDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
		_tileMap->dijkstraDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_endIdX = _ptMouse.x / TILESIZE;
		_endIdY = _ptMouse.y / TILESIZE;
		_tileMap->AStarDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
		_tileMap->dijkstraDebugInit(_startIdX, _startIdY, _endIdX, _endIdY, true);
	}
	_tileMap->update();
	_tank->update();
}
void myTileTestScene::render(void)
{
	_tileMap->render();
	//_tank->render();
	char str[64];
	sprintf_s(str, "S");
	TextOut(getMemDC(), _startIdX * TILESIZE + 5, _startIdY * TILESIZE + 5, str, strlen(str));
	sprintf_s(str, "E");
	TextOut(getMemDC(), _endIdX * TILESIZE + 5, _endIdY * TILESIZE + 5, str, strlen(str));
	
	//다익스트라랑 에이스타 속도 비교용 포문 100번
	//for (int i = 0; i < 100; ++i) _tileMap->getShortestAStar(_startIdX, _startIdY, _endIdX, _endIdY, true);

	////에이스타, 다익스트라 둘 다 안터지는지 확인용
	//_tileMap->getShortestAStar(_startIdX, _startIdY, _endIdX, _endIdY, true);
	//_tileMap->getShortestAStar(_startIdX, _startIdY, _endIdX, _endIdY, false);
	//_tileMap->getShortestDijkstra(_startIdX, _startIdY, _endIdX, _endIdY, true);
	//_tileMap->getShortestDijkstra(_startIdX, _startIdY, _endIdX, _endIdY, false);

	//vector<myTile*> path = _tileMap->getShortestAStar(_startIdX, _startIdY, _endIdX, _endIdY, true);


	switch (_mode)
	{
	case myTileTestScene::MODE_ASTAR:
		//에이스타 디버그용
		if (!_tileMap->isFinished && (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_RETURN)))
		{
			_tileMap->isSearched ? _tileMap->AStarDebugSelect() : _tileMap->AStarDebugSearch();
		}

		for (int j = 0; j < TILENUMY; ++j)
		{
			for (int i = 0; i < TILENUMX; ++i)
			{
				RECT rc;
				RECT rc2;
				if (_tileMap->node[i][j].parent != NULL)
				{
					rc = _tileMap->getTile(i, j)->getRect();
					rc2 = _tileMap->node[i][j].parent->getRect();
					float angle = getAngle(rc.left, rc.top, rc2.left, rc2.top);
					//LineMake(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, rc.left + (rc.right - rc.left) / 2 + (TILESIZE / 2 - 2) * cosf(angle), rc.top + (rc.bottom - rc.top) / 2 + (TILESIZE / 2 - 2) * -sinf(angle));
					LineMake(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, rc2.left + (rc2.right - rc2.left) / 2, rc2.top + (rc2.bottom - rc2.top) / 2);
				}
				if (_tileMap->node[i][j].isOpen)
				{
					rc = _tileMap->getTile(i, j)->getRect();
					EllipseMakeCenter(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, 10, 10);
				}
				if (_tileMap->node[i][j].isClosed)
				{
					rc = _tileMap->getTile(i, j)->getRect();
					EllipseMakeCenter(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, 5, 5);
				}
				rc = _tileMap->current->getRect();
				RectangleMakeCenter(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, 10, 10);
			}
		}

		//if (_tileMap->isFinished)
		{
			RECT rc1;
			RECT rc2;
			myTile* copyCurrent = _tileMap->current;
			while (_tileMap->node[copyCurrent->getIdX()][copyCurrent->getIdY()].parent != NULL)
			{
				rc1 = copyCurrent->getRect();
				rc2 = _tileMap->node[copyCurrent->getIdX()][copyCurrent->getIdY()].parent->getRect();
				LineMake(getMemDC(), rc1.left + (rc1.right - rc1.left) / 2, rc1.top + (rc1.bottom - rc1.top) / 2, rc2.left + (rc2.right - rc2.left) / 2, rc2.top + (rc2.bottom - rc2.top) / 2);
				copyCurrent = _tileMap->node[copyCurrent->getIdX()][copyCurrent->getIdY()].parent;
			}
		}

		break;
	case myTileTestScene::MODE_DIJKSTRA:
		//다익스트라 디버그용
		if (!_tileMap->isFinished && (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_RETURN)))
		{
			_tileMap->isSearched ? _tileMap->dijkstraDebugSelect() : _tileMap->dijkstraDebugSearch();
		}

		for (int i = 0; i < _tileMap->vOpenLine.size(); ++i)
		{
			RECT rc = _tileMap->vOpenLine[i]->to->getRect();
			EllipseMakeCenter(getMemDC(), rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, 10, 10);
		}

		for (int i = 0; i < _tileMap->vClosedLine.size(); ++i)
		{
			RECT rc1 = _tileMap->vClosedLine[i]->from->getRect();
			RECT rc2 = _tileMap->vClosedLine[i]->to->getRect();
			LineMake(getMemDC(), rc1.left + (rc1.right - rc1.left) / 2, rc1.top + (rc1.bottom - rc1.top) / 2, rc2.left + (rc2.right - rc2.left) / 2, rc2.top + (rc2.bottom - rc2.top) / 2);

			if (i == _tileMap->vClosedLine.size() - 1)
			{
				RectangleMakeCenter(getMemDC(), rc2.left + (rc2.right - rc2.left) / 2, rc2.top + (rc2.bottom - rc2.top) / 2, 10, 10);
			}
		}

		break;
	}
}
