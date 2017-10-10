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
	//�κ��丮 â �̹��� 
	image*			_mainInventory;
	
	//��ȭâ �̹���
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

