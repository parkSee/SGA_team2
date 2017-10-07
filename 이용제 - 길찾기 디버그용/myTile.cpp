#include "stdafx.h"
#include "myTile.h"   //다른 헤더에서 stdafx.h 인클루드 하고 있다고 해서 저거 생략하면 안되네

myTile::myTile() {}
myTile::~myTile() {}


HRESULT myTile::init(int idX, int idY)
{
	_idX = idX;
	_idY = idY;

	_rc = RectMake(TILESIZE * _idX, TILESIZE * _idY, TILESIZE, TILESIZE);

	_attr = ATTR_NORMAL;
	_obj = OBJ_NONE;
	_frameX = _frameY = 0;
	_isUnmovable = false;

	return S_OK;
}
void myTile::release(void)
{

}
void myTile::update(void)
{

}
void myTile::render(void)
{
	RectangleMake(getMemDC(), _rc.left, _rc.top, TILESIZE, TILESIZE);

	if (_isUnmovable)
	{
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), CreatePen(PS_SOLID, 2, RGB(200, 200, 200)));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), CreateSolidBrush(RGB(200, 200, 200)));

		Ellipse(getMemDC(), _rc.left + 1, _rc.top + 1, _rc.right - 1, _rc.bottom - 1);

		DeleteObject(SelectObject(getMemDC(), oldBrush));
		DeleteObject(SelectObject(getMemDC(), oldPen));
	}
}


bool myTile::getIsPtInIt(POINT pt)
{
	if (PtInRect(&_rc, pt)) return true;

	return false;
}
