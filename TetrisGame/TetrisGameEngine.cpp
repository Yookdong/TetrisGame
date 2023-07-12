#include "TetrisGameEngine.h"
#include "TetrisInfoHeader.h"

TetrisGameEngine* TetrisGameEngine::TetrisGEInstance = nullptr;

TetrisGameEngine::TetrisGameEngine()
{
	TetrisGEInstance = this;

	CurrentState = TGameState::GAMEPLAY;

	GameGridData[TGRID_HEIGHT][TGRID_WIDTH] = { 0, };
	UseBlock[TUSERBLOCK_SIZE][TUSERBLOCK_SIZE] = { 0, };

	//UserBlockVarious[0][TUSERBLOCK_SIZE][TUSERBLOCK_SIZE] = { {0,1,0},{0,1,0},{0,1,0} };
	//UserBlockVarious[1][TUSERBLOCK_SIZE][TUSERBLOCK_SIZE] = { {0,0,0},{0,1,1},{0,1,1} };
	//UserBlockVarious[2][TUSERBLOCK_SIZE][TUSERBLOCK_SIZE] = { {0,0,0},{0,1,0},{1,1,1} };

	// 블럭 생성되는 위치값	
	BlockX = 0;
	BlockY = 0;

	BlockDownSpeed = 0;
	BlockMoveRL = 0;

}

TetrisGameEngine::~TetrisGameEngine()
{
}
