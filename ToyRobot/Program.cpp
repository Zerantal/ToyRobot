// ToyRobot_CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <regex>
#include <tuple>
#include <vector>
#include <sstream>

#include "../RobotLib/ToyRobot.h"

Command ParseCommand(const std::string& cmdStr, std::tuple<int, int, Direction>& placeArgs);
std::vector<std::string> Tokenize(const std::string& str, const std::regex& re);

int main(const int argc, char *argv[])
{
    ToyRobot robot;
    bool suppressCmdPrompt = false;

    if (argc == 2 && strcmp(argv[1], "-s") == 0)
        suppressCmdPrompt = true;


    std::string cmdStr;
    std::tuple<int, int, Direction> placeArgs = std::make_tuple<int, int, Direction>(0, 0, North);
    bool running = true;
    while (running)
    {
        if (!suppressCmdPrompt) std::cout << "> "; // cmd prompt
        std::getline(std::cin, cmdStr);
        if (!std::cin)
            running = false;    // stop program (allow discrete commands to be piped from file to program)
        else
        {
            std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), [](const unsigned char c) {return toupper(c); });

            switch (ParseCommand(cmdStr, placeArgs))
            {
	            int yPos;
	            int xPos;
            case Place:
	            xPos = std::get<0>(placeArgs);
	            yPos = std::get<1>(placeArgs);
                if (xPos >= 0 && xPos < 5 && yPos >= 0 && yPos < 5)
                    robot.Place(std::get<0>(placeArgs), std::get<1>(placeArgs), std::get<2>(placeArgs));
                else
                    std::cout << "Place arguments out of range (x,y positions must be between 0 and 4 inclusively)" << std::endl;
                break;
            case Move:
                robot.Move();
                break;
            case Left:
                robot.TurnLeft();
                break;
            case Right:
                robot.TurnRight();
                break;
            case Report:
                std::cout << robot.Report() << std::endl;
                break;
            case Quit:
                running = false;
                break;
            case Invalid:
                std::cout << "Invalid Command" << std::endl;
                break;
            }
        }
    }

    return 0;
}

Command ParseCommand(const std::string& cmdStr, std::tuple<int, int, Direction>& placeArgs)
{
    std::stringstream ss(cmdStr);

    const std::regex re(R"([\s|,]+)");
    const std::vector<std::string> cmdTokens = Tokenize(cmdStr, re);

    if (cmdTokens.empty()) return Invalid;

    const auto iter = COMMAND_STR_MAP.find(cmdTokens[0]);
    if (iter == COMMAND_STR_MAP.end())
        return Invalid;

    if (iter->second == Place)
    {
        if (cmdTokens.size() < 4) return Invalid;

        // parse positional arguments
        int x, y;
        try
        {
            x = std::stoi(cmdTokens[1]);
            y = std::stoi(cmdTokens[2]);
        }
        catch (...)
        {
            return Invalid;
        }

        const auto dirArg = DIRECTION_STR_MAP.find(cmdTokens[3]);
        if (dirArg == DIRECTION_STR_MAP.end())
            return Invalid;

        std::get<0>(placeArgs) = x;
        std::get<1>(placeArgs) = y;
        std::get<2>(placeArgs) = dirArg->second;
    }

    return iter->second;
}

std::vector<std::string> Tokenize(const std::string& str, const std::regex& re)
{
    const std::sregex_token_iterator iter{ str.begin(),
                         str.end(), re, -1 };
    std::vector<std::string> tokens{ iter, {} };

    // Additional check to remove empty strings
    tokens.erase(
        std::remove_if(tokens.begin(),
            tokens.end(),
            [](std::string const& s) {
                return s.empty();
            }),
        tokens.end());

    return tokens;
}

