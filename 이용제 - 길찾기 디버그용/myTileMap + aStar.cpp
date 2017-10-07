#include "stdafx.h"
#include "myTileMap.h"

int myTileMap::getHeuristic(int idX1, int idY1, int idX2, int idY2, bool eightDirection)
{
	////�Ʒ� ó�� �ϴ� �� ���� �� getDistance ���°� �� �����Ű���...�� �ƴѰ�?
	//return (int)getDistance(_pTile[idX1][idY1]->getRect().left, _pTile[idX1][idY1]->getRect().top,
	//	_pTile[idX2][idY2]->getRect().left, _pTile[idX2][idY2]->getRect().top);

	//�� �����Ÿ� ���ϱ� �ִܰ�� ��ã�°� �ƴұ�...�� ���� �����̾��� ����������������
	//�ε��� �޾Ƽ� �밢���̶� ���� �ؼ� �غ���
	int dx = abs(idX1 - idX2);
	int dy = abs(idY1 - idY2);
	int diagonal = min(dx, dy);
	return (dx - diagonal + dy - diagonal) * TILESIZE + diagonal * TILESIZE * sqrtf(2);
}
vector<myTile*> myTileMap::getShortestAStar(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
{
	//������ ������ ������ �ٷ� ����
	if (startIdX == endIdX && startIdY == endIdY)
	{
		vector<myTile*> nothing;
		return nothing;
	}

	//Ÿ�Ϲ��� ����� �Է°��� �ٷ� ����
	if (!(0 <= startIdX && startIdX < TILENUMX && 0 <= startIdY && startIdY < TILENUMY &&
		0 <= endIdX && endIdX < TILENUMX && 0 <= endIdY && endIdY < TILENUMY))
	{
		vector<myTile*> nothing;
		return nothing;
	}

	//�ִ� ��� ���� (��� �ʱ�ȭ�� ���δ�)
	const int MAX = 0x0fffffff;

	//��� ����ü ����
	struct tagNode
	{
		myTile* parent;
		bool isOpen;
		bool isClosed;
		int costTotal;
		int costFromStart;
		int costToEnd;

		tagNode() : parent(NULL), isOpen(false), isClosed(false),
			costTotal(MAX), costFromStart(MAX), costToEnd(MAX) {}
		//�����ڷ� �ʱ�ȭ �� �� ������ ���ִµ� ����� �����ϳ�
		//MAX�� const int �� �������Ѵ�

		void calculateTotal() { costTotal = costFromStart + costToEnd; }
	};

	//���� Ÿ�ϴ�� ��� ����
	//���� ���� �ε�����ȣ�� Ÿ���� �޸����̶�� ���� �ȴ�
	//�θ���, ��������, ��������, F, G, H
	tagNode node[TILENUMX][TILENUMY];
	//��� �ʱ�ȭ�� ��� �̴ϼȶ����� ��������� ����

	//������ ��� �ʱ�ȭ
	node[startIdX][startIdY].parent = NULL;
	node[startIdX][startIdY].isOpen = true;
	node[startIdX][startIdY].isClosed = true;
	node[startIdX][startIdY].costFromStart = 0;
	node[startIdX][startIdY].costToEnd = getHeuristic(startIdX, startIdY, endIdX, endIdY, eightDirection);
	node[startIdX][startIdY].calculateTotal();

	//������� ����
	vector<myTile*> vOpen;

	//�������� ���� ����, �������� ����������
	//tagNode* startNode = &node[startIdX][startIdY];
	//tagNode* endNode = &node[endIdX][endIdY];
	//tagNode* current = startNode;
	myTile* startTile = _pTile[startIdX][startIdY];
	myTile* endTile = _pTile[endIdX][endIdY];
	myTile* current = startTile;


	/*----------------------------------------------------------
	������ �������� �� ���� �ʱ�ȭ
	�Ʒ����� ����
	----------------------------------------------------------*/


	//���̽�Ÿ ��ã�� ����
	while (true)
	{
		if (current == NULL) break;   //������ġ

		int curX = current->getIdX();
		int curY = current->getIdY();

		//������ �߽� 9Ÿ�� Ž��
		for (int j = curY - 1; j <= curY + 1; ++j)
		{
			if (j < 0 || j >= TILENUMY) continue;
			for (int i = curX - 1; i <= curX + 1; ++i)
			{
				if (i < 0 || i >= TILENUMX) continue;

				//�ڱ� �ڽ��� continue
				if (i == curX && j == curY) continue;

				//8���� �̵� �Ұ����ϸ� (4���� �̵��� �����ϸ�) �����¿� �ƴϸ� continue
				if (!eightDirection)
				{
					if (!(i == curX && j == curY - 1 ||
						i == curX && j == curY + 1 ||
						i == curX - 1 && j == curY ||
						i == curX + 1 && j == curY)) continue;
				}
				else   //8���� �̵����� �������� ��ֹ��̸� �� ���� �밢�� �����ֱ�
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

				//���������� continue
				if (node[i][j].isClosed) continue;
				//��ֹ��̸� continue
				if (_pTile[i][j]->getIsUnmovable())
				{
					node[i][j].isOpen = true;
					node[i][j].isClosed = true;
					continue;
				}

				//ó�� �� ����� ��Ȳ
				if (!node[i][j].isOpen)
				{
					node[i][j].isOpen = true;
					node[i][j].parent = current;
					node[i][j].costFromStart = node[curX][curY].costFromStart +
						getDistance(current->getRect().left, current->getRect().top,
							_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);
					node[i][j].costToEnd = getHeuristic(i, j, endIdX, endIdY, eightDirection);
					node[i][j].calculateTotal();

					vOpen.push_back(_pTile[i][j]);
				}
				//���ô� ����� ��Ȳ
				else
				{
					//�޸���ƽ ���� ������ �ʴ´�
					//costFromStart�� ���ؼ� �� ������ ������
					int newG = node[curX][curY].costFromStart +
						getDistance(current->getRect().left, current->getRect().top,
							_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);
					if (newG < node[i][j].costFromStart)
					{
						node[i][j].costFromStart = newG;
						node[i][j].calculateTotal();
						node[i][j].parent = current;
					}
				}
			}
		}

		//9Ÿ�� Ž���� ������ ���� ������Ͽ��� costTotal �ּ��� �� ����
		myTile* tileMin = NULL;
		for (int i = 0; i < vOpen.size(); ++i)
		{
			if (tileMin == NULL)
			{
				tileMin = vOpen[i];
				continue;
			}
			if (node[vOpen[i]->getIdX()][vOpen[i]->getIdY()].costTotal <
				node[tileMin->getIdX()][tileMin->getIdY()].costTotal)
			{
				tileMin = vOpen[i];
			}
		}
		//����Ÿ�� �������� true�� �ϰ� ����Ÿ�� ������Ͽ��� ����
		if (tileMin != NULL)
		{
			node[tileMin->getIdX()][tileMin->getIdY()].isClosed = true;
			for (int i = 0; i < vOpen.size(); ++i)
			{
				if (vOpen[i] == tileMin)
				{
					vOpen.erase(vOpen.begin() + i);
					break;
				}
			}
			//����Ÿ���� ���� current�� ����
			current = tileMin;
		}
		else   //����Ÿ���� ���� == ��������� ����ִ� == �� �� �ִ� ���� ����
		{
			break;   //��ã�� ���� �����Ų��
		}

		// <��������> ����Ÿ���� ��ǥ�� ������ ��Ȳ
		if (tileMin == endTile)
		{
			vector<myTile*> solution;
			vector<myTile*> solutionReversed;
			myTile* tempTile = current;

			//����Ÿ�Ϻ��� �θ� ���󰡸鼭 solutionReversed�� �߰�
			solutionReversed.push_back(tempTile);
			while (node[tempTile->getIdX()][tempTile->getIdY()].parent != NULL)
			{
				tempTile = node[tempTile->getIdX()][tempTile->getIdY()].parent;
				solutionReversed.push_back(tempTile);
			}

			//�ַ�Ǹ����� ����� �ַ�ǿ� ����ְ� ��ȯ
			for (int i = solutionReversed.size() - 1; i >= 0; --i)
			{
				solution.push_back(solutionReversed[i]);
			}
			return solution;
		}
		// <>
	}

	//��ã�� ������ ������������ ����� ��Ȳ
	//�� ���� ��ȯ���� ����
	vector<myTile*> nothing;
	return nothing;
}





void myTileMap::AStarDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
{
	//������ ������ ������ �ٷ� ����
	if (startIdX == endIdX && startIdY == endIdY) return;

	//Ÿ�Ϲ��� ����� �Է°��� �ٷ� ����
	if (!(0 <= startIdX && startIdX < TILENUMX && 0 <= startIdY && startIdY < TILENUMY &&
		0 <= endIdX && endIdX < TILENUMX && 0 <= endIdY && endIdY < TILENUMY)) return;

	//��� �ʱ�ȭ
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			node[i][j].parent = NULL;
			node[i][j].isOpen = false;
			node[i][j].isClosed = false;
			node[i][j].costFromStart = MAX;
			node[i][j].costToEnd = MAX;
			node[i][j].costTotal = MAX;
		}
	}

	//������ ��� �ʱ�ȭ
	node[startIdX][startIdY].parent = NULL;
	node[startIdX][startIdY].isOpen = true;
	node[startIdX][startIdY].isClosed = true;
	node[startIdX][startIdY].costFromStart = 0;
	node[startIdX][startIdY].costToEnd = getHeuristic(startIdX, startIdY, endIdX, endIdY, eightDirection);
	node[startIdX][startIdY].calculateTotal();

	//������� �ʱ�ȭ
	vOpen.clear();

	//�������� ���� ����, �������� ����������
	startTile = _pTile[startIdX][startIdY];
	endTile = _pTile[endIdX][endIdY];
	current = startTile;
	this->eightDirection = eightDirection;
	isSearched = false;
	isFinished = false;
}
void myTileMap::AStarDebugSearch()
{
	if (current == NULL) return;   //������ġ

	int endIdX = endTile->getIdX();
	int endIdY = endTile->getIdY();

	int curX = current->getIdX();
	int curY = current->getIdY();

	//������ �߽� 9Ÿ�� Ž��
	for (int j = curY - 1; j <= curY + 1; ++j)
	{
		if (j < 0 || j >= TILENUMY) continue;
		for (int i = curX - 1; i <= curX + 1; ++i)
		{
			if (i < 0 || i >= TILENUMX) continue;

			//�ڱ� �ڽ��� continue
			if (i == curX && j == curY) continue;

			//8���� �̵� �Ұ����ϸ� (4���� �̵��� �����ϸ�) �����¿� �ƴϸ� continue
			if (!eightDirection)
			{
				if (!(i == curX && j == curY - 1 ||
					i == curX && j == curY + 1 ||
					i == curX - 1 && j == curY ||
					i == curX + 1 && j == curY)) continue;
			}
			else   //8���� �̵����� �������� ��ֹ��̸� �� ���� �밢�� �����ֱ�
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

			//���������� continue
			if (node[i][j].isClosed) continue;
			//��ֹ��̸� continue
			if (_pTile[i][j]->getIsUnmovable())
			{
				node[i][j].isOpen = true;
				node[i][j].isClosed = true;
				continue;
			}

			//ó�� �� ����� ��Ȳ
			if (!node[i][j].isOpen)
			{
				node[i][j].isOpen = true;
				node[i][j].parent = current;
				node[i][j].costFromStart = node[curX][curY].costFromStart +
					getDistance(current->getRect().left, current->getRect().top,
						_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);
				node[i][j].costToEnd = getHeuristic(i, j, endIdX, endIdY, eightDirection);
				node[i][j].calculateTotal();

				vOpen.push_back(_pTile[i][j]);
			}
			//���ô� ����� ��Ȳ
			else
			{
				//�޸���ƽ ���� ������ �ʴ´�
				//costFromStart�� ���ؼ� �� ������ ������
				int newG = node[curX][curY].costFromStart +
					getDistance(current->getRect().left, current->getRect().top,
						_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);
				if (newG < node[i][j].costFromStart)
				{
					node[i][j].costFromStart = newG;
					node[i][j].calculateTotal();
					node[i][j].parent = current;
				}
			}
		}
	}

	isSearched = true;
}
void myTileMap::AStarDebugSelect()
{
	//9Ÿ�� Ž���� ������ ���� ������Ͽ��� costTotal �ּ��� �� ����
	myTile* tileMin = NULL;
	for (int i = 0; i < vOpen.size(); ++i)
	{
		if (vOpen[i] == current)
		{
			vOpen.erase(vOpen.begin() + i--);
			continue;
		}
		if (tileMin == NULL)
		{
			tileMin = vOpen[i];
			continue;
		}
		if (node[vOpen[i]->getIdX()][vOpen[i]->getIdY()].costTotal <
			node[tileMin->getIdX()][tileMin->getIdY()].costTotal)
		{
			tileMin = vOpen[i];
		}
	}
	//����Ÿ�� �������� true�� �ϰ� ����Ÿ�� ������Ͽ��� ����
	if (tileMin != NULL)
	{
		//������� ������ tileMin�� ������ ã�Ƽ� ���ִ� ����
		//���� ���� �������� �ϸ� ���ʿ��� ���� �ѹ� ���� �� ���� ������.
		node[tileMin->getIdX()][tileMin->getIdY()].isClosed = true;
		//for (int i = 0; i < vOpen.size(); ++i)
		//{
		//	if (vOpen[i] == tileMin)
		//	{
		//		vOpen.erase(vOpen.begin() + i);
		//		break;
		//	}
		//}

		//����Ÿ���� ���� current�� ����
		current = tileMin;
	}
	else   //����Ÿ���� ���� == ��������� ����ִ� == �� �� �ִ� ���� ����
	{
		isFinished = true;
		return;   //��ã�� ���� �����Ų��
	}

	// <��������> ����Ÿ���� ��ǥ�� ������ ��Ȳ
	if (tileMin == endTile)
	{
		vector<myTile*> solution;
		vector<myTile*> solutionReversed;
		myTile* tempTile = current;

		//����Ÿ�Ϻ��� �θ� ���󰡸鼭 solutionReversed�� �߰�
		solutionReversed.push_back(tempTile);
		while (node[tempTile->getIdX()][tempTile->getIdY()].parent != NULL)
		{
			tempTile = node[tempTile->getIdX()][tempTile->getIdY()].parent;
			solutionReversed.push_back(tempTile);
		}

		//�ַ�Ǹ����� ����� �ַ�ǿ� ����ְ� ��ȯ
		for (int i = solutionReversed.size() - 1; i >= 0; --i)
		{
			solution.push_back(solutionReversed[i]);
		}

		isFinished = true;
		return;
	}
	// <>

	isSearched = false;
}
