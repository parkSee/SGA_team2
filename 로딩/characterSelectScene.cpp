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
	SOUNDMANAGER->play("�ϱ�ȴ�", 1.0f);

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
	IMAGEMANAGER->findImage("����Ʈ��")->render(getMemDC(), 0, 0);
}
