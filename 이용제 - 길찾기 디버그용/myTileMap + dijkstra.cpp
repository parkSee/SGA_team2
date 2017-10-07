#include "stdafx.h"
#include "myTileMap.h"

vector<myTile*> myTileMap::getShortestDijkstra(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
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

	//�ִ� ���� (�ּҺ�� �ʱ�ȭ�� ���δ�)
	const int MAX = 0x0fffffff;

	//����(������ ��) ����ü ����
	//�����, ������, �������ڽ�Ʈ
	struct tagLine
	{
		myTile* from;
		myTile* to;
		int toCost;

		//tagLine() : from(NULL), to(NULL), toCost(MAX) {}   //���� �ʿ� ���µ�
	};

	//�������� �迭 ����
	//�����ִٴ� �� �� Ÿ�Ͽ� �����ϴ� �ִ� ��Ʈ�� Ȯ���ƴٴ� ��
	bool isClosed[TILENUMX][TILENUMY];
	//�������� �ʱ�ȭ
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			isClosed[i][j] = false;
		}
	}
	//�������� ���� ���·�
	isClosed[startIdX][startIdY] = true;

	//����Ÿ�ϱ����� �ּҺ�� �迭 ����
	int minCost[TILENUMX][TILENUMY];
	//�ּҺ�� �ʱ�ȭ
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			minCost[i][j] = MAX;
		}
	}
	//�������� �ּҺ�� 0
	minCost[startIdX][startIdY] = 0;

	//Ž������ �� ����Ʈ(���¸���Ʈ)�� �ִܸ���Ʈ(Ŭ����帮��Ʈ) ����
	vector<tagLine*> vOpen;
	vector<tagLine*> vClosed;

	//�������� ���� ����, �������� ����������
	myTile* startTile = _pTile[startIdX][startIdY];
	myTile* endTile = _pTile[endIdX][endIdY];
	myTile* current = startTile;


	/*----------------------------------------------------------
	������ �������� �� ���� �ʱ�ȭ
	�Ʒ����� ����
	----------------------------------------------------------*/


	//���ͽ�Ʈ�� ��ã�� ����
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
				if (isClosed[i][j]) continue;
				//��ֹ��̸� continue
				if (_pTile[i][j]->getIsUnmovable())
				{
					isClosed[i][j] = true;
					continue;
				}

				tagLine* lineTemp = new tagLine;   //���θ޸� �Ƚᵵ �ǳ�? ���θ޸𸮴� �����Ȳ�� ���°���...
												   //memset(lineTemp, 0, sizeof(*lineTemp));
				lineTemp->from = current;
				lineTemp->to = _pTile[i][j];
				lineTemp->toCost = minCost[curX][curY] + getDistance(current->getRect().left, current->getRect().top,
					_pTile[i][j]->getRect().left, _pTile[i][j]->getRect().top);

				vOpen.push_back(lineTemp);
			}
		}

		//9Ÿ�� Ž���� ������ ���� ������Ͽ��� ���� �ڽ�Ʈ ���� ���� ����
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
		//���ö��� ������ �������� true�� �ϰ� �ּ��ڽ�Ʈ ���
		if (lineMin != NULL)
		{
			isClosed[lineMin->to->getIdX()][lineMin->to->getIdY()] = true;
			minCost[lineMin->to->getIdX()][lineMin->to->getIdY()] = lineMin->toCost;
		}
		else   //���ö����� ���� == ��������� ����ִ� == �� �� �ִ� ���� ����
		{
			break;   //��ã�� ���� �����Ų��
		}

		//������Ͽ��� ���ö��� �������� ���� ������ ���� ������
		//�ڽ�Ʈ Ȯ���ؼ� ���ö��� �������ڽ�Ʈ�� ������ ������Ͽ� ���� �߰��ϰ�
		//�ش� ���� ������Ͽ��� ����
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

		// <��������> ���ö��� �������� ��ǥ�� ������ ��Ȳ
		if (lineMin->to == endTile)
		{
			vector<myTile*> solution;
			vector<myTile*> solutionReversed;
			tagLine* lineCurrent = vClosed[vClosed.size() - 1];   //������Ͽ� ���������� �߰��� ������ �������� ����
			solutionReversed.push_back(lineCurrent->to);

			//�������� ���� ���� ���������� solutionReversed�� �߰�
			while (true)
			{
				solutionReversed.push_back(lineCurrent->from);

				// <��������> ������� ������� �������� ������ ����
				if (lineCurrent->from == startTile) break;
				// <>

				//������Ͽ��� ������� ������� �������� ���� ������ ���� ����������� ����
				for (int i = 0; i < vClosed.size(); ++i)
				{
					if (vClosed[i]->to == lineCurrent->from)
					{
						lineCurrent = vClosed[i];
						break;
					}
				}
			}

			//�ַ�Ǹ����� ����� �ַ�ǿ� ����ְ� ��ȯ
			for (int i = solutionReversed.size() - 1; i >= 0; --i)
			{
				solution.push_back(solutionReversed[i]);
			}
			return solution;
		}
		// <>

		current = lineMin->to;
	}

	//��ã�� ������ ������������ ����� ��Ȳ
	//�� ���� ��ȯ���� ����
	vector<myTile*> nothing;
	return nothing;
}





