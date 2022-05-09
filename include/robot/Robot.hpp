// Inclusion guard
#ifndef ROBOT_H
#define ROBOT_H

// Included libraries
#include "./subsystems/Drive.hpp"
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
    RobotConfigs* configuration;

    /**
     * Updates the carrier using the controller input
     * @param master The controller being used
     */
    void UpdateCarrier(pros::Controller& master);

    /**
     * Updates the claw using the controller input
     * @param master The controller being used
     */
    void UpdateClaw(pros::Controller& master);

    /**
     * Updates the drive using the controller input
     * @param master The controller being used
     */
    void UpdateDrive(pros::Controller& master);

    /**
     * Updates the intake using the controller input
     * @param master The controller being used
     */
    void UpdateIntake(pros::Controller& master);

    /**
     * Updates the lift using the controller input
     * @param master The controller being used
     */
    void UpdateLift(pros::Controller& master);

public:
    /**
     * The subsystems contained in the robot
     */
    Drive* drive;
	Carrier* carrier;
	Lift* lift;
	Claw* claw;
	Intake* intake;

    /**
     * Builder class for Robot
     */
    class RobotBuilder
    {
    public:
        /**
         * The data being used to build the robot
         */
        RobotConfigs* configuration;
        Carrier* carrier;
        Claw* claw;
        Drive* drive;
        Intake* intake;
        Lift* lift;

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
        RobotBuilder* WithConfiguration(RobotConfigs* configuration);

        /**
         * Add a carrier to the build
         * @param carrier The carrier being added
         * @return The builder for build chaining
         */
        RobotBuilder* WithCarrier(Carrier* carrier);

         /**
         * Add a claw to the build
         * @param claw The claw being added
         * @return The builder for build chaining
         */
        RobotBuilder* WithClaw(Claw* claw);

         /**
         * Add a drive to the build
         * @param drive The drive being added
         * @return The builder for build chaining
         */
        RobotBuilder* WithDrive(Drive* drive);

         /**
         * Add an intake to the build
         * @param intake The intake being added
         * @return The builder for build chaining
         */
        RobotBuilder* WithIntake(Intake* intake);

         /**
         * Add a lift to the build
         * @param lift The lift being added
         * @return The builder for build chaining
         */
        RobotBuilder* WithLift(Lift* lift);

        /**
         * Builds a robot using the stored data
         * @return The new robot
         */
        Robot* Build();
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
    void Initialize();

    /**
     * Controls the robot using controller input
     * @param master The controller
     */
    void RobotControl(pros::Controller& master);
};

#endif