// Inclusion guard
#ifndef CARRIER_HPP
#define CARRIER_HPP

// Included libraries
#include <list>
#include <cfloat>
#include "./processes/PID.hpp"
#include "./main.h"


/**
 * This class manages a carrier subsystem
 */
class Carrier
{
private:
    /**
     * The motors on the carrier
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The pistons on the carrier
     */
    std::list<pros::ADIDigitalOut*>* pistonList;

    /**
     * The PID controller for the carrier
     */
    PID* carrierPID;

    /**
     * The starting position of the carrier
     */
    double* startAngle;
    double* startHeight;

    /**
     * How many encoder counts translate to real-world movements
     */
    double* countsPerDegree;
    double* countsPerInch;

    /**
     * The length of the carrier arm
     */
    double* armLength;

    /**
     * The bounding positions of the carrier
     */
    double* minPosition;
    double* maxPosition;

    /**
     * The preset up and down positions of the carrier
     */
    double* downPosition;
    double* upPosition;

    /**
     * Whether the carrier is currently down or not
     */
    bool* isDown;

    /**
     * Converts an angle to an encoder position
     * @param angle The angle being converted
     */
    double AngleToPosition(double angle);

    /**
     * Converts a height to an encoder position
     * @param height The height being converted
     */
    double HeightToPosition(double height);

public:
    /**
     * Builder class for Carriers
     */
    class CarrierBuilder
    {
    public:
        /**
         * The data being used to build the carrier
         */
        std::list<pros::Motor*>* motorList;
        std::list<pros::ADIDigitalOut*>* pistonList;
        PID* carrierPID;
        double* startAngle;
        double* minAngle;
        double* maxAngle;
        double* startHeight;
        double* minHeight;
        double* maxHeight;
        double* countsPerDegree;
        double* countsPerInch;
        double* armLength;
        double* downPosition;
        double* upPosition;

        /**
         * Default constructor for CarrierBuilder
         */
        CarrierBuilder();

        /**
         * Default destructor for CarrierBuilder
         */
        ~CarrierBuilder();

        /**
         * Adds a motor to the builder data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithMotor(pros::Motor* motor);

        /**
         * Adds a piston to the builder data
         * @param piston The piston being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithPiston(pros::ADIDigitalOut* piston);

        /**
         * Adds a PID controller to the builder data
         * @param PID The PID controller being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithPID(PID* pid);

        /**
         * Adds an initial angle to the builder data
         * @param startAngle The initial angle being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithStartAngle(double startAngle);

        /**
         * Adds a minimum angle to the builder data
         * @param minAngle The minimum angle being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithMinAngle(double minAngle);

        /**
         * Adds a maximum angle to the builder data
         * @param maxAngle The maximum angle being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithMaxAngle(double maxAngle);

        /**
         * Adds an initial height to the builder data
         * @param startHeight The initial height being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithStartHeight(double startHeight);

        /**
         * Adds a minimum height to the builder data
         * @param minHeight The minimum height being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithMinHeight(double minHeight);

        /**
         * Adds a maximum height to the builder data
         * @param maxHeight The maximum height being added
         * @return The builder for build chaining
         */
        CarrierBuilder* WithMaxHeight(double maxHeight);

        /**
         * Adds the number of counts per degree of movement to the build data
         * @param countsPerDegree The number of encoder counts per degree
         * @return The builder for build chaining
         */
        CarrierBuilder* WithCountsPerDegree(double countsPerDegree);

        /**
         * Adds the number of counts per inch of movement to the build data
         * @param countsPerInch The number of encoder counts per inch
         * @return The builder for build chaining
         */
        CarrierBuilder* WithCountsPerInch(double countsPerInch);

        /**
         * Adds the length of the arm of the carrier to the build data
         * @param armLength The length of the arm
         * @return The builder for build chaining
         */
        CarrierBuilder* WithArmLength(double armLength);

        /**
         * Adds the position when the carrier is down to the build data
         * @param downPosition The position of the carrier when it is down
         * @return The builder for build chaining
         */
        CarrierBuilder* WithDownPosition(double downPosition);

        /**
         * Adds the position when the carrier is up to the build data
         * @param upPosition The position of the carrier when it is up
         * @return The builder for build chaining
         */
        CarrierBuilder* WithUpPosition(double upPosition);

        /**
         * Builds a carrier using the stored build data
         * @return The new carrier
         */
        Carrier* Build();
    };

    /**
     * Builder constructor for Carrier
     * @param builder The builder being used for construction
     */
    Carrier(CarrierBuilder* builder);

    /**
     * Default destructor for Carrier
     */
    ~Carrier();

    /**
     * Initializes the carrier
     */
    void Initialize();

    /**
     * Sets the motors on the carrier to a specific power level
     * @param power The power level to set the motors to
     */
    void SetCarrier(double power);

    /**
     * Lowers the carrier
     */
    void Lower();

    /**
     * Raises the carrier
     */
    void Raise();

    /**
     * Holds the carrier in its current position
     */
    void HoldPosition();

    /**
     * Gets the current position of the carrier
     * @return The current position of the carrier
     */
    double GetPosition();

    /**
     * Sets the target angle of the carrier
     * @param targetAngle The new target angle
     */
    void SetAngle(double targetAngle);

    /**
     * Sets the target height of the carrier
     * @param targetHeight The new target height
     */
    void SetHeight(double targetHeight);

    /**
     * Gets the current angle of the carrier
     * @return The current angle of the carrier
     */
    double GetAngle();

    /**
     * Gets the current height of the carrier
     * @return The current height of the carrier
     */
    double GetHeight();

    /**
     * Sets the carrier to the down position
     */
    void SetDown();

    /**
     * Sets the carrier to the up position
     */
    void SetUp();

    /**
     * Toggles the position of the carrier between up and down
     */
    void TogglePosition();

    /**
     * Checks if the carrier is at the bottom of its range of motion
     * @return True if the carrier is at the bottom, false if not
     */
    bool AtBottom();

    /**
     * Checks if the carrier is at the top of its range of motion
     * @return True if the carrier is at the top, false if not
     */
    bool AtTop();
};

#endif