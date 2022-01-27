#include "pch.h"

#include "../RobotLib/ToyRobot.h"

struct ToyRobotTest : testing::Test
{
	std::unique_ptr<ToyRobot> Robot;

	void SetUp() override
	{
		Robot = std::make_unique<ToyRobot>();
	}
};

TEST_F(ToyRobotTest, RobotPlacedTooFarWest)
{
	ASSERT_DEATH(Robot->Place(-1, 0, North), "");
}

TEST_F(ToyRobotTest, RobotPlacedTooFarEast)
{
	ASSERT_DEATH(Robot->Place(5, 0, East), "");
}

TEST_F(ToyRobotTest, RobotPlacedTooFarNorth)
{
	ASSERT_DEATH(Robot->Place(3, 5, East), "");
}

TEST_F(ToyRobotTest, RobotPlacedTooFarSouth)
{
	ASSERT_DEATH(Robot->Place(2, -1, East), "");
}


TEST_F(ToyRobotTest, RobotMoveOnTable)
{
	// move North
	Robot->Place(2, 2, North);
	Robot->Move();
	EXPECT_STREQ("2,3,NORTH", Robot->Report(false).c_str());

	// move East
	Robot->Place(2, 2, East);
	Robot->Move();
	EXPECT_STREQ("3,2,EAST", Robot->Report(false).c_str());

	// move South
	Robot->Place(2, 2, South);
	Robot->Move();
	EXPECT_STREQ("2,1,SOUTH", Robot->Report(false).c_str());

	// move West
	Robot->Place(2, 2, West);
	Robot->Move();
	EXPECT_STREQ("1,2,WEST", Robot->Report(false).c_str());
}

TEST_F(ToyRobotTest, RobotMoveOffTable)
{
	// move too far north
	Robot->Place(0, 4, North);
	Robot->Move();
	EXPECT_STRCASEEQ("0,4,North", Robot->Report(false).c_str());

	// move too far east
	Robot->Place(4, 0, East);
	Robot->Move();
	EXPECT_STRCASEEQ("4,0,East", Robot->Report(false).c_str());

	// move too far south
	Robot->Place(0, 0, South);
	Robot->Move();
	EXPECT_STRCASEEQ("0,0,South", Robot->Report(false).c_str());

	// move too far west
	Robot->Place(0, 0, West);
	Robot->Move();
	EXPECT_STRCASEEQ("0,0,West", Robot->Report(false).c_str());
}

TEST_F(ToyRobotTest, RobotTurnLeft)
{
	Robot->Place(3, 2, North);
	Robot->TurnLeft();
	EXPECT_STRCASEEQ("3,2,West", Robot->Report(false).c_str());
	Robot->TurnLeft();
	EXPECT_STRCASEEQ("3,2,South", Robot->Report(false).c_str());
	Robot->TurnLeft();
	EXPECT_STRCASEEQ("3,2,east", Robot->Report(false).c_str());
	Robot->TurnLeft();
	EXPECT_STRCASEEQ("3,2,north", Robot->Report(false).c_str());
}

TEST_F(ToyRobotTest, RobotTurnRight)
{
	Robot->Place(3, 2, North);
	Robot->TurnRight();
	EXPECT_STRCASEEQ("3,2,east", Robot->Report(false).c_str());
	Robot->TurnRight();
	EXPECT_STRCASEEQ("3,2,south", Robot->Report(false).c_str());
	Robot->TurnRight();
	EXPECT_STRCASEEQ("3,2,west", Robot->Report(false).c_str());
	Robot->TurnRight();
	EXPECT_STRCASEEQ("3,2,north", Robot->Report(false).c_str());
}

TEST_F(ToyRobotTest, RobotReport)
{
	EXPECT_STREQ("Robot not placed on table.", Robot->Report().c_str());
	Robot->Place(2, 2, East);
	EXPECT_STRCASEEQ("2,2,East", Robot->Report(false).c_str());
	EXPECT_STRCASEEQ(
		"-----\n"
		"-----\n"
		"--X--\n"
		"-----\n"
		"-----\n"
		"2,2,EAST", Robot->Report().c_str());
}