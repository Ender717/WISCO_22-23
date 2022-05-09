// Defined library
#include "config/BlueConfig.hpp"

namespace BlueConfig
{
    // Constants
    const double DRIVE_TRACKING_WHEEL_SIZE = 2.81;
    const double DRIVE_LEFT_TRACKING_DISTANCE = 3.53125;
    const double DRIVE_RIGHT_TRACKING_DISTANCE = 3.53125;
    const double DRIVE_STRAFE_TRACKING_DISTANCE = 3.125;
    const double DRIVE_COUNTS_PER_ROTATION = 36000.0;
    const double LIFT_BOTTOM_POSITION = -8.5;
    const double LIFT_TOP_POSITION = 100.0;
    const double LIFT_START_POSITION = 150.0;
    const double LIFT_COUNTS_PER_DEGREE = 10.0;

    // Motor ports
    const int LEFT_DRIVE_1_PORT = 10;
    const int LEFT_DRIVE_2_PORT = 2;
    const int LEFT_DRIVE_3_PORT = 4;
    const int LEFT_DRIVE_4_PORT = 5;
    const int RIGHT_DRIVE_1_PORT = 14;
    const int RIGHT_DRIVE_2_PORT = 13;
    const int RIGHT_DRIVE_3_PORT = 12;
    const int RIGHT_DRIVE_4_PORT = 11;
    const int INTAKE_1_PORT = 21;
    const int LEFT_LIFT_1_PORT = 6;
    const int LEFT_LIFT_2_PORT = 7;
    const int RIGHT_LIFT_1_PORT = 16;
    const int RIGHT_LIFT_2_PORT = 15;

    // Sensor ports
    const int LEFT_DRIVE_TRACKING_PORT = 8;
    const int RIGHT_DRIVE_TRACKING_PORT = 17;
    const int STRAFE_DRIVE_TRACKING_PORT = 9;
    const int INERTIAL_PORT = 20;

    // Piston ports
    const char CARRIER_1_PORT = 'H';
    const char CLAW_1_PORT = 'G';
}