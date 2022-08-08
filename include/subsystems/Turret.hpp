// Inclusion guard
#ifndef TURRET_HPP
#define TURRET_HPP

// Included libraries
#include <list>
#include <cfloat>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class defines a turret subsystem for the robot
 * @author Nathan Sandvig
 */
class TURRET
{
private:
    std::list<pros::Motor*>* motorList;
    pros::Imu* inertialSensor;
    PID* turretPID;
    double minPosition;
    double maxPosition;

public:
    class TurretBuilder
    {
    public:

    };
};

#endif