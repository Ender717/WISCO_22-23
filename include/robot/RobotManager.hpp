// Inclusion guard
#ifndef ROBOT_MANAGER_HPP
#define ROBOT_MANAGER_HPP

// Included libraries
#include "./config/BlueConfig.hpp"
#include "./config/OrangeConfig.hpp"
#include "Robot.hpp"
#include "./main.h"

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
     * Creates a pre-configured blue robot
     */
    void CreateBlueRobot();

    /**
     * Creates a pre-configured orange robot
     */
    void CreateOrangeRobot();

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
    void CreateRobot(RobotConfigs config);

    /**
     * Gets the stored robot configuration
     * @return The robot which was created
     */
    Robot* GetRobot();
};

#endif