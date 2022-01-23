#pragma once
#include <map>

enum Direction
{
	North,
	East,
	South,
	West
};
static const std::map<std::string, Direction> DIRECTION_STR_MAP = {
	{"NORTH", North },
	{"EAST", East},
	{"SOUTH", South },
	{"WEST", West} };

enum Command
{
	Place,
	Move,
	Left,
	Right,
	Report,
	Quit,
	Invalid
};
static const std::map<std::string, Command> COMMAND_STR_MAP = {
	{"PLACE", Place},
	{"MOVE", Move},
	{"LEFT", Left},
	{"RIGHT", Right},
	{"REPORT", Report},
	{"QUIT", Quit},
	{"INVALID", Invalid}};
