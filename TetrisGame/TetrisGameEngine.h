#pragma once

#include <ctime>
#include <cmath>
#include "TetrisInfoHeader.h"

enum class TGameState;

class TetrisGameEngine
{
public:
	TetrisGameEngine();
	~TetrisGameEngine();

	static TetrisGameEngine* TetrisGEInstance; // �̱����� �⺻ ����

private:
	TGameState CurrentState;

	int GameGridData[TGRID_HEIGHT][TGRID_WIDTH];
	int UseBlock[TUSERBLOCK_SIZE][TUSERBLOCK_SIZE];

	int UserBlockVarious[3][TUSERBLOCK_SIZE][TUSERBLOCK_SIZE];

	// �� �����Ǵ� ��ġ��	
	int BlockX;
	int BlockY;

	float BlockDownSpeed;
	float BlockMoveRL;

	// ���ʿ� ���� ������ �ʱ�ȭ �ϴ� ������ �þ� �Ѵ�.
	void Init(); // MakeBlock();

	// �� �����ӿ� �ҷ��� �Լ�
	void Tick(float deltatime, char inputvalue);

	void Next(float deltatime, char inputvalue)
	{
		if (CurrentState == TGameState::GAMEOVER) return;

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
				if (GameoverDecision()) CurrentState = TGameState::GAMEOVER;
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
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && (i + BlockY + 1) >= TGRID_HEIGHT)
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
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
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
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && (j + BlockX + 1) >= TGRID_WIDTH)
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
		for (int i = 0; i < TGRID_WIDTH; i++)
		{
			if (GameGridData[y][i] == 0) return false;
		}
		return true;
	}

	void EraseLine(int y)
	{
		for (int i = 0; i < TGRID_WIDTH; i++)
		{
			GameGridData[y][i] = 0;
		}
	}

	// ���� ���� �������� �� ���� ��� ĭ�� �Ʒ��� �����;� �Ѵ�.
	void DropLine(int y)
	{
		for (int i = y; i >= 0; i--)
		{
			for (int j = 0; j < TGRID_WIDTH; j++)
			{
				GameGridData[i][j] = ((i - 1) < 0) ? 0 : GameGridData[i - 1][j];
			}
		}
	}

	// ������ ���� ���ӵ����ͷ� �Ѱ��ִ� �Լ�
	void trans()
	{
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				GameGridData[i + BlockY][j + BlockX] = UseBlock[i][j] | GameGridData[i + BlockY][j + BlockX];
			}
		}

		//  ���� ���� ���� �� �ִ��� Ȯ��
		for (int i = 0; i < TGRID_HEIGHT; i++)
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
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				if (UseBlock[i][j] == 1 && GameGridData[i + BlockY][j + BlockX] == 1) return true;
			}
		}

		return false;
	}

	void MakeBlock()
	{
		BlockX = (TGRID_WIDTH / 2) - (TUSERBLOCK_SIZE / 2);
		BlockY = 0;

		// ������ ���� ���ο� ��
		// srand(time(0)); // ����ȭ�� ���� ���ο��� �� ���� ȣ���Ѵ�.

		int various = rand() % 3;
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
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
		for (int i = 0; i < TGRID_HEIGHT; i++)
		{
			for (int j = 0; j < TGRID_WIDTH; j++)
			{
				// TetrisDisplayData[i][j] = GameGridData[i][j];
			}
		}

		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				if ((i + BlockY) < 0 || (i + BlockY) > TGRID_HEIGHT)
				{

				}
				else if ((j + BlockX) < 0 || (j + BlockX) > TGRID_HEIGHT)
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
					// TetrisDisplayData[_y][_x] = UseBlock[i][j] | TetrisDisplayData[_y][_x];
				}
			}
		}

	}
};

#define TGEngine TetrisGameEngine::TetrisGEInstance