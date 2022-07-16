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
    robot = nullptr;
}

// Private method definitions --------------------------------------------------
void RobotManager::createMatchBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createMatchOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createSkillsBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createSkillsOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createTestRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }

    // Create the holo drive
    HoloDrive::HoloDriveBuilder* holoDriveBuilder = new HoloDrive::HoloDriveBuilder();
    HoloDrive* holoDrive = holoDriveBuilder->
        withLeftFrontMotor(pros::Motor(TestConfig::LEFT_FRONT_DRIVE_1_PORT, E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withLeftRearMotor(pros::Motor(TestConfig::LEFT_REAR_DRIVE_1_PORT, E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withRightFrontMotor(pros::Motor(TestConfig::RIGHT_FRONT_DRIVE_1_PORT, E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS))->
        withRightRearMotor(pros::Motor(TestConfig::RIGHT_REAR_DRIVE_1_PORT, E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS))->
        build();
    delete holoDriveBuilder;
    holoDriveBuilder = nullptr;

    // Create the robot
    Robot::RobotBuilder* robotBuilder = new Robot::RobotBuilder();
    robot = robotBuilder->
        withHoloDrive(holoDrive)->
        build();
    delete robotBuilder;
    robotBuilder = nullptr;
}

// Public method definitions --------------------------------------------------
void RobotManager::createRobot(Menu::Configurations config)
{
    switch (config)
    {
        case Menu::Configurations::MATCH_BLUE:
            createMatchBlueRobot();
            break;
        case Menu::Configurations::MATCH_ORANGE:
            createMatchOrangeRobot();
            break;
        case Menu::Configurations::SKILLS_BLUE:
            createSkillsBlueRobot();
            break;
        case Menu::Configurations::SKILLS_ORANGE:
            createSkillsOrangeRobot();
            break;
        case Menu::Configurations::TEST:
            createTestRobot();
            break;
    }
}

Robot* RobotManager::getRobot()
{
    return robot;
}