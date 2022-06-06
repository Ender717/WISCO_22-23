// Inclusion guard
#ifndef MENU_HPP
#define MENU_HPP

// Included libraries
#include "./robot/RobotState.hpp"
#include "./processes/Position.hpp"
#include "./autonomous/autons.hpp"
#include "./main.h"

/**
 * This namespace manages the menu system
 */
namespace Menu
{
    /**
     * Whether an autonomous has been selected or not
     */
    extern bool autonSelected;

    /**
     * Whether a robot has been selected or not
     */
    extern bool robotSelected;

    /**
     * Erases the area within the specified coordinates
     * @param x1 The left side of the area
     * @param y1 The top of the area
     * @param x2 The right side of the area
     * @param y2 The bottom of the area
     */
    extern void erase(int x1, int y1, int x2, int y2);
    
    /**
     * Draws a selection menu
     */
    extern void drawMenuSelect();

    /**
     * Runs the autonomous selection process
     */
    extern void autonSelect();

    /**
     * Runs the robot selection process
     */
    extern void robotSelect();

    /**
     * Draws the current position of the robot on a 2d field
     * @param position The position which is being drawn
     */
    extern void drawPosition(Position position);
}

#endif