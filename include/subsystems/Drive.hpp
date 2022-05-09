// Inclusion guard
#ifndef DRIVE_HPP
#define DRIVE_HPP

// Included libraries
#include <list>
#include "./processes/PID.hpp"
#include "./processes/Position.hpp"
#include "./main.h"
    
/**
 * This class manages a Drive subsystem
 */
class Drive
{
private:
    
    /**
     * The motors on the left side of the drive
     */
    std::list<pros::Motor*>* leftMotorList;

    /**
     * The motors on the right side of the drive
     */
    std::list<pros::Motor*>* rightMotorList;

    /**
     * The tracking sensors on the drive
     */
    pros::Rotation* leftTrackingSensor;
    pros::Rotation* rightTrackingSensor;
    pros::Rotation* strafeTrackingSensor;

    /**
     * The inertial sensor on the drive
     */
    pros::Imu* inertialSensor;

    /**
     * The PID controllers
     */
    PID* distancePID;
    PID* anglePID;
    PID* turnPID;

    /**
     * The position tracking system
     */
    Position* position;

    /**
     * The size of the tracking wheels
     */
    double* wheelSize;

public:
    /**
     * Builder class for Drive
     */
    class DriveBuilder
    {
    public:
        /**
         * Data being used for Drive construction
         */
        std::list<pros::Motor*>* leftMotorList;
        std::list<pros::Motor*>* rightMotorList;
        pros::Rotation* leftTrackingSensor;
        pros::Rotation* rightTrackingSensor;
        pros::Rotation* strafeTrackingSensor;
        pros::Imu* inertialSensor;
        PID* distancePID;
        PID* anglePID;
        PID* turnPID;
        Position* position;
        double* wheelSize;

        /**
         * Default constructor for DriveBuilder
         */
        DriveBuilder();

        /**
         * Default destructor for DriveBuilder
         */
        ~DriveBuilder();

        /**
         * Add a left drive motor the build data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithLeftMotor(pros::Motor* motor);

        /**
         * Add a right drive motor the build data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithRightMotor(pros::Motor* motor);

        /**
         * Add a left tracking sensor to the build data
         * @param sensor The tracking sensor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithLeftTrackingSensor(pros::Rotation* sensor);

        /**
         * Add a right tracking sensor to the build data
         * @param sensor The tracking sensor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithRightTrackingSensor(pros::Rotation* sensor);

        /**
         * Add a strafe tracking sensor to the build data
         * @param sensor The tracking sensor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithStrafeTrackingSensor(pros::Rotation* sensor);

        /**
         * Add an inertial sensor to the build data
         * @param sensor The inertial sensor being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithInertialSensor(pros::Imu* sensor);

        /**
         * Add a PID controller for distance to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithDistancePID(PID* pid);

        /**
         * Add a PID controller for angle to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithAnglePID(PID* pid);

        /**
         * Add a PID controller for turning to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithTurnPID(PID* pid);

        /**
         * Add a position calculation system to the build data
         * @param position The position calculation system being added
         * @return The builder for build chaining
         */
        DriveBuilder* WithPosition(Position* position);

        /**
         * Add the size of the tracking wheels to the build data
         * @param wheelSize The size of the wheels
         * @return The builder for build chaining
         */
        DriveBuilder* WithWheelSize(double wheelSize);

        /**
         * Builds the drive using the stored build data
         * @return The new drive
         */
        Drive* Build();
    };

    /**
     * Builder constructor for Drive
     * @param builder The builder being used for construction
     */
    Drive(DriveBuilder* builder);

    /**
     * Default destructor for Drive
     */
    ~Drive();

    /**
     * Initializes the drive
     */
    void Initialize();

    /**
     * Sets the motors on the drive to the specified power levels
     * @param leftPower The power to set for the left side of the drive
     * @param rightpower The power to set for the right side of the drive
     */
    void SetDrive(double leftPower, double rightPower);

    /**
     * Drives straight forward the specified distance at the specified angle
     * @param distance The distance to drive forward
     * @param angle The angle to maintain while driving
     */
    void DriveStraight(double distance, double angle);

    /**
     * Drives straight through the specified distance
     * @param distance The distance to drive through
     * @param angle The angle to maintain while driving
     * @param power The power to set the motors to by default
     */
    void DriveStraightThrough(double distance, double angle, double power);

    /**
     * Turn to the specified angle
     * @param targetAngle The angle to turn to
     */
    void TurnToAngle(double targetAngle);

    /**
     * Sets the x-coordinate of the internal position tracking system
     * @param x The x-coordinate being set
     */
    void SetX(double x);

    /**
     * Sets the y-coordinate of the internal position tracking system
     * @param y The y-coordinate being set
     */
    void SetY(double y);

    /**
     * Sets the theta of the internal position tracking system
     * @param theta The theta being set
     */
    void SetTheta(double theta);

    /**
     * Sets the position of the internal position tracking system
     * @param x The x-coordinate being set
     * @param y The y-coordinate being set
     * @param theta The theta being set
     */
    void SetPosition(double x, double y, double theta);

    /**
     * Gets the x-coordinate from the internal position tracking system
     * @return The x-coordinate of the position tracking system
     */
    double GetX() const;

    /**
     * Gets the y-coordinate from the internal position tracking system
     * @return The y-coordinate of the position tracking system
     */
    double GetY() const;

    /**
     * Gets the theta from the internal position tracking system
     * @return The theta of the position tracking system
     */
    double GetTheta() const;

    /**
     * Updates the internal position tracking system
     */
    void UpdatePosition();
};

#endif