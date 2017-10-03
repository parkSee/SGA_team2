#include "stdafx.h"
#include "characterSelectScene.h"


characterSelectScene::characterSelectScene()
{
}


characterSelectScene::~characterSelectScene()
{

}

HRESULT characterSelectScene::init(void)
{
	SOUNDMANAGER->play("ÇÏ±â½È´Ù", 1.0f);

	return S_OK;
}

void characterSelectScene::release(void)
{

}

void characterSelectScene::update(void)	
{

}

void characterSelectScene::render(void)	
{
	IMAGEMANAGER->findImage("¼¿·ºÆ®¾À")->render(getMemDC(), 0, 0);
}
