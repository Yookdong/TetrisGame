#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "TetrisHelper.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

// ���� ȭ�� ������
#define GRID_WIDTH 14
#define GRID_HEIGHT 25

// �������� ����� ũ�� ����
#define USERBLOCK_SIZE 3

// Display ����
int DisplayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
// �迭�� ��� �պκ��� Y, ���� ��Ÿ���� �޺κ��� X, ���� ��Ÿ����.

enum class GameState
{
	GAMEPLAY, GAMEOVER
};

class Display // ȭ�� ��� ��� Ŭ����
{
public:
	Display();
	~Display();

	void draw()
	{
		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				//(DisplayData[i][j] == 0) ? drawPosition(j, i, false) : drawPosition(j, i, true);
				drawPosition(j, i, !(DisplayData[i][j] == 0));
			}
		}
	}
private:
};

Display::Display()
{
}

Display::~Display()
{
}


class GameEngine // ���� �׸���(������ ��)�� �����ϰ� Display �� ������ ����
{
public:
	GameEngine();
	~GameEngine();

	GameState CurrentState = GameState::GAMEPLAY;

	int GameGridData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
	int UseBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = { {0,0,1},{0,0,1},{0,0,1} };

	int UserBlockVarious[3][USERBLOCK_SIZE][USERBLOCK_SIZE] = { { {0,1,0},{0,1,0},{0,1,0} },
		{ {0,0,0},{0,1,1},{0,1,1} }, { {0,0,0},{0,1,0},{1,1,1} } };

	// �� �����Ǵ� ��ġ��	
	int BlockX = 0;
	int BlockY = 0;

	float BlockDownSpeed = 0;
	float BlockMoveRL = 0;

	// ���ʿ� ���� ������ �ʱ�ȭ �ϴ� ������ �þ� �Ѵ�.
	void Init()
	{
		MakeBlock();
	}

	// �� �����ӿ� �ҷ��� �Լ�
	void Next(float deltatime, char inputvalue)
	{
		if (CurrentState == GameState::GAMEOVER) return;

		BlockDownSpeed += deltatime;
		BlockMoveRL += deltatime;

		if (BlockDownSpeed >= .5f)
		{
			if (CanDown())
			{
				BlockY++;
			}
			else
			{
				trans();
				if (GameoverDecision()) CurrentState = GameState::GAMEOVER;
			}

			BlockDownSpeed -= .5f;
		}

		if (BlockMoveRL > 0.05)
		{
			if (inputvalue == 'a' && CanLeft())
			{
				BlockX--;
			}
			if (inputvalue == 'd' && CanRight())
			{
				BlockX++;
			}
			if (inputvalue == 's' && CanDown())
			{
				BlockY++;
			}
			if (inputvalue == 'w')
			{
				RotateBlock();
			}

			BlockMoveRL = 0;
		}
	}

	bool CanDown()
	{
		// �Ʒ� ��ֹ��� �ִ��� Ȯ���ϴ� �ݺ���
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && (i + BlockY + 1) >= GRID_HEIGHT)
				{
					return false;
				}

				if (UseBlock[i][j] == 1 && GameGridData[i + BlockY + 1][j + BlockX] == 1)
				{
					return false;
				}
			}
		}

		// �ݺ����� �ɸ��� ������ �Ʒ��� �̵�
		return true;
	}

	bool CanLeft()
	{
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && (j + BlockX - 1) < 0)
				{
					return false;
				}

				if (UseBlock[i][j] == 1 && GameGridData[i + BlockY][j + BlockX - 1] == 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool CanRight()
	{
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && (j + BlockX + 1) >= GRID_WIDTH)
				{
					return false;
				}

				if (UseBlock[i][j] == 1 && GameGridData[i + BlockY][j + BlockX + 1] == 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool IsLineFilled(int y)
	{
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			if (GameGridData[y][i] == 0) return false;
		}
		return true;
	}

	void EraseLine(int y)
	{
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			GameGridData[y][i] = 0;
		}
	}

	// ���� ���� �������� �� ���� ��� ĭ�� �Ʒ��� �����;� �Ѵ�.
	void DropLine(int y)
	{
		for (int i = y; i >= 0; i--)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				GameGridData[i][j] = ((i - 1) < 0) ? 0 : GameGridData[i - 1][j];
			}
		}
	}

	// ������ ���� ���ӵ����ͷ� �Ѱ��ִ� �Լ�
	void trans()
	{
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				GameGridData[i + BlockY][j + BlockX] = UseBlock[i][j] | GameGridData[i + BlockY][j + BlockX];
			}
		}

		//  ���� ���� ���� �� �ִ��� Ȯ��
		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			if (IsLineFilled(i))
			{
				EraseLine(i);
				DropLine(i);
			}
		}

		// ���ο� ��� ����
		MakeBlock();
	}

	bool GameoverDecision()
	{
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && GameGridData[i + BlockY][j + BlockX] == 1) return true;
			}
		}

		return false;
	}

	void MakeBlock()
	{
		BlockX = (GRID_WIDTH / 2) - (USERBLOCK_SIZE / 2);
		BlockY = 0;

		// ������ ���� ���ο� ��
		// srand(time(0)); // ����ȭ�� ���� ���ο��� �� ���� ȣ���Ѵ�.

		int various = rand() % 3;
		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				UseBlock[i][j] = UserBlockVarious[various][i][j];
			}
		}

	}

	// ���� �����غ���
	void RotateBlock()
	{

	}

	// ���� ���� �����͸� ȭ�鿡 ����� �����ͷ� �ٲٴ� �Լ�
	void MakeDisplayData()
	{
		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				DisplayData[i][j] = GameGridData[i][j];
			}
		}

		for (int i = 0; i < USERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < USERBLOCK_SIZE; j++)
			{
				if ((i + BlockY) < 0 || (i + BlockY) > GRID_HEIGHT)
				{

				}
				else if ((j + BlockX) < 0 || (j + BlockX) > GRID_HEIGHT)
				{

				}
				else
				{
					// ������ ����� �ϴ� �ڵ�
					// DisplayData[i + BlockY][j + BlockX] = (UseBlock[i][j] == 1) ? UseBlock[i][j] : DisplayData[i + BlockY][j + BlockX];

					// �� �ڵ尡 ������ �ξ� ����
					// �������ڷ� Ȱ���� �� �ڵ带 ���� �� - bitwise ����
					// �ݺ��� �Ǵ� ������ ����ó���ϴ� ���� ������ �ξ� ����.
					int _x = j + BlockX;
					int _y = i + BlockY;
					DisplayData[_y][_x] = UseBlock[i][j] | DisplayData[_y][_x];
				}
			}
		}

	}

private:
};

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}
