// Inclusion guard
#ifndef DRIVE_CONTROLLER_HPP
#define DRIVE_CONTROLLER_HPP

// Included headers
#include "./main.h"
#include "./robot/Robot.hpp"
#include "./menu/MenuData.hpp"

/**
 * This class manages subsystem control for the robot
 * @author Nathan Sandvig
 */
class DriveController
{
private:
    /**
     * The robot being controlled
     */
    Robot* robot;

    /**
     * Updates the controls for the holonomic drive
     * @param holoDrive The holonomic drive being controlled
     */
    void updateHoloDrive(HoloDrive* holoDrive, pros::Controller master);

public:
    /**
     * Parameterized constructor for a drive controller
     * @param robot The robot being controlled
     */
    DriveController(Robot* robot);

    /**
     * Default destructor for the drive controller
     */
    ~DriveController();

    /**
     * Updates the controller
     */
    void update(pros::Controller master);
};

#endif