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
#define GRID_WIDTH 7
#define GRID_HEIGHT 10

// �������� ����� ũ�� ����
#define USERBLOCK_SIZE 3

// Display ����
int DisplayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
// �迭�� ��� �պκ��� Y, ���� ��Ÿ���� �޺κ��� X, ���� ��Ÿ����.

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

	int GameGridData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
	int UseBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = { {1,1,1},{0,0,1},{0,0,1} };

	// �� �����Ǵ� ��ġ��	
	int BlockX = 0;
	int BlockY = 0;

	float BlockDownSpeed = 0;

	// ���ʿ� ���� ������ �ʱ�ȭ �ϴ� ������ �þ� �Ѵ�.
	void Init()
	{
	}

	// �� �����ӿ� �ҷ��� �Լ�
	void Next(float deltatime, char inputvalue)
	{
		BlockDownSpeed += deltatime;

		if (BlockDownSpeed >= .5f)
		{
			BlockY++;
			BlockDownSpeed -= .5f;
		}
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
