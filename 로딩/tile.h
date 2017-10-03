#pragma once
#include "gameNode.h"
#include <string>

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H
	//F == TotalCost
	//G == CostFromStart == 시작점으로부터 현재 노드(타일)
	//H == CostToGoal	 == 현재 노드로부터 도착점(타일)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;

	tile* _parentNode;		//상위노드 == 현재타일

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;

	string _attribute;
	
public:
	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdX(void) { return _idX; }
	int getIdY(void) { return _idY; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }

	tile();
	~tile();
};

