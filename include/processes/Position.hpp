// Inclusion Guard
#ifndef POSITION_HPP
#define POSITION_HPP

// Included libraries
#include "./main.h"
#include "pros/rotation.hpp"

/**
 * This class manages an odometric position calculation system
 */
class Position
{
private:
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
     * Sets a new reset position
     */
    void setResetPosition();

public:
    /**
     * Builder class for the position calculator
     */
    class PositionBuilder
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
        PositionBuilder();

        /**
         * Default destructor for PositionBuilder
         */
        ~PositionBuilder();

        /**
         * Adds a linear tracking wheel encoder to the build
         * @param linearTrackingSensor The linear tracking wheel encoder
         * @return The builder for build chaining
         */
        PositionBuilder* withLinearSensor(pros::Rotation* linearTrackingSensor);

        /**
         * Adds a strafe tracking wheel encoder to the build
         * @param strafeTrackingSensor The strafe tracking wheel encoder
         * @return The builder for build chaining
         */
        PositionBuilder* withStrafeSensor(pros::Rotation* strafeTrackingSensor);

        /**
         * Adds an inertial sensor to the build
         * @param inertialSensor The inertial sensor
         * @return The builder for build chaining
         */
        PositionBuilder* withInertialSensor(pros::Imu* inertialSensor);

        /**
         * Adds the distance from the linear tracking wheel to the center of the
         * robot to the builder
         * @param linearTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionBuilder* withLinearDistance(double linearTrackingDistance);

        /**
         * Adds the distance from the strafe tracking wheel to the center of the
         * robot to the builder
         * @param strafeTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionBuilder* withStrafeDistance(double strafeTrackingDistance);

        /**
         * Adds a starting x-coordinate to the builder
         * @param startX The x-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* withStartX(double startX);

        /**
         * Adds a starting y-coordinate to the builder
         * @param startY The y-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* withStartY(double startY);

        /**
         * Adds a starting angle to the builder
         * @param startAngle The angle to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* withStartAngle(double startAngle);

        /**
         * Builds a Position object using the stored data
         * @return the new Position object
         */
        Position* build();
    };

    /**
     * Builder constructor for Position
     * @param builder The builder being used for construction
     */
    Position(PositionBuilder* builder);

    /**
     * Default destructor for Position
     */
    ~Position();

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
     * Gets the current x-coordinate of the system
     * @return The current x-coordinate
     */
    double getPositionX() const;

    /**
     * Gets the current y-coordinate of the system
     * @return The current y-coordinate
     */
    double getPositionY() const;

    /**
     * Gets the current theta of the system
     * @return The current theta
     */
    double getPositionTheta() const;

    /**
     * Gets the current x-velocity of the system
     * @return the current x-velocity
     */
    double getVelocityX() const;

    /**
     * Gets the current y-velocity of the system
     * @return the current y-velocity
     */
    double getVelocityY() const;
    
    /**
     * Gets the current theta-velocity of the system
     * @return the current theta-velocity
     */
    double getVelocityTheta() const;
};

#endif
