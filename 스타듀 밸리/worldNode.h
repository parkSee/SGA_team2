#pragma once

//모든 스탯 및 초기 값 디파인은 여기서 해준다
//이렇게 해주면 추 후 밸런스 조절 시 쉽게 조정 가능 

//ex) #define PLAYERSPEED 5
//player->init()에서 _player.speed = PLAYERSPEED

//우리 모든 아이들의 좌표
//POINTFLOAT이란게 있지만 그건 기본생성자만 있을 뿐 구조체째로 값을 초기화 해주는 그거 두번째 함수가 없기때문에 만들었음
struct tagFloat
{
	float x;
	float y;

	tagFloat() { x = 0; y = 0; };
	tagFloat(float X, float Y) { x = X; y = Y; }
};


//=================== UI ======================
//대화창 디파인
#define PLAYER 0



