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

    /**
     * The programming skills routine for the blue robot
     */
    extern void ProgrammingSkillsBlue();

    /**
     * The programming skills routine for the orange robot
     */
    extern void ProgrammingSkillsOrange();

    /**
     * The left goal auton routine for the blue robot
     */
    extern void LeftAutonBlue();

    /**
     * The middle goal auton routine for the blue robot
     */
    extern void MiddleAutonBlue();

    /**
     * The right goal auton routine for the blue robot
     */
    extern void RightAutonBlue();

    /**
     * The left goal auton routine for the orange robot
     */
    extern void LeftAutonOrange();

    /**
     * The middle goal auton routine for the orange robot
     */
    extern void MiddleAutonOrange();

    /**
     * The right goal auton routine for the orange robot
     */
    extern void RightAutonOrange();
}

#endif