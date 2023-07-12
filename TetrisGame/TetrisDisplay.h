#pragma once

class TetrisInfoHeader;

class TetrisDisplay
{
public:
	TetrisDisplay();
	~TetrisDisplay();

	void Render();

private:
	TetrisInfoHeader* info;
};

