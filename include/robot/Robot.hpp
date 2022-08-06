// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included libraries
#include "./main.h"
#include "./subsystems/HoloDrive.hpp"
#include "./subsystems/TankDrive.hpp"
#include "./subsystems/Catapult.hpp"

/**
 * This class manages a robot
 */
class Robot
{
private:
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
        TankDrive* tankDrive;
        HoloDrive* holoDrive;
        Catapult* catapult;

        /**
         * Default constructor for RobotBuilder
         */
        RobotBuilder();

        /**
         * Default destructor for RobotBuilder
         */
        ~RobotBuilder();

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
};

#endif