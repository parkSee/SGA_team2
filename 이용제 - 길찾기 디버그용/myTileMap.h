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

	//A* 디버그용
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
		//생성자로 초기화 할 때 변수는 못넣는데 상수는 가능하네
		//MAX를 const int 로 만들어야한다

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
	//Dijkstra 디버그용 추가
	struct tagLine
	{
		myTile* from;
		myTile* to;
		int toCost;

		//tagLine() : from(NULL), to(NULL), toCost(MAX) {}   //굳이 필요 없는듯
	};
	bool isClosed[TILENUMX][TILENUMY];
	int minCost[TILENUMX][TILENUMY];
	vector<tagLine*> vOpenLine;
	vector<tagLine*> vClosedLine;

	//A* 따로 cpp로 분리
	int getHeuristic(int idX1, int idY1, int idX2, int idY2, bool eightDirection);
	vector<myTile*> getShortestAStar(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	//디버그용
	void AStarDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	void AStarDebugSearch();
	void AStarDebugSelect();

	//dijkstra 따로 cpp로 분리
	vector<myTile*> getShortestDijkstra(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	//디버그용
	void dijkstraDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection);
	void dijkstraDebugSearch();
	void dijkstraDebugSelect();

	inline myTile* getTile(int idX, int idY) { return _pTile[idX][idY]; }
	inline bool getIsUnmovable(int idX, int idY) { return _pTile[idX][idY]->getIsUnmovable(); }
	inline ATTRIBUTE getAttribute(int idX, int idY) { return _pTile[idX][idY]->getAttribute(); }
};
