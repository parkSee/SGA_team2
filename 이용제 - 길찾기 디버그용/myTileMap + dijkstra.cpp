#include "stdafx.h"
#include "myTileMap.h"

vector<myTile*> myTileMap::getShortestDijkstra(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
{
	//시작점 끝점이 같으면 바로 끝냄
	if (startIdX == endIdX && startIdY == endIdY)
	{
		vector<myTile*> nothing;
		return nothing;
	}

	//타일범위 벗어나는 입력값도 바로 끝냄
	if (!(0 <= startIdX && startIdX < TILENUMX && 0 <= startIdY && startIdY < TILENUMY &&
		0 <= endIdX && endIdX < TILENUMX && 0 <= endIdY && endIdY < TILENUMY))
	{
		vector<myTile*> nothing;
		return nothing;
	}

	//최댓값 정의 (최소비용 초기화에 쓰인다)
	const int MAX = 0x0fffffff;

	//라인(인접한 길) 구조체 정의
	//출발지, 도착지, 도착지코스트
	struct tagLine
	{
		myTile* from;
		myTile* to;
		int toCost;

		//tagLine() : from(NULL), to(NULL), toCost(MAX) {}   //굳이 필요 없는듯
	};

	//닫힘여부 배열 생성
	//닫혀있다는 건 그 타일에 도달하는 최단 루트가 확정됐다는 것
	bool isClosed[TILENUMX][TILENUMY];
	//닫힘여부 초기화
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			isClosed[i][j] = false;
		}
	}
	//시작점은 닫힌 상태로
	isClosed[startIdX][startIdY] = true;

	//닫힌타일까지의 최소비용 배열 생성
	int minCost[TILENUMX][TILENUMY];
	//최소비용 초기화
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			minCost[i][j] = MAX;
		}
	}
	//시작점은 최소비용 0
	minCost[startIdX][startIdY] = 0;

	//탐색중인 길 리스트(오픈리스트)랑 최단리스트(클로즈드리스트) 생성
	vector<tagLine*> vOpen;
	vector<tagLine*> vClosed;

	//시작점과 끝점 설정, 현재점은 시작점으로
	myTile* startTile = _pTile[startIdX][startIdY];
	myTile* endTile = _pTile[endIdX][endIdY];
	myTile* current = startTile;


	/*----------------------------------------------------------
	위쪽은 변수선언 및 변수 초기화
	아래부터 로직
	----------------------------------------------------------*/


	//다익스트라 길찾는 루프
	while (true)
	{
		if (current == NULL) break;   //안전장치

		int curX = current->getIdX();
		int curY = current->getIdY();

		//현재점 중심 9타일 탐색
		for (int j = curY - 1; j <= curY + 1; ++j)
		{
			if (j < 0 || j >= TILENUMY) continue;
			for (int i = curX - 1; i <= curX + 1; ++i)
			{
				if (i < 0 || i >= TILENUMX) continue;

				//자기 자신은 continue
				if (i == curX && j == curY) continue;

				//8방향 이동 불가능하면 (4방향 이동만 가능하면) 상하좌우 아니면 continue
				if (!eightDirection)
				{
					if (!(i == curX && j == curY - 1 ||
						i == curX && j == curY + 1 ||
						i == curX - 1 && j == curY ||
						i == curX + 1 && j == curY)) continue;
				}
				else   //8방향 이동에서 직선방향 장애물이면 그 옆에 대각선 막아주기
				{
					if (curX - 1 >= 0 && _pTile[curX - 1][curY]->getIsUnmovable())
						if (i == curX - 1 && j != curY) continue;
					if (curX + 1 < TILENUMX && _pTile[curX + 1][curY]->getIsUnmovable())
						if (i == curX + 1 && j != curY) continue;
					if (curY - 1 >= 0 && _pTile[curX][curY - 1]->getIsUnmovable())
						if (j == curY - 1 && i != curX) continue;
					if (curY + 1 < TILENUMY && _pTile[curX][curY + 1]->getIsUnmovable())
						if (j == curY + 1 && i != curX) continue;
				}

				//닫혀있으면 continue
				if (isClosed[i][j]) continue;
				//장애물이면 continue
				if (_pTile[i][j]->getIsUnmovable())
				{
					isClosed[i][j] = true;
					continue;
				}

				tagLine* lineTemp = new tagLine;   //제로메모리 안써도 되나? 제로메모리는 어느상황에 쓰는거지...
												   //memset(lineTemp, 0, sizeof(*lineTemp));
				lineTemp->from = current;
				lineTemp->to = _pTile[i][j];
				lineTemp->toCost = minCost[curX][curY] + getDistance(current->getRect().left, current->getRect().top,
					_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);

				vOpen.push_back(lineTemp);
			}
		}

		//9타일 탐색은 끝났고 이제 열린목록에서 가장 코스트 작은 라인 선택
		tagLine* lineMin = NULL;
		for (int i = 0; i < vOpen.size(); ++i)
		{
			if (lineMin == NULL)
			{
				lineMin = vOpen[i];
				continue;
			}
			if (vOpen[i]->toCost < lineMin->toCost)
			{
				lineMin = vOpen[i];
			}
		}
		//선택라인 도착지 닫힘여부 true로 하고 최소코스트 기록
		if (lineMin != NULL)
		{
			isClosed[lineMin->to->getIdX()][lineMin->to->getIdY()] = true;
			minCost[lineMin->to->getIdX()][lineMin->to->getIdY()] = lineMin->toCost;
		}
		else   //선택라인이 없다 == 열린목록이 비어있다 == 갈 수 있는 길이 없다
		{
			break;   //길찾기 루프 종료시킨다
		}

		//열린목록에서 선택라인 도착지와 같은 도착지 라인 있으면
		//코스트 확인해서 선택라인 도착지코스트와 같으면 닫힌목록에 라인 추가하고
		//해당 라인 열린목록에서 제거
		for (int i = 0; i < vOpen.size(); ++i)
		{
			if (vOpen[i]->to == lineMin->to)
			{
				if (vOpen[i]->toCost == lineMin->toCost)
				{
					vClosed.push_back(vOpen[i]);
				}
				vOpen.erase(vOpen.begin() + i--);
			}
		}

		// <종료조건> 선택라인 도착지가 목표한 끝점인 상황
		if (lineMin->to == endTile)
		{
			vector<myTile*> solution;
			vector<myTile*> solutionReversed;
			tagLine* lineCurrent = vClosed[vClosed.size() - 1];   //닫힌목록에 마지막으로 추가한 라인은 도착지가 끝점
			solutionReversed.push_back(lineCurrent->to);

			//끝점부터 라인 따라서 시작점까지 solutionReversed에 추가
			while (true)
			{
				solutionReversed.push_back(lineCurrent->from);

				// <종료조건> 현재라인 출발지가 시작점과 같으면 종료
				if (lineCurrent->from == startTile) break;
				// <>

				//닫힌목록에서 현재라인 출발지를 도착지로 갖는 라인을 다음 현재라인으로 설정
				for (int i = 0; i < vClosed.size(); ++i)
				{
					if (vClosed[i]->to == lineCurrent->from)
					{
						lineCurrent = vClosed[i];
						break;
					}
				}
			}

			//솔루션리버스 뒤집어서 솔루션에 집어넣고 반환
			for (int i = solutionReversed.size() - 1; i >= 0; --i)
			{
				solution.push_back(solutionReversed[i]);
			}
			return solution;
		}
		// <>

		current = lineMin->to;
	}

	//길찾기 루프가 비정상적으로 종료된 상황
	//빈 벡터 반환으로 끝냄
	vector<myTile*> nothing;
	return nothing;
}





