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

// 게임 화면 사이즈
#define GRID_WIDTH 7
#define GRID_HEIGHT 10

// 떨어지는 블록의 크기 제한
#define USERBLOCK_SIZE 3

// Display 관련
int DisplayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
// 배열의 경우 앞부분이 Y, 행을 나타내고 뒷부분이 X, 열을 나타낸다.

class Display // 화면 출력 담당 클래스
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


class GameEngine // 유저 그리드(생성된 블럭)을 관리하고 Display 에 정보를 전달
{
public:
	GameEngine();
	~GameEngine();

	int GameGridData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
	int UseBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = { {1,1,1},{0,0,1},{0,0,1} };

	// 블럭 생성되는 위치값	
	int BlockX = 0;
	int BlockY = 0;

	float BlockDownSpeed = 0;

	// 최초에 게임 엔진을 초기화 하는 과정을 맡아 한다.
	void Init()
	{
	}

	// 매 프레임에 불려질 함수
	void Next(float deltatime, char inputvalue)
	{
		BlockDownSpeed += deltatime;

		if (BlockDownSpeed >= .5f)
		{
			BlockY++;
			BlockDownSpeed -= .5f;
		}
	}

	// 실제 게임 데이터를 화면에 출력할 데이터로 바꾸는 함수
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
					// 동일한 기능을 하는 코드
					// DisplayData[i + BlockY][j + BlockX] = (UseBlock[i][j] == 1) ? UseBlock[i][j] : DisplayData[i + BlockY][j + BlockX];
					
					// 이 코드가 성능이 훨씬 좋다
					// 논리연산자로 활용해 위 코드를 줄인 것 - bitwise 연산
					// 반복이 되는 연산은 변수처리하는 것이 성능이 훨씬 좋다.
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
