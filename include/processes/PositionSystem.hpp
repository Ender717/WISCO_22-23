// Inclusion Guard
#ifndef POSITION_SYSTEM_HPP
#define POSITION_SYSTEM_HPP

// Included libraries
#include "Database.hpp"
#include "Position.hpp"
#include "./main.h"

/**
 * This class manages an odometric position calculation system
 */
class PositionSystem
{
private:
    /**
     * Constants involved with position tracking
     */
    static constexpr double WHEEL_SIZE = 2.75;
    static constexpr double COUNTS_PER_ROTATION = 36000.0;
    static constexpr double PI = 3.1415;

    /**
     * The database system manager for this system
     */
    Database database;

    /**
     * The sensors involved with the position tracking system
     */
    pros::Rotation* linearTrackingSensor;
    pros::Rotation* strafeTrackingSensor;
    pros::Imu* inertialSensor;

    /**
     * The distance from each tracking wheel to the center of the robot
     */
    double linearTrackingDistance;
    double strafeTrackingDistance;

    /**
     * The current position of the robot
     */
    double currentX;
    double currentY;
    double currentTheta;

    /**
     * The current velocity of the robot
     */
    double xVelocity;
    double yVelocity;
    double thetaVelocity;

    /**
     * The sensor values during the previous process loop
     */
    double lastLinear;
    double lastStrafe;
    double lastTheta;

    /**
     * The most recent reset position
     */
    double resetX;
    double resetY;
    double resetTheta;

    /**
     * Converts tracking wheel counts to inches
     */
    double countsToInches(double counts);

    /**
     * Sets a new reset position
     */
    void setResetPosition();

public:
    /**
     * Builder class for the position calculator
     */
    class PositionSystemBuilder
    {
    public:
        /**
         * All attributes being used by the builder
         */
        pros::Rotation* linearTrackingSensor;
        pros::Rotation* strafeTrackingSensor;
        pros::Imu* inertialSensor;
        double* linearTrackingDistance;
        double* strafeTrackingDistance;
        double* startX;
        double* startY;
        double* startTheta;

        /**
         * Default constructor for PositionBuilder
         */
        PositionSystemBuilder();

        /**
         * Default destructor for PositionBuilder
         */
        ~PositionSystemBuilder();

        /**
         * Adds a linear tracking wheel encoder to the build
         * @param linearTrackingSensor The linear tracking wheel encoder
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withLinearSensor(pros::Rotation* linearTrackingSensor);

        /**
         * Adds a strafe tracking wheel encoder to the build
         * @param strafeTrackingSensor The strafe tracking wheel encoder
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withStrafeSensor(pros::Rotation* strafeTrackingSensor);

        /**
         * Adds an inertial sensor to the build
         * @param inertialSensor The inertial sensor
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withInertialSensor(pros::Imu* inertialSensor);

        /**
         * Adds the distance from the linear tracking wheel to the center of the
         * robot to the builder
         * @param linearTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withLinearDistance(double linearTrackingDistance);

        /**
         * Adds the distance from the strafe tracking wheel to the center of the
         * robot to the builder
         * @param strafeTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withStrafeDistance(double strafeTrackingDistance);

        /**
         * Adds a starting x-coordinate to the builder
         * @param startX The x-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withStartX(double startX);

        /**
         * Adds a starting y-coordinate to the builder
         * @param startY The y-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withStartY(double startY);

        /**
         * Adds a starting angle to the builder
         * @param startAngle The angle to initialize the position to
         * @return The builder for build chaining
         */
        PositionSystemBuilder* withStartAngle(double startAngle);

        /**
         * Builds a PositionSystem object using the stored data
         * @return the new Position object
         */
        PositionSystem* build();
    };

    /**
     * Builder constructor for PositionSystem
     * @param builder The builder being used for construction
     */
    PositionSystem(PositionSystemBuilder* builder);

    /**
     * Default destructor for PositionSystem
     */
    ~PositionSystem();

    /**
     * Initialize the position tracking system
     */
    void initialize();

    /**
     * Updates the position of the system
     */
    void updatePosition();

    /**
     * Sets the position of the system
     * @param x The new x-coordinate
     * @param y The new y-coordinate
     * @param theta The new theta
     */
    void setPosition(double x, double y, double theta);

    /**
     * Gets the current position of the system
     * @return The current position
     */
    Position* getPosition();
};

#endif
