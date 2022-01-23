#pragma once

#include <string>

#include "Enums.h"

class ToyRobot
{
	const int TableXDim = 5;
	const int TableYDim = 5;

	int XPos = -1;
	int YPos = -1;
	Direction Dir = North;

	bool OffTable() const;

public:
	void Place(int x, int y, Direction dir);
	void Move();
	void TurnLeft();
	void TurnRight();
	std::string Report(bool generateVisual = true) const;
};

