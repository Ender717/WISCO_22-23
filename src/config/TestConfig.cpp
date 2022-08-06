#include "TestConfig.hpp"

namespace TestConfig
{
    // Constants
    const double DRIVE_TRACKING_WHEEL_SIZE = 2.75;
    const double DRIVE_LEFT_TRACKING_DISTANCE = 0.0;
    const double DRIVE_RIGHT_TRACKING_DISTANCE = 0.0;
    const double DRIVE_STRAFE_TRACKING_DISTANCE = 0.0;
    const double DRIVE_COUNTS_PER_ROTATION = 36000;

    // Motor ports
    const int LEFT_FRONT_DRIVE_1_PORT = 19;
    const int LEFT_REAR_DRIVE_1_PORT = 20;
    const int RIGHT_FRONT_DRIVE_1_PORT = 12;
    const int RIGHT_REAR_DRIVE_1_PORT = 11;
    const int TURRET_1_PORT = 18;

    // Sensor ports
    const int VISION_PORT = 9;
    const int LEFT_DRIVE_TRACKING_PORT = -1;
    const int RIGHT_DRIVE_TRACKING_PORT = -1;
    const int STRAFE_DRIVE_TRACKING_PORT = -1;
    const int DRIVE_INERTIAL_PORT = 13;
    const int TURRET_INERTIAL_PORT = 8;
}