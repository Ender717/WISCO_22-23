// Inclusion guard
#ifndef ROBOT_STATE_HPP
#define ROBOT_STATE_HPP

// Included libraries
#include "Robot.hpp"
#include "RobotManager.hpp"
#include "./main.h"

/**
 * Stores the robot state
 */
namespace RobotState
{
    /**
     * The current robot
     */
    extern Robot* robot;

    /**
     * The chosen configuration for the robot
     */
    extern RobotConfigs* configuration;
};

#endif