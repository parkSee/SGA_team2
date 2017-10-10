#include "stdafx.h"
#include "townScene.h"
#include "UI.h"

HRESULT townScene::init()
{
	return S_OK;

}

void townScene::release()
{

}

void townScene::update()
{
	if (!a)
	{
		UI* uiManager = new UI;
		uiManager->init("UI");
		TOWNWORLD->addObject(objectType::INTERFACE, uiManager);
		a = true;
	}

	TOWNWORLD->update();
}

void townScene::render()
{
	TOWNWORLD->render();
}