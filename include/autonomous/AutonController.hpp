// Inclusion guard
#ifndef AUTON_CONTROLLER_HPP
#define AUTON_CONTROLLER_HPP

// Included libraries
#include "./robot/Robot.hpp"
#include "./main.h"

/**
 * This namespace manages the autonomous tasks
 */
namespace AutonController
{
    /**
     * The robot performing the tasks
     */
    extern Robot* robot;
};

#endif