void myTileMap::dijkstraDebugInit(int startIdX, int startIdY, int endIdX, int endIdY, bool eightDirection)
{
	//������ ������ ������ �ٷ� ����
	if (startIdX == endIdX && startIdY == endIdY) return;

	//Ÿ�Ϲ��� ����� �Է°��� �ٷ� ����
	if (!(0 <= startIdX && startIdX < TILENUMX && 0 <= startIdY && startIdY < TILENUMY &&
		0 <= endIdX && endIdX < TILENUMX && 0 <= endIdY && endIdY < TILENUMY)) return;

	//�������� �ʱ�ȭ
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			isClosed[i][j] = false;
		}
	}
	//�������� ���� ���·�
	isClosed[startIdX][startIdY] = true;

	//�ּҺ�� �ʱ�ȭ
	for (int j = 0; j < TILENUMY; ++j)
	{
		for (int i = 0; i < TILENUMX; ++i)
		{
			minCost[i][j] = MAX;
		}
	}
	//�������� �ּҺ�� 0
	minCost[startIdX][startIdY] = 0;

	//Ž������ �� ����Ʈ(���¸���Ʈ)�� �ִܸ���Ʈ(Ŭ����帮��Ʈ) �ʱ�ȭ
	vOpenLine.clear();
	vClosedLine.clear();

	//�������� ���� ����, �������� ����������
	startTile = _pTile[startIdX][startIdY];
	endTile = _pTile[endIdX][endIdY];
	current = startTile;
	this->eightDirection = eightDirection;
	isSearched = false;
	isFinished = false;
}
void myTileMap::dijkstraDebugSearch()
{
	if (current == NULL) return;   //������ġ

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
			if (isClosed[i][j]) continue;
			//��ֹ��̸� continue
			if (_pTile[i][j]->getIsUnmovable())
			{
				isClosed[i][j] = true;
				continue;
			}

			tagLine* lineTemp = new tagLine;   //���θ޸� �Ƚᵵ �ǳ�? ���θ޸𸮴� �����Ȳ�� ���°���...
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
	//9Ÿ�� Ž���� ������ ���� ������Ͽ��� ���� �ڽ�Ʈ ���� ���� ����
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
	//���ö��� ������ �������� true�� �ϰ� �ּ��ڽ�Ʈ ���
	if (lineMin != NULL)
	{
		isClosed[lineMin->to->getIdX()][lineMin->to->getIdY()] = true;
		minCost[lineMin->to->getIdX()][lineMin->to->getIdY()] = lineMin->toCost;
	}
	else   //���ö����� ���� == ��������� ����ִ� == �� �� �ִ� ���� ����
	{
		isFinished = true;
		return;   //��ã�� ���� �����Ų��
	}

	//������Ͽ��� ���ö��� �������� ���� ������ ���� ������
	//�ڽ�Ʈ Ȯ���ؼ� ���ö��� �������ڽ�Ʈ�� ������ ������Ͽ� ���� �߰��ϰ�
	//�ش� ���� ������Ͽ��� ����
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

	// <��������> ���ö��� �������� ��ǥ�� ������ ��Ȳ
	if (lineMin->to == endTile)
	{
		vector<myTile*> solution;
		vector<myTile*> solutionReversed;
		tagLine* lineCurrent = vClosedLine[vClosedLine.size() - 1];   //������Ͽ� ���������� �߰��� ������ �������� ����
		solutionReversed.push_back(lineCurrent->to);

		//�������� ���� ���� ���������� solutionReversed�� �߰�
		while (true)
		{
			solutionReversed.push_back(lineCurrent->from);

			// <��������> ������� ������� �������� ������ ����
			if (lineCurrent->from == startTile) break;
			// <>

			//������Ͽ��� ������� ������� �������� ���� ������ ���� ����������� ����
			for (int i = 0; i < vClosedLine.size(); ++i)
			{
				if (vClosedLine[i]->to == lineCurrent->from)
				{
					lineCurrent = vClosedLine[i];
					break;
				}
			}
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

	current = lineMin->to;

	isSearched = false;
}
