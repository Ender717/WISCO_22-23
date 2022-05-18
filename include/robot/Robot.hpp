// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included libraries
#include "./subsystems/TankDrive.hpp"
#include "./subsystems/Carrier.hpp"
#include "./subsystems/Lift.hpp"
#include "./subsystems/Claw.hpp"
#include "./subsystems/Intake.hpp"
#include "./main.h"

/**
 * This enum manages different possible robot configurations
 */
enum class RobotConfigs
{
    BLUE,
    ORANGE
};

/**
 * This class manages a robot
 */
class Robot
{
private:
    /**
     * The configuration of this robot
     */
    RobotConfigs configuration;

public:
    /**
     * Builder class for Robot
     */
    class RobotBuilder
    {
    public:
        /**
         * Attributes for construction
         */
        RobotConfigs* configuration;

        /**
         * Default constructor for RobotBuilder
         */
        RobotBuilder();

        /**
         * Default destructor for RobotBuilder
         */
        ~RobotBuilder();

        /**
         * Add a configuration to the build
         * @param configuration The configuration being added
         * @return The builder for build chaining
         */
        RobotBuilder* withConfiguration(RobotConfigs configuration);

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
     * Controls the robot using controller input
     * @param master The controller
     */
    void robotControl(pros::Controller& master);
};

#endif