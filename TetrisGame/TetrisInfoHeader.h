#pragma once

// 게임 화면 사이즈
#define TGRID_WIDTH 14
#define TGRID_HEIGHT 25

// 떨어지는 블록의 크기 제한
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
	// Display 관련
	int TetrisDisplayData[TGRID_HEIGHT][TGRID_WIDTH] = { 0, };
};