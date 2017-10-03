#pragma once
#include "gameNode.h"
#include "tank.h"
#include "tankMap.h"

class tankScene : public gameNode
{
private:
	tankMap* _tankMap;
	tank* _tank;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	tankScene();
	~tankScene();
};

