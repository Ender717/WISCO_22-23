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
     * The tuning multipliers for the position tracking sensors
     */
    extern const double DRIVE_LINEAR_TRACKING_MULTIPLIER;
    extern const double DRIVE_STRAFE_TRACKING_MULTIPLIER;
    extern const double DRIVE_INERTIAL_MULTIPLIER;

    /**
     * The distances between the drive tracking wheels and the center of the drive
     */
    extern const double DRIVE_LINEAR_TRACKING_DISTANCE;
    extern const double DRIVE_STRAFE_TRACKING_DISTANCE;

    /**
     * The number of counts the drive tracking wheels move per rotation
     */
    extern const double DRIVE_COUNTS_PER_ROTATION;

    /**
     * The diameter of the flywheel
     */
    extern const double FLYWHEEL_WHEEL_SIZE;

    /**
     * The counts per revolution of the flywheel
     */
    extern const double FLYWHEEL_COUNTS_PER_REVOLUTION;

    /**
     * The maximum RPM of the flywheel
     */
    extern const double FLYWHEEL_MAX_RPM;

    /**
     * The starting angle of the turret
     */
    extern const double TURRET_START_ANGLE;

    /**
     * The counts per degree for the turret
     */
    extern const double TURRET_COUNTS_PER_DEGREE;

    /**
     * The minimum angle of the turret
     */
    extern const double TURRET_MIN_ANGLE;

    /**
     * The maximum angle of the turret
     */
    extern const double TURRET_MAX_ANGLE;

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
     * The ports for the flywheel motors
     */
    extern const int FLYWHEEL_1_PORT;

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
    extern const int LINEAR_DRIVE_TRACKING_PORT;
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