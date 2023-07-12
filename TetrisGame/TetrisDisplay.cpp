#include "TetrisDisplay.h"
#include "TetrisHelper.h"
#include "TetrisInfoHeader.h"

TetrisDisplay::TetrisDisplay()
{
	info = new TetrisInfoHeader();
}

TetrisDisplay::~TetrisDisplay()
{
	delete info;
}

void TetrisDisplay::Render()
{
	for (int i = 0; i < TGRID_HEIGHT; i++)
	{
		for (int j = 0; j < TGRID_WIDTH; j++)
		{
			//(DisplayData[i][j] == 0) ? drawPosition(j, i, false) : drawPosition(j, i, true);
			drawPosition(j, i, !(info->TetrisDisplayData[i][j] == 0));
		}
	}
}
