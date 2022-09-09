// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included libraries
#include "./main.h"
#include "./processes/PositionSystem.hpp"
#include "./subsystems/HoloDrive.hpp"
#include "./subsystems/TankDrive.hpp"
#include "./subsystems/Catapult.hpp"
#include "./subsystems/Flywheel.hpp"
#include "./subsystems/Turret.hpp"

/**
 * This class manages a robot
 */
class Robot
{
private:
    /**
     * The position tracking system for the robot
     */
    PositionSystem* positionSystem;

    /**
     * The tank drive for the robot
     */
    TankDrive* tankDrive;

    /**
     * The holonomic drive for the robot
     */
    HoloDrive* holoDrive;

    /**
     * The catapult for the robot
     */
    Catapult* catapult;

    /**
     * The flywheel for the robot
     */
    Flywheel* flywheel;

    /**
     * The turret for the robot
     */
    Turret* turret;

public:
    /**
     * Builder class for Robot
     */
    class RobotBuilder
    {
    public:
        /**
         * Build attributes
         */
        PositionSystem* positionSystem;
        TankDrive* tankDrive;
        HoloDrive* holoDrive;
        Catapult* catapult;
        Flywheel* flywheel;
        Turret* turret;

        /**
         * Default constructor for RobotBuilder
         */
        RobotBuilder();

        /**
         * Default destructor for RobotBuilder
         */
        ~RobotBuilder();

        /**
         * Wither method to add a positionSystem to the build
         * @param positionSystem the positionSystem object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withPositionSystem(PositionSystem* positionSystem);

        /**
         * Wither method to add a tankDrive to the build
         * @param tankDrive the tankDrive object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withTankDrive(TankDrive* tankDrive);

        /**
         * Wither method to add a holoDrive to the build
         * @param holoDrive the holoDrive object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withHoloDrive(HoloDrive* holoDrive);

        /**
         * Wither method to add a catapult to the build
         * @param catapult the catapult object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withCatapult(Catapult* catapult);

        /**
         * Wither method to add a flywheel to the build
         * @param flywheel the flywheel object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withFlywheel(Flywheel* flywheel);

        /**
         * Wither method to add a turret to the build
         * @param turret the turret object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withTurret(Turret* turret);

        /**
         * Builds a robot using the stored data
         * @return The new robot
         */
        Robot* build();
    };

    /**
     * Builder constructor for Robot
     * @param builder The builder being used for construction
     * @param configuration The configuration of the robot
     */
    Robot(RobotBuilder* builder);

    /**
     * Default destructor for Robot
     */
    ~Robot();

    /**
     * Initializes the robot
     */
    void initialize();

    /**
     * Gets the positionSystem for this robot
     * @return A pointer to the position system
     */
    PositionSystem* getPositionSystem();

    /**
     * Gets the tankDrive for this robot
     * @return A pointer to the tank drive
     */
    TankDrive* getTankDrive();

    /**
     * Gets the holoDrive for this robot
     * @return A pointer to the holo drive
     */
    HoloDrive* getHoloDrive();

    /**
     * Gets the catapult for this robot
     * @return A pointer to the catapult
     */
    Catapult* getCatapult();

    /**
     * Gets the flywheel for this robot
     * @return A pointer to the flywheel
     */
    Flywheel* getFlywheel();

    /**
     * Gets the turret for this robot
     * @return A pointer to the turret
     */
    Turret* getTurret();
};

#endif