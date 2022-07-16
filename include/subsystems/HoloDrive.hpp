// Standard inclusion guard
#ifndef HOLO_DRIVE_HPP
#define HOLO_DRIVE_HPP

// Included libraries
#include <list>
#include "./main.h"

/**
 * This class manages a holonomic drive subsystem
 */
class HoloDrive
{
private:
    /**
     * The motors on the left front wheel of the drive
     */
    std::list<pros::Motor*> leftFrontMotorList;

    /**
     * The motors on the left rear wheel of the drive
     */
    std::list<pros::Motor*> leftRearMotorList;

    /**
     * The motors on the right front wheel of the drive
     */
    std::list<pros::Motor*> rightFrontMotorList;

    /**
     * The motors on the right rear wheel of the drive
     */
    std::list<pros::Motor*> rightRearMotorList;

public:
    /**
     * Builder class for HoloDrive
     */
    class HoloDriveBuilder
    {
    public:
        /**
         * Data being used for HoloDrive construction
         */
        std::list<pros::Motor*>* leftFrontMotorList;
        std::list<pros::Motor*>* leftRearMotorList;
        std::list<pros::Motor*>* rightFrontMotorList;
        std::list<pros::Motor*>* rightRearMotorList;

        /**
         * Default constructor for HoloDriveBuilder
         */
        HoloDriveBuilder();

        /**
         * Default destructor for HoloDriveBuilder
         */
        ~HoloDriveBuilder();

        /**
         * Wither method to add a motor to the left front wheel
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        HoloDriveBuilder* withLeftFrontMotor(pros::Motor motor);

        /**
         * Wither method to add a motor to the left rear wheel
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        HoloDriveBuilder* withLeftRearMotor(pros::Motor motor);

        /**
         * Wither method to add a motor to the right front wheel
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        HoloDriveBuilder* withRightFrontMotor(pros::Motor motor);

        /**
         * Wither method to add a motor to the right rear wheel
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        HoloDriveBuilder* withRightRearMotor(pros::Motor motor);
        
        /**
         * Build method to create the HoloDrive
         */
        HoloDrive* build();
    };

    /**
     * Builder constructor for HoloDrive
     */
    HoloDrive(HoloDriveBuilder* builder);

    /**
     * Default destructor for HoloDrive
     */
    ~HoloDrive();

    /**
     * Initializes the holonomic drive
     */
    void initialize();

    /**
     * Sets the motors on the drive to the specified power levels
     * @param leftFrontPower The power to set for the left front wheel of the drive
     * @param leftRearPower The power to set for the left rear wheel of the drive
     * @param rightFrontPower The power to set for the right front wheel of the drive
     * @param rightRearPower The power to set for the right rear wheel of the drive
     */
    void setDrive(double leftFrontPower, double leftRearPower, 
        double rightFrontPower, double rightRearPower);

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