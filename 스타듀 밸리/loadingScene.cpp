#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	char image[100];
	for (int i = 0; i < 300; i++)
	{
		memset(image, 0, sizeof(image));
		sprintf(image, "mainInventory%d", i);
		_loading->loadImage(image,"resource/UI/mainInventory.bmp" ,800,95,true,RGB(255,0,255));
	}
	_loading->loadImage("mainInventory", "resource/UI/mainInventory.bmp", 800, 95, true, RGB(255, 0, 255));

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("¸¶À»¾À");
	}

}

void loadingScene::render()
{
	_loading->render();

}


