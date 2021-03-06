// Inclusion guard
#ifndef LIFT_HPP
#define LIFT_HPP

// Included libraries
#include <list>
#include <cfloat>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class manages a Lift subsystem
 */
class Lift
{
private:
    /**
     * The motors on the left side of the lift
     */
    std::list<pros::Motor*> leftMotorList;

    /**
     * The motors on the right side of the lift
     */
    std::list<pros::Motor*> rightMotorList;

    /**
     * The PID controller for the lift
     */
    PID* liftPID;

    /**
     * The starting position of the lift
     */
    double startAngle;
    double startHeight;

    /**
     * The multiplier to measurable position from encoder counts
     */
    double countsPerDegree;
    double countsPerInch;

    /**
     * The length of the lift arm
     */
    double armLength;

    /**
     * The bounds of the lift position
     */
    double minPosition;
    double maxPosition;

    /**
     * Converts an angle to a position in encoder counts
     * @param angle The angle being converted
     * @return The position equivalent
     */
    double angleToPosition(double angle);

    /**
     * Converts a height to a position in encoder counts
     * @param height The height being converted
     * @return The position equivalent
     */
    double heightToPosition(double height);

public:
    /**
     * Builder class for Lift
     */
    class LiftBuilder
    {
    public:
        /**
         * The data being used for construction
         */
        std::list<pros::Motor*>* leftMotorList;
        std::list<pros::Motor*>* rightMotorList;
        PID* liftPID;
        double* startAngle;
        double* minAngle;
        double* maxAngle;
        double* startHeight;
        double* minHeight;
        double* maxHeight;
        double* countsPerDegree;
        double* countsPerInch;
        double* armLength;

        /**
         * Default constructor for LiftBuilder
         */
        LiftBuilder();

        /**
         * Default destructor for LiftBuilder
         */
        ~LiftBuilder();

        /**
         * Adds a left motor to the build
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        LiftBuilder* withLeftMotor(pros::Motor* motor);

        /**
         * Adds a right motor to the build
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        LiftBuilder* withRightMotor(pros::Motor* motor);

        /**
         * Adds a PID controller to the build
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        LiftBuilder* withPID(PID* pid);

        /**
         * Adds a starting angle to the build
         * @param startAngle The initial angle of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withStartAngle(double startAngle);

        /**
         * Adds a minimum angle to the build
         * @param minAngle The minimum angle of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withMinAngle(double minAngle);

        /**
         * Adds a maximum angle to the build
         * @param maxAngle The maximum angle of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withMaxAngle(double maxAngle);

        /**
         * Adds a starting height to the build
         * @param startHeight The initial height of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withStartHeight(double startHeight);

        /**
         * Adds a minimum height to the build
         * @param minHeight The minimum height of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withMinHeight(double minHeight);

        /**
         * Adds a maximum height to the build
         * @param maxHeight The maximum height of the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withMaxHeight(double maxHeight);

        /**
         * Adds a conversion multiplier from counts to degrees to the build
         * @param countsPerDegree The number of encoder counts per degrees of motion
         * @return The builder for build chaining
         */
        LiftBuilder* withCountsPerDegree(double countsPerDegree);

        /**
         * Adds a conversion multiplier from counts to inches to the build
         * @param countsPerDegree The number of encoder counts per inches of motion
         * @return The builder for build chaining
         */
        LiftBuilder* withCountsPerInch(double countsPerInch);

        /**
         * Adds an arm length to the build
         * @param armLength The length of the arm on the lift
         * @return The builder for build chaining
         */
        LiftBuilder* withArmLength(double armLength);

        /**
         * Builds a lift using the stored data
         * @return The new lift
         */
        Lift* build();
    };

    /**
     * Builder constructor for Lift
     * @param builder The builder being used for construction
     */
    Lift(LiftBuilder* builder);

    /**
     * Default destructor for Lift
     */
    ~Lift();

    /**
     * Initializes the lift
     */
    void initialize();

    /**
     * Sets the lift motors to a specified power level
     * @param power The power level to set the motors to
     */
    void setLift(double power);

    /**
     * Raises the lift
     */
    void raise();

    /**
     * Lowers the lift
     */
    void lower();

    /**
     * Stops the lift
     */
    void stop();

    /**
     * Holds the lift at its current position
     */
    void holdPosition();

    /**
     * Gets the current position of the lift
     * @return The current position of the lift
     */
    double getPosition();

    /**
     * Sets a target angle for the lift
     * @param targetAngle The target angle being set
     */
    void setAngle(double targetAngle);

    /**
     * Sets a target height for the lift
     * @param targetHeight The target height being set
     */
    void setHeight(double targetHeight);

    /**
     * Gets the current angle of the lift
     * @return The current angle of the lift
     */
    double getAngle();

    /**
     * Gets the current height of the lift
     * @return The current height of the lift
     */
    double getHeight();

    /**
     * Checks if the lift is currently at the bottom
     * @return True if the lift is at the bottom, false if not
     */
    bool atBottom();

    /**
     * Checks if the lift is currently at the top
     * @return True if the lift is at the top, false if not
     */
    bool atTop();
};

#endif