void myTileMap::dijkstraDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
{
	//시작점 끝점이 같으면 바로 끝냄
	if (startIdX == endIdX && startIdY == endIdY) return;

	//타일범위 벗어나는 입력값도 바로 끝냄
	if (!(0 <= startIdX && startIdX < TILENUMX && 0 <= startIdY && startIdY < TILENUMY &&
		0 <= endIdX && endIdX < TILENUMX && 0 <= endIdY && endIdY < TILENUMY)) return;

	//닫힘여부 초기화
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			isClosed[i][j] = false;
		}
	}
	//시작점은 닫힌 상태로
	isClosed[startIdX][startIdY] = true;

	//최소비용 초기화
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			minCost[i][j] = MAX;
		}
	}
	//시작점은 최소비용 0
	minCost[startIdX][startIdY] = 0;

	//탐색중인 길 리스트(오픈리스트)랑 최단리스트(클로즈드리스트) 초기화
	vOpenLine.clear();
	vClosedLine.clear();

	//시작점과 끝점 설정, 현재점은 시작점으로
	startTile = _pTile[startIdX][startIdY];
	endTile = _pTile[endIdX][endIdY];
	current = startTile;
	this->eightDirection = eightDirection;
	isSearched = false;
	isFinished = false;
}
void myTileMap::dijkstraDebugSearch()
{
	if (current == NULL) return;   //안전장치

	int curX = current->getIdX();
	int curY = current->getIdY();

	//현재점 중심 9타일 탐색
	for (int j = curY - 1; j <= curY + 1; ++j)
	{
		if (j < 0 || j >= TILENUMY) continue;
		for (int i = curX - 1; i <= curX + 1; ++i)
		{
			if (i < 0 || i >= TILENUMX) continue;

			//자기 자신은 continue
			if (i == curX && j == curY) continue;

			//8방향 이동 불가능하면 (4방향 이동만 가능하면) 상하좌우 아니면 continue
			if (!eightDirection)
			{
				if (!(i == curX && j == curY - 1 ||
					i == curX && j == curY + 1 ||
					i == curX - 1 && j == curY ||
					i == curX + 1 && j == curY)) continue;
			}
			else   //8방향 이동에서 직선방향 장애물이면 그 옆에 대각선 막아주기
			{
				if (curX - 1 >= 0 && _pTile[curX - 1][curY]->getIsUnmovable())
					if (i == curX - 1 && j != curY) continue;
				if (curX + 1 < TILENUMX && _pTile[curX + 1][curY]->getIsUnmovable())
					if (i == curX + 1 && j != curY) continue;
				if (curY - 1 >= 0 && _pTile[curX][curY - 1]->getIsUnmovable())
					if (j == curY - 1 && i != curX) continue;
				if (curY + 1 < TILENUMY && _pTile[curX][curY + 1]->getIsUnmovable())
					if (j == curY + 1 && i != curX) continue;
			}

			//닫혀있으면 continue
			if (isClosed[i][j]) continue;
			//장애물이면 continue
			if (_pTile[i][j]->getIsUnmovable())
			{
				isClosed[i][j] = true;
				continue;
			}

			tagLine* lineTemp = new tagLine;   //제로메모리 안써도 되나? 제로메모리는 어느상황에 쓰는거지...
											   //memset(lineTemp, 0, sizeof(*lineTemp));
			lineTemp->from = current;
			lineTemp->to = _pTile[i][j];
			lineTemp->toCost = minCost[curX][curY] + getDistance(current->getRect().left, current->getRect().top,
				_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);

			vOpenLine.push_back(lineTemp);
		}
	}

	isSearched = true;
}
void myTileMap::dijkstraDebugSelect()
{
	//9타일 탐색은 끝났고 이제 열린목록에서 가장 코스트 작은 라인 선택
	tagLine* lineMin = NULL;
	for (int i = 0; i < vOpenLine.size(); ++i)
	{
		if (lineMin == NULL)
		{
			lineMin = vOpenLine[i];
			continue;
		}
		if (vOpenLine[i]->toCost < lineMin->toCost)
		{
			lineMin = vOpenLine[i];
		}
	}
	//선택라인 도착지 닫힘여부 true로 하고 최소코스트 기록
	if (lineMin != NULL)
	{
		isClosed[lineMin->to->getIdX()][lineMin->to->getIdY()] = true;
		minCost[lineMin->to->getIdX()][lineMin->to->getIdY()] = lineMin->toCost;
	}
	else   //선택라인이 없다 == 열린목록이 비어있다 == 갈 수 있는 길이 없다
	{
		isFinished = true;
		return;   //길찾기 루프 종료시킨다
	}

	//열린목록에서 선택라인 도착지와 같은 도착지 라인 있으면
	//코스트 확인해서 선택라인 도착지코스트와 같으면 닫힌목록에 라인 추가하고
	//해당 라인 열린목록에서 제거
	for (int i = 0; i < vOpenLine.size(); ++i)
	{
		if (vOpenLine[i]->to == lineMin->to)
		{
			if (vOpenLine[i]->toCost == lineMin->toCost)
			{
				vClosedLine.push_back(vOpenLine[i]);
			}
			vOpenLine.erase(vOpenLine.begin() + i--);
		}
	}

	// <종료조건> 선택라인 도착지가 목표한 끝점인 상황
	if (lineMin->to == endTile)
	{
		vector<myTile*> solution;
		vector<myTile*> solutionReversed;
		tagLine* lineCurrent = vClosedLine[vClosedLine.size() - 1];   //닫힌목록에 마지막으로 추가한 라인은 도착지가 끝점
		solutionReversed.push_back(lineCurrent->to);

		//끝점부터 라인 따라서 시작점까지 solutionReversed에 추가
		while (true)
		{
			solutionReversed.push_back(lineCurrent->from);

			// <종료조건> 현재라인 출발지가 시작점과 같으면 종료
			if (lineCurrent->from == startTile) break;
			// <>

			//닫힌목록에서 현재라인 출발지를 도착지로 갖는 라인을 다음 현재라인으로 설정
			for (int i = 0; i < vClosedLine.size(); ++i)
			{
				if (vClosedLine[i]->to == lineCurrent->from)
				{
					lineCurrent = vClosedLine[i];
					break;
				}
			}
		}

		//솔루션리버스 뒤집어서 솔루션에 집어넣고 반환
		for (int i = solutionReversed.size() - 1; i >= 0; --i)
		{
			solution.push_back(solutionReversed[i]);
		}
		isFinished = true;
		return;
	}
	// <>

	current = lineMin->to;

	isSearched = false;
}
