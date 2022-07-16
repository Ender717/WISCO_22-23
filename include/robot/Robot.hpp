// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included libraries
#include "./main.h"
#include "./subsystems/HoloDrive.hpp"

/**
 * This class manages a robot
 */
class Robot
{
private:
    /**
     * The holonomic drive for the robot
     */
    HoloDrive* holoDrive;

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
        HoloDrive* holoDrive;

        /**
         * Default constructor for RobotBuilder
         */
        RobotBuilder();

        /**
         * Default destructor for RobotBuilder
         */
        ~RobotBuilder();

        /**
         * Wither method to add a holoDrive to the build
         * @param holoDrive the holoDrive object being added
         * @return The builder for build chaining
         */
        RobotBuilder* withHoloDrive(HoloDrive* holoDrive);

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
     * Gets the holoDrive for this robot
     * @return A pointer to the holo drive
     */
    HoloDrive* getHoloDrive();
};

#endif