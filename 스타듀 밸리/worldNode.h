#pragma once

//��� ���� �� �ʱ� �� �������� ���⼭ ���ش�
//�̷��� ���ָ� �� �� �뷱�� ���� �� ���� ���� ���� 

//ex) #define PLAYERSPEED 5
//player->init()���� _player.speed = PLAYERSPEED

//�츮 ��� ���̵��� ��ǥ
//POINTFLOAT�̶��� ������ �װ� �⺻�����ڸ� ���� �� ����ü°�� ���� �ʱ�ȭ ���ִ� �װ� �ι�° �Լ��� ���⶧���� �������
struct tagFloat
{
	float x;
	float y;

	tagFloat() { x = 0; y = 0; };
	tagFloat(float X, float Y) { x = X; y = Y; }
};


//=================== UI ======================
//��ȭâ ������
#define PLAYER 0



