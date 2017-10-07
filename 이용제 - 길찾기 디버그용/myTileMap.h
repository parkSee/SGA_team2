#pragma once
#include "gameNode.h"
#include "myTile.h"


class myTileMap : public gameNode
{
private:
	vector<myTile*> _vTile;
	myTile* _pTile[TILENUMX][TILENUMY];

public:
	myTileMap();
	~myTileMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void leftClickInput(POINT pt);
	void rightClickInput(POINT pt);

	//A* ����׿�
	const int MAX = 0x0fffffff;
	struct tagNode
	{
		myTile* parent;
		bool isOpen;
		bool isClosed;
		int costTotal;
		int costFromStart;
		int costToEnd;

		tagNode() : parent(NULL), isOpen(false), isClosed(false),
			costTotal(0x0fffffff), costFromStart(0x0fffffff), costToEnd(0x0fffffff) {}
		//�����ڷ� �ʱ�ȭ �� �� ������ ���ִµ� ����� �����ϳ�
		//MAX�� const int �� �������Ѵ�

		void calculateTotal() { costTotal = costFromStart + costToEnd; }
	};
	tagNode node[TILENUMX][TILENUMY];
	vector<myTile*> vOpen;
	myTile* startTile;
	myTile* endTile;
	myTile* current;
	bool eightDirection;
	bool isSearched;
	bool isFinished;
	//Dijkstra ����׿� �߰�
	struct tagLine
	{
		myTile* from;
		myTile* to;
		int toCost;

		//tagLine() : from(NULL), to(NULL), toCost(MAX) {}   //���� �ʿ� ���µ�
	};
	bool isClosed[TILENUMX][TILENUMY];
	int minCost[TILENUMX][TILENUMY];
	vector<tagLine*> vOpenLine;
	vector<tagLine*> vClosedLine;

	//A* ���� cpp�� �и�
	int getHeuristic(int idX1, int idY1, int idX2, int idY2, bool eightDirection);
	vector<myTile*> getShortestAStar(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	//����׿�
	void AStarDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	void AStarDebugSearch();
	void AStarDebugSelect();

	//dijkstra ���� cpp�� �и�
	vector<myTile*> getShortestDijkstra(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	//����׿�
	void dijkstraDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	void dijkstraDebugSearch();
	void dijkstraDebugSelect();

	inline myTile* getTile(int idX, int idY) { return _pTile[idX][idY]; }
	inline bool getIsUnmovable(int idX, int idY) { return _pTile[idX][idY]->getIsUnmovable(); }
	inline ATTRIBUTE getAttribute(int idX, int idY) { return _pTile[idX][idY]->getAttribute(); }
};
