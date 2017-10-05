#include "stdafx.h"
#include "playGround.h"

//照撹馬室食 ぞぞぞぞぞぞぞぞぞぞぞぞ
playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("漆刑闘樟", "漆刑闘樟.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	SCENEMANAGER->addScene("稽漁樟", new loadingScene);
	SCENEMANAGER->addScene("漆刑樟", new characterSelectScene);

	SCENEMANAGER->changeScene("稽漁樟");

	return S_OK;
}

void playGround::release(void)
{
	gameNode::release();

}

void playGround::update(void)
{
	gameNode::update();


	SCENEMANAGER->update();
	
}

void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	

	SCENEMANAGER->render();
	
	//TIMEMANAGER->render(getMemDC());

	//=================== 謝 企 走 原 ===================
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
