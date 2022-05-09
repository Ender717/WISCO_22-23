// Inclusion Guard
#ifndef POSITION_HPP
#define POSITION_HPP

// Included libraries
#include "./main.h"

/**
 * This class manages an odometric position calculation system
 */
class Position
{
private:
    /**
     * The distance from each tracking wheel to the center of the robot
     */
    double* leftTrackingDistance;
    double* rightTrackingDistance;
    double* strafeTrackingDistance;

    /**
     * The current position of the robot
     */
    double* currentX;
    double* currentY;
    double* currentTheta;

    /**
     * The sensor values during the previous process loop
     */
    double* lastLeft;
    double* lastRight;
    double* lastStrafe;
    double* lastTheta;

    /**
     * The most recent reset position
     */
    double* resetX;
    double* resetY;
    double* resetTheta;

    /**
     * Sets a new reset position
     */
    void SetResetPosition();

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
        double* leftTrackingDistance;
        double* rightTrackingDistance;
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
         * Adds the distance from the left tracking wheel to the center of the
         * robot to the builder
         * @param leftTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionBuilder* WithLeftDistance(double leftTrackingDistance);

        /**
         * Adds the distance from the right tracking wheel to the center of the
         * robot to the builder
         * @param rightTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionBuilder* WithRightDistance(double rightTrackingDistance);

        /**
         * Adds the distance from the strafe tracking wheel to the center of the
         * robot to the builder
         * @param strafeTrackingDistance The distance between the wheel and center
         * @return The builder for build chaining
         */
        PositionBuilder* WithStrafeDistance(double strafeTrackingDistance);

        /**
         * Adds a starting x-coordinate to the builder
         * @param startX The x-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* WithStartX(double startX);

        /**
         * Adds a starting y-coordinate to the builder
         * @param startY The y-coordinate to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* WithStartY(double startY);

        /**
         * Adds a starting angle to the builder
         * @param startAngle The angle to initialize the position to
         * @return The builder for build chaining
         */
        PositionBuilder* WithStartAngle(double startAngle);

        /**
         * Builds a Position object using the stored data
         * @return the new Position object
         */
        Position* Build();
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
     * @param leftValue The current left tracking wheel position
     * @param rightValue The current right tracking wheel position
     * @param strafeValue The current strafe tracking wheel position
     * @param thetaValue The current theta of the system
     * *Credit to 5225A - The E-Bots Pilons
     */
    void UpdatePosition(double leftValue, double rightValue, double strafeValue, double thetaValue);

    /**
     * Sets the x-coordinate of the system
     * @param x The new x-coordinate
     */
    void SetX(double x);

    /**
     * Sets the y-coordinate of the system
     * @param y The new y-coordinate
     */
    void SetY(double y);

    /**
     * Sets the angle of the system
     * @param angle The new angle
     */
    void SetAngle(double angle);

    /**
     * Sets the position of the system
     * @param x The new x-coordinate
     * @param y The new y-coordinate
     * @param theta The new theta
     */
    void SetPosition(double x, double y, double theta);

    /**
     * Gets the current x-coordinate of the system
     * @return The current x-coordinate
     */
    double GetX() const;

    /**
     * Gets the current y-coordinate of the system
     * @return The current y-coordinate
     */
    double GetY() const;

    /**
     * Gets the current theta of the system
     * @return The current theta
     */
    double GetTheta() const;

    /**
     * Gets the current angle of the system
     * @return The current angle
     */
    double GetAngle() const;
};

#endif
