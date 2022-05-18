// Inclusion guard
#ifndef AUTONS_HPP
#define AUTONS_HPP

// Included libraries
#include "AutonController.hpp"
#include "./main.h"

/**
 * This namespace manages all the autonomous routines
 */
namespace Autons
{
    /**
     * The number of auton routines in the system
     */
    extern const int NUM_AUTONS;

    /**
     * The number of the auton which was selected
     */
    extern int selectedAuton;
}

#endif