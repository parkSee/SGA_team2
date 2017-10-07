#include "stdafx.h"
#include "myTank.h"
#include "myTileMap.h"

myTank::myTank() {}
myTank::~myTank() {}


HRESULT myTank::init(int left, int top)
{
	_direction = DIRECTION_RIGHT;

	_rc = RectMake(left, top, TILESIZE, TILESIZE);
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
	
	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));
	
	_speed = 1000.0f;
	
	_lever = _pastLever = LEVER_IDLE;
	
	//_isPlayer = isPlayer;
	_isMove = false;

	return S_OK;
}
void myTank::release(void)
{

}
void myTank::update(void)
{
	leverStateUpdate();
	leverToDirection();
	tankMove();
}
void myTank::render(void)
{
	setTankImageDirection();
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	//EllipseMakeCenter(getMemDC(), _rc.left, _rc.top, 10, 10);
}


void myTank::tankMove()
{
	float savex = _x;
	float savey = _y;

	int idX, idY;
	
	if (_lever != LEVER_IDLE)
	{
		switch (_direction)
		{
		case myTank::DIRECTION_LEFT:
			_x -= _speed * TIMEMANAGER->getElapsedTime();
			if (_x - TILESIZE / 2 < 0)
			{
				_x = TILESIZE / 2;
				setTankCenter(_x, _y);
				break;
			}

			idX = _rc.left / TILESIZE;
			idY = _rc.top / TILESIZE;
			if (_tankMap->getIsUnmovable(idX, idY) ||
				_tankMap->getIsUnmovable(idX, idY + 1))
			{
				
			}

			setTankCenter(_x, _y);
			break;
		case myTank::DIRECTION_UP:
			_y -= _speed * TIMEMANAGER->getElapsedTime();
			if (_y - TILESIZE / 2 < 0)
			{
				_y = TILESIZE / 2;
				setTankCenter(_x, _y);
				break;
			}

			idX = _rc.left / TILESIZE;
			idY = _rc.top / TILESIZE;
			if (_tankMap->getIsUnmovable(idX, idY) ||
				_tankMap->getIsUnmovable(idX + 1, idY))
			{
				_x = savex;
				_y = savey;
			}

			setTankCenter(_x, _y);
			break;
		case myTank::DIRECTION_RIGHT:
			_x += _speed * TIMEMANAGER->getElapsedTime();
			if (_x + TILESIZE / 2 > TILESIZE * TILENUMX)
			{
				_x = TILESIZE * TILENUMX - TILESIZE / 2;
				setTankCenter(_x, _y);
				break;
			}

			//idX = _rc.left / TILESIZE;
			//idY = _rc.top / TILESIZE;
			//if (_tankMap->getIsUnmovable(idX + 1, idY) ||
			//	_tankMap->getIsUnmovable(idX + 1, idY + 1))
			//{
			//	_x = savex;
			//	_y = savey;
			//}

			setTankCenter(_x, _y);
			break;
		case myTank::DIRECTION_DOWN:
			_y += _speed * TIMEMANAGER->getElapsedTime();
			if (_y + TILESIZE / 2 > TILESIZE * TILENUMX)
			{
				_y = TILESIZE * TILENUMX - TILESIZE / 2;
				setTankCenter(_x, _y);
				break;
			}

			idX = _rc.left / TILESIZE;
			idY = _rc.top / TILESIZE;
			if (_tankMap->getIsUnmovable(idX, idY + 1) ||
				_tankMap->getIsUnmovable(idX + 1, idY + 1))
			{
				_x = savex;
				_y = savey;
			}

			setTankCenter(_x, _y);
			break;
		}
	}
}
void myTank::setTankPosition(int idX, int idY)
{
	//_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;
	_rc = RectMake(TILESIZE * idX, TILESIZE * idY, TILESIZE, TILESIZE);
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
void myTank::setTankLeftTop(int left, int top)
{
	_rc = RectMake(left, top, TILESIZE, TILESIZE);
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
void myTank::setTankCenter(float x, float y)
{
	_x = x;
	_y = y;
	_rc = RectMake((int)_x - TILESIZE / 2, (int)_y - TILESIZE / 2, TILESIZE, TILESIZE);
}
void myTank::leverStateUpdate()
{
	_pastLever = _lever;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _lever = LEVER_LEFT_DOWN;
		else if (KEYMANAGER->isStayKeyDown(VK_UP)) _lever = LEVER_LEFT_UP;
		else _lever = LEVER_LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _lever = LEVER_RIGHT_DOWN;
		else if (KEYMANAGER->isStayKeyDown(VK_UP)) _lever = LEVER_RIGHT_UP;
		else _lever = LEVER_RIGHT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _lever = LEVER_DOWN;
	else if (KEYMANAGER->isStayKeyDown(VK_UP)) _lever = LEVER_UP;
	else _lever = LEVER_IDLE;
}
void myTank::leverToDirection()
{
	switch (_lever)
	{
	case LEVER_LEFT_DOWN:
		if (_pastLever != LEVER_LEFT_DOWN)
		{
			if (_direction == DIRECTION_LEFT) _direction = DIRECTION_DOWN;
			else _direction = DIRECTION_LEFT;
		}
		break;
	case LEVER_DOWN:
		_direction = DIRECTION_DOWN;
		break;
	case LEVER_RIGHT_DOWN:
		if (_pastLever != LEVER_RIGHT_DOWN)
		{
			if (_direction == DIRECTION_RIGHT) _direction = DIRECTION_DOWN;
			else _direction = DIRECTION_RIGHT;
		}
		break;
	case LEVER_LEFT:
		_direction = DIRECTION_LEFT;
		break;
	case LEVER_IDLE:
		return;
		break;   //이 break는 return 때문에 어차피 안들어갈텐데 혹시 몰라서 써놨다
	case LEVER_RIGHT:
		_direction = DIRECTION_RIGHT;
		break;
	case LEVER_LEFT_UP:
		if (_pastLever != LEVER_LEFT_UP)
		{
			if (_direction == DIRECTION_LEFT) _direction = DIRECTION_UP;
			else _direction = DIRECTION_LEFT;
		}
		break;
	case LEVER_UP:
		_direction = DIRECTION_UP;
		break;
	case LEVER_RIGHT_UP:
		if (_pastLever != LEVER_RIGHT_UP)
		{
			if (_direction == DIRECTION_RIGHT) _direction = DIRECTION_UP;
			else _direction = DIRECTION_RIGHT;
		}
		break;
	}
}
void myTank::setTankImageDirection()
{
	switch (_direction)
	{
	case DIRECTION_LEFT:
		_image->setFrameX(0);
		_image->setFrameY(3);
		break;
	case DIRECTION_UP:
		_image->setFrameX(0);
		_image->setFrameY(0);
		break;
	case DIRECTION_RIGHT:
		_image->setFrameX(0);
		_image->setFrameY(2);
		break;
	case DIRECTION_DOWN:
		_image->setFrameX(0);
		_image->setFrameY(1);
		break;
	}
}
