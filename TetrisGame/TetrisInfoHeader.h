#pragma once

// ���� ȭ�� ������
#define TGRID_WIDTH 14
#define TGRID_HEIGHT 25

// �������� ����� ũ�� ����
#define TUSERBLOCK_SIZE 3


enum class TGameState
{
	GAMEPLAY, GAMEOVER
};

class TetrisInfoHeader
{
public:
	TetrisInfoHeader();
	~TetrisInfoHeader();
	// Display ����
	int TetrisDisplayData[TGRID_HEIGHT][TGRID_WIDTH] = { 0, };
};