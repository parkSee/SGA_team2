#include "stdafx.h"
#include "tankScene.h"


tankScene::tankScene()
{
}


tankScene::~tankScene()
{

}

HRESULT tankScene::init(void)
{
	_tankMap = new tankMap;
	_tankMap->init();

	_tank = new tank;
	_tank->init();
	_tank->setTankMapAddressLink(_tankMap);
	_tank->setTankPosition();


	return S_OK;
}

void tankScene::release(void)
{

}

void tankScene::update(void) 
{
	_tankMap->update();
	_tank->update();
}

void tankScene::render(void) 
{
	_tankMap->render();
	_tank->render();
}
