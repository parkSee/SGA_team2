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

//���� + ���� �����ӿ�ũ ���� �ش��� (Guardians Of SGA)
//������, ����, ȿ��, ��Ƽ��, ��������
//��Ÿ�ε�, �巢��, �����, �׷�Ʈ, ����
// -> ���� ���������� �ø�

//17�ñ���!

//�� �� �������� ���ƿ�~
//��~ �� ��Ƽ������ ���ƿ�~ ���� ��ü�����̾�~
//��~ �� ȿ���̲� ���ƿ�
//�� ~ �������� ���� ������!