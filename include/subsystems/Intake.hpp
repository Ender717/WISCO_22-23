// Inclusion guard
#ifndef INTAKE_HPP
#define INTAKE_HPP

// Included libraries
#include <list>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class manages an Intake subsystem
 */
class Intake
{
private:
    /**
     * The default intake speed
     */
    static constexpr double DEFAULT_SPEED = 127.0;

    /**
     * The motors on the intake
     */
    std::list<pros::Motor*> motorList;

    /**
     * The PID controller for the intake
     */
    PID* intakePID;

    /**
     * The speed of the intake
     */
    double speed;

public:
    /**
     * Builder class for Intake
     */
    class IntakeBuilder
    {
    public:
        /**
         * Data being used for construction
         */
        std::list<pros::Motor*>* motorList;
        PID* intakePID;
        double* speed;

        /**
         * Default constructor for IntakeBuilder
         */
        IntakeBuilder();

        /**
         * Default destructor for IntakeBuilder
         */
        ~IntakeBuilder();

        /**
         * Add a motor to the build
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        IntakeBuilder* withMotor(pros::Motor* motor);

        /**
         * Add a PID controller to the build
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        IntakeBuilder* withPID(PID* pid);

        /**
         * Add an intake speed to the build
         * @param speed The intake speed being added
         * @return The builder for build chaining
         */
        IntakeBuilder* withSpeed(double speed);

        /**
         * Builds the intake using the stored data
         * @return The new intake
         */
        Intake* build();
    };

    /**
     * Builder constructor for Intake
     * @param builder The builder being used for construction
     */
    Intake(IntakeBuilder* builder);

    /**
     * Default destructor for Intake
     */
    ~Intake();
    
    /**
     * Initializes the intake
     */
    void initialize();

    /**
     * Sets the intake to a specified power
     * @param power The power to set the intake to
     */
    void setIntake(double power);

    /**
     * Sets the speed of the intake
     * @param speed The new speed of the intake
     */
    void setSpeed(double speed);

    /**
     * Sucks the intake inward
     */
    void suck();

    /**
     * Blows the intake outward
     */
    void blow();

    /**
     * Stops the intake
     */
    void stop();
};

#endif