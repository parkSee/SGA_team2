#include "stdafx.h"
#include "playGround.h"

//�ȳ��ϼ��� ������������������������
//�����ο� ������������������������
//���� �귣ġ ���� �� �����ͺ귣ġ ���� ��ħ
playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("����Ʈ��", "����Ʈ��.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("������", new characterSelectScene);

	SCENEMANAGER->changeScene("�ε���");

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

	//=================== �� �� �� �� ===================
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
