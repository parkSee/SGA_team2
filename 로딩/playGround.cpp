#include "stdafx.h"
#include "playGround.h"

//¾È³ÉÇÏ¼¼¿© ¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾
//¾á³ÉÇá¼Î¿© ¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾¤¾
//¸ÊÅø ºê·£Ä¡ »ý¼º ÈÄ ¸¶½ºÅÍºê·£Ä¡ ¿©±â °íÄ§
playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("¼¿·ºÆ®¾À", "¼¿·ºÆ®¾À.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	SCENEMANAGER->addScene("·Îµù¾À", new loadingScene);
	SCENEMANAGER->addScene("¼¿·º¾À", new characterSelectScene);

	SCENEMANAGER->changeScene("·Îµù¾À");

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

	//=================== ¼Õ ´ë Áö ¸¶ ===================
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
