#pragma once
#include "gameObject.h"

struct tagConverSation
{
	image* window;
	image* who;
	image* scroll;
};

class UI : public gameObject
{
private:
	//인벤토리 창 이미지 
	image*			_mainInventory;
	
	//대화창 이미지
	tagConverSation	_conversation;
	
public:
	virtual HRESULT init(string objName);
	virtual void release();
	virtual void update();
	virtual void render();

	void setAddCallback();
	void setTokeWindow(int who , char txt);

	UI() {}
	virtual ~UI() {}
};

