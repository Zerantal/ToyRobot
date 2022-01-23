#include "pch.h"

#include <cassert>
#include <sstream>

#include "ToyRobot.h"

bool ToyRobot::OffTable() const
{
	return XPos == -1;
}

void ToyRobot::Place(const int x, const int y, const Direction dir)
{
	assert(x >= 0 && x < TableXDim);
	assert(y >= 0 && y < TableYDim);

	XPos = x;
	YPos = y;
	Dir = dir;
}

void ToyRobot::Move()
{
	if (OffTable())
		return;

	int newX = XPos;
	int newY = YPos;

	switch(Dir)
	{
	case North:
		newY++;
		break;
	case East:
		newX++;
		break;
	case South:
		newY--;
		break;
	case West:
		newX--;
		break;
	}

	if (newX >= 0 && newX < TableXDim && newY >=0 && newY < TableYDim)
	{
		XPos = newX;
		YPos = newY;
	}
}

void ToyRobot::TurnLeft()
{
	if (OffTable())
		return;

	switch(Dir)
	{
	case North: Dir = West; break;
	case East: Dir = North; break;
	case South: Dir = East;  break;
	case West: Dir = South; break;
	}
}

void ToyRobot::TurnRight()
{
	if (OffTable())
		return;

	switch(Dir)
	{
	case North: Dir = East; break;
	case East: Dir = South; break;
	case South: Dir = West; break;
	case West: Dir = North; break;
	}
}

std::string ToyRobot::Report(const bool generateVisual) const
{
	if (OffTable())
		return "Robot not placed on table.";

	std::stringstream reportStr;

	if (generateVisual)
	{
		for (int y = TableYDim; y >= 0; y--)
		{
			for (int x = 0; x < TableXDim; x++)
			{
				// admittedly this may not be efficient for large table dimensions
				if (XPos != x || YPos != y)
					reportStr << "-";
				else
					reportStr << "X";
			}
			reportStr << std::endl;
		}
	}

	// print last line regardless of whether robot has been placed on table
	const auto dirString = std::find_if(std::begin(DIRECTION_STR_MAP), std::end(DIRECTION_STR_MAP), [&](const std::pair<std::string, Direction> &pair)
	{
		return pair.second == Dir;
	});

	reportStr << XPos << "," << YPos << "," << dirString->first;

	return reportStr.str();
}


