// Inclusion guard
#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

// Included libraries
#include "./main.h"

/**
 * This namespace manages the configuration of the test robot
 */
namespace TestConfig
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
     * The ports for the left front drive motors
     */
    extern const int LEFT_FRONT_DRIVE_1_PORT;

    /**
     * The ports for the left rear drive motors
     */
    extern const int LEFT_REAR_DRIVE_1_PORT;

    /**
     * The ports for the right front drive motors
     */
    extern const int RIGHT_FRONT_DRIVE_1_PORT;

    /**
     * The ports for the right rear drive motors
     */
    extern const int RIGHT_REAR_DRIVE_1_PORT;

    /**
     * The ports for the turret motors
     */
    extern const int TURRET_1_PORT;

    /**
     * The port for the vision sensor
     */
    extern const int VISION_PORT;
    
    /**
     * The ports for the drive tracking sensors
     */
    extern const int LEFT_DRIVE_TRACKING_PORT;
    extern const int RIGHT_DRIVE_TRACKING_PORT;
    extern const int STRAFE_DRIVE_TRACKING_PORT;

    /**
     * The port for the drive inertial sensor
     */
    extern const int DRIVE_INERTIAL_PORT;

    /**
     * The port for the turret inertial sensor
     */
    extern const int TURRET_INERTIAL_PORT;
}

#endif