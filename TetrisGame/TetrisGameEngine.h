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

	static TetrisGameEngine* TetrisGEInstance; // 싱글톤의 기본 구조

private:
	TGameState CurrentState;

	int GameGridData[TGRID_HEIGHT][TGRID_WIDTH];
	int UseBlock[TUSERBLOCK_SIZE][TUSERBLOCK_SIZE];

	int UserBlockVarious[3][TUSERBLOCK_SIZE][TUSERBLOCK_SIZE];

	// 블럭 생성되는 위치값	
	int BlockX;
	int BlockY;

	float BlockDownSpeed;
	float BlockMoveRL;

	// 최초에 게임 엔진을 초기화 하는 과정을 맡아 한다.
	void Init(); // MakeBlock();

	// 매 프레임에 불려질 함수
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
		// 아래 장애물이 있는지 확인하는 반복문
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

		// 반복문에 걸리지 않으면 아래로 이동
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

	// 꽉찬 줄을 기준으로 그 위의 모든 칸이 아래로 내려와야 한다.
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

	// 내려온 블럭을 게임데이터로 넘겨주는 함수
	void trans()
	{
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				GameGridData[i + BlockY][j + BlockX] = UseBlock[i][j] | GameGridData[i + BlockY][j + BlockX];
			}
		}

		//  가로 줄이 가득 차 있는지 확인
		for (int i = 0; i < TGRID_HEIGHT; i++)
		{
			if (IsLineFilled(i))
			{
				EraseLine(i);
				DropLine(i);
			}
		}

		// 새로운 블록 생성
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

		// 랜덤을 통한 새로운 블럭
		// srand(time(0)); // 최적화를 위해 메인에서 한 번만 호출한다.

		int various = rand() % 3;
		for (int i = 0; i < TUSERBLOCK_SIZE; i++)
		{
			for (int j = 0; j < TUSERBLOCK_SIZE; j++)
			{
				UseBlock[i][j] = UserBlockVarious[various][i][j];
			}
		}

	}

	// 직접 구현해보기
	void RotateBlock()
	{

	}

	// 실제 게임 데이터를 화면에 출력할 데이터로 바꾸는 함수
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
					// 동일한 기능을 하는 코드
					// DisplayData[i + BlockY][j + BlockX] = (UseBlock[i][j] == 1) ? UseBlock[i][j] : DisplayData[i + BlockY][j + BlockX];

					// 이 코드가 성능이 훨씬 좋다
					// 논리연산자로 활용해 위 코드를 줄인 것 - bitwise 연산
					// 반복이 되는 연산은 변수처리하는 것이 성능이 훨씬 좋다.
					int _x = j + BlockX;
					int _y = i + BlockY;
					// TetrisDisplayData[_y][_x] = UseBlock[i][j] | TetrisDisplayData[_y][_x];
				}
			}
		}

	}
};

#define TGEngine TetrisGameEngine::TetrisGEInstance