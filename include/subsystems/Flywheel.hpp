// Inclusion guard
#ifndef FLYWHEEL_H
#define FLYWHEEL_H

// Included libraries
#include <list>
#include <cfloat>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class manages a flywheel subsystem for the robot
 * @author Nathan Sandvig
 */
class Flywheel
{
private:
    /**
     * The list of motors on the flywheel
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The PID controller for the flywheel's velocity
     */
    PID* flywheelPID;

    /**
     * The diameter of the flywheel
     */
    double wheelSize;

    /**
     * The number of encoder counts per flywheel revolution
     */
    double countsPerRevolution;

    /**
     * The power currently being sent to the motors
     */
    double motorPower;

    /**
     * The position of the flywheel during the last loop
     * Used for RPM tracking
     */
    double lastPosition;

    /**
     * The system clock time during the last loop
     * Used for RPM tracking
     */
    double lastTime;

    /**
     * The current rpm of the flywheel
     */
    double currentRPM;

    /**
     * The target rpm of the flywheel
     */
    double targetRPM;

public:
    /**
     * Builder class for Flywheel
     */
    class FlywheelBuilder
    {
    public:
        /**
         * The data being used to build the flywheel
         */
        std::list<pros::Motor*>* motorList;
        PID* flywheelPID;
        double* wheelSize;
        double* countsPerRevolution;

        /**
         * Default constructor for FlywheelBuilder
         */
        FlywheelBuilder();

        /**
         * Default destructor for FlywheelBuilder
         */
        ~FlywheelBuilder();

        /**
         * Adds a motor to the builder data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        FlywheelBuilder* withMotor(pros::Motor* motor);

        /**
         * Adds a PID controller to the builder data
         * @param pid The PID controller being added
         * @return The buider for build chaining
         */
        FlywheelBuilder* withPID(PID* pid);

        /**
         * Adds the diameter of the flywheel to the builder data
         * @param wheelSize The diameter of the wheel being added
         * @return The builder for build chaining
         */
        FlywheelBuilder* withWheelSize(double wheelSize);

        /**
         * Adds a number of encoder counts per revolution to the builder data
         * @param countsPerRevolution The encoder counts per flywheel revolution being added
         * @return The builder for build chaining
         */
        FlywheelBuilder* withCountsPerRevolution(double countsPerRevolution);

        /**
         * Builds the Flywheel using the stored data
         * @return The new Flywheel
         */
        Flywheel* build();
    };

    /**
     * Default constructor for Flywheel
     */
    Flywheel();

    /**
     * Builder constructor for Flywheel
     * @param builder The builder being used for construction
     */
    Flywheel(FlywheelBuilder* builder);

    /**
     * Default destructor for Flywheel
     */
    ~Flywheel();

    /**
     * Initializes the flywheel
     */
    void initialize();

    /**
     * Updates the state of the flywheel
     */
    void update();

    /**
     * Sets the flywheel motors to a specific power level
     * @param power The power level being set
     */
    void setFlywheel(double power);

    /**
     * Sets the RPM of the flywheel
     * @param RPM The value to set the RPM to
     */
    void setRPM(double RPM);

    /**
     * Gets the RPM of the flywheel
     */
    double getRPM();

    /**
     * Gets the target RPM of the flywheel
     */
    double getTargetRPM();

    /**
     * Sets the linear velocity of the flywheel
     */
    void setVelocity(double velocity);

    /**
     * Gets the linear velocity of the flywheel
     */
    double getVelocity();
};

#endif