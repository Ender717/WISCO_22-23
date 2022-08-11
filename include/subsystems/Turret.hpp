// Inclusion guard
#ifndef TURRET_HPP
#define TURRET_HPP

// Included libraries
#include <list>
#include <cfloat>
#include <cmath>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class defines a turret subsystem for the robot
 * @author Nathan Sandvig
 */
class Turret
{
private:
    /**
     * The list of motors being used for the turret
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The PID controller for the turret
     */
    PID* turretPID;

    /**
     * The starting angle of the turret
     */
    double startAngle;

    /**
     * The counts per degree of rotation for the turret
     */
    double countsPerDegree;

    /**
     * The minimum position of the turret
     */
    double minPosition;

    /**
     * The maximum position of the turret
     */
    double maxPosition;

    /**
     * The target angle of the turret
     */
    double targetAngle;

public:
    /**
     * Builder class for Turret
     */
    class TurretBuilder
    {
    public:
        /**
         * Builder attributes
         */
        std::list<pros::Motor*>* motorList;
        PID* turretPID;
        double* startAngle;
        double* countsPerDegree;
        double* minAngle;
        double* maxAngle;

        /**
         * Default constructor for TurretBuilder
         */
        TurretBuilder();

        /**
         * Default destructor for TurretBuilder
         */
        ~TurretBuilder();

        /**
         * Wither method to add a motor to the build
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        TurretBuilder* withMotor(pros::Motor* motor);

        /**
         * Wither method to add a PID controller to the build
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        TurretBuilder* withPID(PID* pid);

        /**
         * Wither method to add a starting angle to the build
         * @param startAngle The starting angle being added
         * @return The builder for build chaining
         */
        TurretBuilder* withStartAngle(double startAngle);

        /**
         * Wither method to add a number of encoder counts per degree to the build
         * @param countsPerDegree The number of encoder counts per degree being added
         * @return The builder for build chaining
         */
        TurretBuilder* withCountsPerDegree(double countsPerDegree);

        /**
         * Wither method to add a minimum angle to the build
         * @param minAngle The minimum angle being added
         * @return The builder for build chaining
         */
        TurretBuilder* withMinAngle(double minAngle);

        /**
         * Wither method to add a maximum angle to the build
         * @param maxAngle The maximum angle being added
         * @return The builder for build chaining
         */
        TurretBuilder* withMaxAngle(double maxAngle);

        /**
         * Build method for the builder
         * @return The new turret which was built
         */
        Turret* build();
    };

    /**
     * Default constructor for Turret
     */
    Turret();

    /**
     * Builder constructor for Turret
     */
    Turret(TurretBuilder* builder);
    
    /**
     * Default destructor for Turret
     */
    ~Turret();

    /**
     * Initializes the turret
     */
    void initialize();

    /**
     * Updates the turret
     */
    void update();

    /**
     * Sets the motors on the turret the specified value
     * @param power The power to set the motors to
     */
    void setTurret(double power);

    /**
     * Gets the current position of the turret
     * @return The current position of the turret
     */
    double getPosition();

    /**
     * Sets the angle of the turret
     * @param angle The angle being set
     */
    void setAngle(double angle);

    /**
     * Gets the angle of the turret
     * @return The current angle of the turret
     */
    double getAngle();

    /**
     * Gets the target angle of the turret
     * @return The target angle of the turret
     */
    double getTargetAngle();
};

#endif