// Inclusion guard
#ifndef ROBOT_MANAGER_HPP
#define ROBOT_MANAGER_HPP

// Included libraries
#include "./config/BlueConfig.hpp"
#include "./config/OrangeConfig.hpp"
#include "./config/TestConfig.hpp"
#include "./config/CandyConfig.hpp"
#include "Robot.hpp"
#include "./main.h"
#include "menu/Menu.hpp"

/**
 * This class manages robot creation
 */
class RobotManager
{
private:
    /**
     * The robot being created by the manager
     */
    Robot* robot;

    /**
     * Creates a pre-configured blue match robot
     */
    void createMatchBlueRobot();

    /**
     * Creates a pre-configured orange match robot
     */
    void createMatchOrangeRobot();

    /**
     * Creates a pre-configured blue skills robot
     */
    void createSkillsBlueRobot();

    /**
     * Creates a pre-configured orange skills robot
     */
    void createSkillsOrangeRobot();

    /**
     * Creates a pre-configured test robot
     */
    void createTestRobot();

    /**
     * Creates a pre=configured candy robot
     */
    void createCandyRobot();

public:
    /**
     * Default constructor for RobotManager
     */
    RobotManager();

    /**
     * Default destructor for RobotManager
     */
    ~RobotManager();
    
    /**
     * Creates a robot of the specified configuration
     * @param config The configuration of robot to create
     */
    void createRobot(Menu::Configurations config);

    /**
     * Gets the stored robot configuration
     * @return The robot which was created
     */
    Robot* getRobot();
};

#endif