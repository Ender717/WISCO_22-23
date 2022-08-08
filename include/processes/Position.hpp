// Standard inclusion guard
#ifndef POSITION_HPP
#define POSITION_HPP

/**
 * This class holds a position snapshot from the positioning system
 */
class Position
{
private:
    /**
     * The x-coordinate in the snapshot
     */
    double x;

    /**
     * The y-coordinate in the snapshot
     */
    double y;

    /**
     * The theta in the snapshot
     */
    double theta;

    /**
     * The x-velocity in the snapshot
     */
    double xVelocity;

    /**
     * The y-velocity in the snapshot
     */
    double yVelocity;

    /**
     * The angular theta-velocity in the snapshot
     */
    double thetaVelocity;

public:
    /**
     * Builder class for position class
     */
    class PositionBuilder
    {
    public:
        /**
         * Attributes to build with
         */
        double* x;
        double* y;
        double* theta;
        double* xVelocity;
        double* yVelocity;
        double* thetaVelocity;

        /**
         * Default constructor for the position builder
         */
        PositionBuilder();

        /**
         * Default destructor for the position builder
         */
        ~PositionBuilder();

        /**
         * Wither method to add an x-coordinate to the build
         * @param x The x-coordinate being added
         * @return The builder for build chaining
         */
        PositionBuilder* withX(double x);

        /**
         * Wither method to add an y-coordinate to the build
         * @param y The y-coordinate being added
         * @return The builder for build chaining
         */
        PositionBuilder* withY(double y);

        /**
         * Wither method to add a theta to the build
         * @param theta The theta being added
         * @return The builder for build chaining
         */
        PositionBuilder* withTheta(double theta);

        /**
         * Wither method to add an x-velocity to the build
         * @param xVelocity The x-velocity being added
         * @return The builder for build chaining
         */
        PositionBuilder* withXVelocity(double xVelocity);

        /**
         * Wither method to add an y-velocity to the build
         * @param yVelocity The y-velocity being added
         * @return The builder for build chaining
         */
        PositionBuilder* withYVelocity(double yVelocity);

        /**
         * Wither method to add a theta-velocity to the build
         * @param thetaVelocity The theta-velocity being added
         * @return The builder for build chaining
         */
        PositionBuilder* withThetaVelocity(double thetaVelocity);

        /**
         * Build method for the position builder
         * @return The position object which was built
         */
        Position* build();
    };

    /**
     * Default constructor for variable creation
     */
    Position();

    /**
     * Builder constructor for the Position class
     */
    Position(PositionBuilder* builder);

    /**
     * Gets the x-coordinate stored in the position
     * @return The x-coordinate
     */
    double getX();

    /**
     * Gets the y-coordinate stored in the position
     * @return The y-coordinate
     */
    double getY();

    /**
     * Gets the theta stored in the position
     * @return The theta
     */
    double getTheta();

    /**
     * Gets the x-velocity stored in the position
     * @return The x-velocity
     */
    double getXVelocity();

    /**
     * Gets the y-velocity stored in the position
     * @return The y-velocity
     */
    double getYVelocity();

    /**
     * Gets the theta-velocity stored in the position
     * @return The theta-velocity
     */
    double getThetaVelocity();
};

#endif