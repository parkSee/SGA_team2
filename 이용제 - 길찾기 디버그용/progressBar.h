#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	progressBar();
	~progressBar();
};

//오늘 + 내일 프레임워크 숙제 해당자 (Guardians Of SGA)
//현진이, 순우, 효림, 객티쉬, 구데리안
//스타로드, 드랙스, 가모라, 그루트, 로켓
// -> 내일 왁자지껄에 올림

//17시까지!

//와 난 순우형께 좋아요~
//와~ 난 객티쉬형께 좋아요~ 완전 객체지향이야~
//와~ 난 효림이께 좋아요
//와 ~ 구데리안 형꺼 개간단!