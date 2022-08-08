#include "TestConfig.hpp"

namespace TestConfig
{
    // Constants
    const double DRIVE_TRACKING_WHEEL_SIZE = 2.75;
    const double DRIVE_LINEAR_TRACKING_DISTANCE = 7.75;
    const double DRIVE_STRAFE_TRACKING_DISTANCE = -7.75;
    const double DRIVE_COUNTS_PER_ROTATION = 36000;
    const double FLYWHEEL_WHEEL_SIZE = 3.25;
    const double FLYWHEEL_COUNTS_PER_REVOLUTION = 42.86;
    const double FLYWHEEL_MAX_RPM = 3500.0;

    // Motor ports
    const int LEFT_FRONT_DRIVE_1_PORT = 19;
    const int LEFT_REAR_DRIVE_1_PORT = 20;
    const int RIGHT_FRONT_DRIVE_1_PORT = 12;
    const int RIGHT_REAR_DRIVE_1_PORT = 2;
    const int FLYWHEEL_1_PORT = 14;
    const int TURRET_1_PORT = 18;

    // Sensor ports
    const int VISION_PORT = 8;
    const int LINEAR_DRIVE_TRACKING_PORT = 16;
    const int STRAFE_DRIVE_TRACKING_PORT = 17;
    const int DRIVE_INERTIAL_PORT = 11;
    const int TURRET_INERTIAL_PORT = 9;
}