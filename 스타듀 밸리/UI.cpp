#include "stdafx.h"
#include "UI.h"


HRESULT UI::init(string objName)
{
	gameObject::init(objName);
	
	_mainInventory = IMAGEMANAGER->findImage("mainInventory");


	return S_OK;
}

void UI::release()
{
	gameObject::release();
}

void UI::update()
{
	gameObject::update();
}

void UI::render()
{
	_mainInventory->render(getMemDC(), WINSIZEX / 2 - _mainInventory->getWidth() / 2, WINSIZEY - 150);

}