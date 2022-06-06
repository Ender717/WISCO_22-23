// Inclusion guard
#ifndef DRIVE_HPP
#define DRIVE_HPP

// Included libraries
#include <list>
#include "./processes/PID.hpp"
#include "./main.h"
    
/**
 * This class manages a TankDrive subsystem
 */
class TankDrive
{
private:
    /**
     * The motors on the left side of the drive
     */
    std::list<pros::Motor*> leftMotorList;

    /**
     * The motors on the right side of the drive
     */
    std::list<pros::Motor*> rightMotorList;

    /**
     * The PID controllers
     */
    PID* distancePID;
    PID* anglePID;
    PID* turnPID;

public:
    /**
     * Builder class for TankDrive
     */
    class TankDriveBuilder
    {
    public:
        /**
         * Data being used for TankDrive
         * construction
         */
        std::list<pros::Motor*>* leftMotorList;
        std::list<pros::Motor*>* rightMotorList;
        PID* distancePID;
        PID* anglePID;
        PID* turnPID;

        /**
         * Default constructor for TankDriveBuilder
         */
        TankDriveBuilder();

        /**
         * Default destructor for TankDriveBuilder
         */
        ~TankDriveBuilder();

        /**
         * Add a left drive motor the build data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        TankDriveBuilder* withLeftMotor(pros::Motor* motor);

        /**
         * Add a right drive motor the build data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        TankDriveBuilder* withRightMotor(pros::Motor* motor);

        /**
         * Add a PID controller for distance to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        TankDriveBuilder* withDistancePID(PID* pid);

        /**
         * Add a PID controller for angle to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        TankDriveBuilder* withAnglePID(PID* pid);

        /**
         * Add a PID controller for turning to the build data
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        TankDriveBuilder* withTurnPID(PID* pid);

        /**
         * Builds the drive using the stored build data
         * @return The new drive
         */
        TankDrive* build();
    };

    /**
     * Builder constructor for TankDrive
     * @param builder The builder being used for construction
     */
    TankDrive(TankDriveBuilder* builder);

    /**
     * Default destructor for TankDrive
     */
    ~TankDrive();

    /**
     * Initializes the drive
     */
    void initialize();

    /**
     * Sets the motors on the drive to the specified power levels
     * @param leftPower The power to set for the left side of the drive
     * @param rightpower The power to set for the right side of the drive
     */
    void setDrive(double leftPower, double rightPower);

    /**
     * Go to the target position
     * @param x The target x-coordinate
     * @param y The target y-coordinate
     * @param theta The target angle
     */
    void goToPosition(double x, double y, double theta);

    /**
     * Turn to the specified angle
     * @param targetAngle The angle to turn to
     */
    void turnToAngle(double targetAngle);
};

#endif