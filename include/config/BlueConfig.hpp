// Inclusion guard
#ifndef BLUE_CONFIG_HPP
#define BLUE_CONFIG_HPP

// Included libraries
#include "./main.h"

/**
 * This namespace manages the configuration of the blue robot
 */
namespace BlueConfig
{
    /**
     * The size of the tracking wheels on the drive
     */
    extern const double DRIVE_TRACKING_WHEEL_SIZE;

    /**
     * The distances between the drive tracking wheels and the center of the drive
     */
    extern const double DRIVE_LEFT_TRACKING_DISTANCE;
    extern const double DRIVE_RIGHT_TRACKING_DISTANCE;
    extern const double DRIVE_STRAFE_TRACKING_DISTANCE;

    /**
     * The number of counts the drive tracking wheels move per rotation
     */
    extern const double DRIVE_COUNTS_PER_ROTATION;

    /**
     * The bottom position of the lift in degrees
     */
    extern const double LIFT_BOTTOM_POSITION;

    /**
     * The top position of the lift in degrees
     */
    extern const double LIFT_TOP_POSITION;

    /**
     * The start position of the lift in degrees
     */
    extern const double LIFT_START_POSITION;

    /**
     * The number of encoder counts on the lift per degree of movement
     */
    extern const double LIFT_COUNTS_PER_DEGREE;

    /**
     * The ports for the left drive motors
     */
    extern const int LEFT_DRIVE_1_PORT;
    extern const int LEFT_DRIVE_2_PORT;
    extern const int LEFT_DRIVE_3_PORT;
    extern const int LEFT_DRIVE_4_PORT;

    /**
     * The ports for the right drive motors
     */
    extern const int RIGHT_DRIVE_1_PORT;
    extern const int RIGHT_DRIVE_2_PORT;
    extern const int RIGHT_DRIVE_3_PORT;
    extern const int RIGHT_DRIVE_4_PORT;

    /**
     * The ports for the intake motors
     */
    extern const int INTAKE_1_PORT;

    /**
     * The ports for the left lift motors
     */
    extern const int LEFT_LIFT_1_PORT;
    extern const int LEFT_LIFT_2_PORT;

    /**
     * The ports for the right lift motors
     */
    extern const int RIGHT_LIFT_1_PORT;
    extern const int RIGHT_LIFT_2_PORT;
    
    /**
     * The ports for the drive tracking sensors
     */
    extern const int LEFT_DRIVE_TRACKING_PORT;
    extern const int RIGHT_DRIVE_TRACKING_PORT;
    extern const int STRAFE_DRIVE_TRACKING_PORT;

    /**
     * The port for the inertial sensor
     */
    extern const int INERTIAL_PORT;

    /**
     * The port for the carrier piston
     */
    extern const char CARRIER_1_PORT;

    /**
     * The port for the claw piston
     */
    extern const char CLAW_1_PORT;
}

#endif