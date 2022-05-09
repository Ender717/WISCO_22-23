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

    /**
     * Runs a custom start task for the left auton for the blue robot
     */
    extern void DoLeftStartTaskBlue();

    /**
     * Runs a custom start task for the middle auton for the blue robot
     */
    extern void DoMiddleStartTaskBlue();

    /**
     * Runs a custom start task for the right auton for the blue robot
     */
    extern void DoRightStartTaskBlue();

    /**
     * Runs a custom start task for the left auton for the orange robot
     */
    extern void DoLeftStartTaskOrange();

    /**
     * Runs a custom start task for the middle auton for the orange robot
     */
    extern void DoMiddleStartTaskOrange();

    /**
     * Runs a custom start task for the right auton for the orange robot
     */
    extern void DoRightStartTaskOrange();

    /**
     * Runs a task based on distance using driveStraight
     * @param distance The distance to drive
     * @param angle The angle to drive at
     * @param liftAngle The angle to set the lift to
     * @param clawClosed Whether or not to close the claw
     * @param carrierDown Whether or not to put down the carrier
     * @param intake Whether or not to intake
     */
    extern void DoDistanceTask(double distance, double angle, double liftAngle, 
        bool clawClosed, bool carrierDown, bool intake);

    /**
     * Runs a task based on distance using driveStraight
     * @param distance The distance to drive
     * @param angle The angle to drive at
     * @param power The power to drive at
     * @param liftAngle The angle to set the lift to
     * @param clawClosed Whether or not to close the claw
     * @param carrierDown Whether or not to put down the carrier
     * @param intake Whether or not to intake
     */
    extern void DoThroughDistanceTask(double distance, double angle, double power, 
        double liftAngle, bool clawClosed, bool carrierDown, bool intake);

    /**
     * Runs a task based on angle using turnToAngle
     * @param targetAngle The angle to turn to
     * @param liftAngle The angle to set the lift to
     * @param clawClosed Whether or not to close the claw
     * @param carrierDown Whether or not to put down the carrier
     * @param intake Whether or not to intake
     */
    extern void DoTurnTask(double targetAngle, double liftAngle, bool clawClosed,
        bool carrierDown, bool intake);
};

#endif