// Inclusion guard
#ifndef DRIVE_CONTROLLER_HPP
#define DRIVE_CONTROLLER_HPP

// Included headers
#include "./main.h"
#include "./robot/Robot.hpp"
#include "./menu/MenuData.hpp"
#include "pros/misc.hpp"

// Function prototypes
void positionUpdateFunction(void* parameters);
void positionPrintFunction(void* parameters);
void flywheelUpdateFunction(void* parameters);
void turretUpdateFunction(void* parameters);

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
     * Updates the controls for the tank drive
     * @param tankDrive The tank drive being controlled
     */
    void updateTankDrive(TankDrive* tankDrive, pros::Controller master);

    /**
     * Updates the controls for the holonomic drive
     * @param holoDrive The holonomic drive being controlled
     */
    void updateHoloDrive(HoloDrive* holoDrive, pros::Controller master);

    /**
     * Updates the controls for the catapult
     * @param holoDrive The catapult being controlled
     */
    void updateCatapult(Catapult* catapult, pros::Controller master);

    /**
     * Updates the controls for the flywheel
     * @param flywheel The flywheel being controlled
     */
    void updateFlywheel(Flywheel* flywheel, pros::Controller master);

    /**
     * Updates the controls for the turret
     * @param turret The turret being controlled
     */
    void updateTurret(Turret* turret, pros::Controller master);

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
     * Initializes the controller
     */
    void initialize();

    /**
     * Updates the controller
     */
    void update(pros::Controller master);
};

#endif