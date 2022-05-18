// Included libraries
#include "robot/RobotManager.hpp"

// Constructor definitions -----------------------------------------------------
RobotManager::RobotManager()
{
    robot = nullptr;
}

// Destructor definitions ------------------------------------------------------
RobotManager::~RobotManager()
{
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

// Private method definitions --------------------------------------------------
void RobotManager::createBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

// Public method definitions --------------------------------------------------
void RobotManager::createRobot(RobotConfigs config)
{
    switch (config)
    {
        case RobotConfigs::BLUE:
            createBlueRobot();
            break;
        case RobotConfigs::ORANGE:
            createOrangeRobot();
            break;
    }
}

Robot* RobotManager::getRobot()
{
    return robot;
}