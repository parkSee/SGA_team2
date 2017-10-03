#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{

}

HRESULT keyManager::init()
{
	//처음엔 모든 키가 안눌러져있다고 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}


	return S_OK;
}

void keyManager::release()
{

}


bool keyManager::isOnceKeyDown(int key)
{
	//해당 키를 눌렀을때
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//그 키가 눌러지지 않았다면
		if (!this->getKeyDown()[key])
		{
			//그 키를 눌러졌다고 말해라~~~
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false); //아니면 실패했다고 해라

	return false;
}

bool keyManager::isOnceKeyUp(int key)  
{
	//그 키가 눌러졌다면                    키 떼졌다고 true 신호보내라
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{//그게 아니면 안올라왔다고 전해라~~~
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
