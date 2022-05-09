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
     * The motors on the intake
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The PID controller for the intake
     */
    PID* intakePID;

    /**
     * The speed of the intake
     */
    double* intakeSpeed;

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
        IntakeBuilder* WithMotor(pros::Motor* motor);

        /**
         * Add a PID controller to the build
         * @param pid The PID controller being added
         * @return The builder for build chaining
         */
        IntakeBuilder* WithPID(PID* pid);

        /**
         * Builds the intake using the stored data
         * @return The new intake
         */
        Intake* Build();
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
    void Initialize();

    /**
     * Sets the speed of the intake
     * @param speed The new speed of the intake
     */
    void SetSpeed(double speed);

    /**
     * Sucks the intake inward
     */
    void Suck();

    /**
     * Blows the intake outward
     */
    void Blow();

    /**
     * Stops the intake
     */
    void Stop();
};

#endif