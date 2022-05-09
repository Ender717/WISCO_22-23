// Standard inclusion guard
#ifndef PID_HPP
#define PID_HPP

// Included libraries
#include <cfloat>
#include "./main.h"

/**
 * This class manages a PID controller
 */
class PID
{
private:
    /**
     * The number of milliseconds in a second
     */
    static constexpr int MILLISECONDS_PER_SECOND = 1000;

    /**
     * The control constants for the PID controller
     */
    double* kp;
    double* ki;
    double* kd;

    /**
     * The limiting values of the PID controller
     */
    double* min;
    double* max;

    /**
     * The limiting value of the Integral component of the controller
     */
    double* integralLimit;

    /**
     * The previous system clock time
     */
    double* pastTime;

    /**
     * The target value of the controller
     */
    double* targetValue;

    /**
     * The error to target value of the previous control loop
     */
    double* pastError;

    /**
     * The stored value of the integral controller
     */
    double* iValue;

public:
    /**
     * The builder class for PID controllers
     */
    class PIDBuilder
    {
    public:    
        /**
         * All attributes being used for the builder
         */
        double* kp;
        double* ki;
        double* kd;
        double* min;
        double* max;
        double* integralLimit;
        double* startTarget;

        /**
         * Default constructor for PIDBuilder
         */
        PIDBuilder();

        /**
         * Default destructor for PIDBuilder
         */
        ~PIDBuilder();

        /**
         * Adds a kp constant to the PIDBuilder
         * @param kp The kp constant being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithKp(double kp);

        /**
         * Adds a ki constant to the PIDBuilder
         * @param ki The ki constant being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithKi(double ki);

        /**
         * Adds a kd constant to the PIDBuilder
         * @param kd The kd constant being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithKd(double kd);

        /**
         * Adds a minimum control value to the PIDBuilder
         * @param min The minimum being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithMin(double min);

        /**
         * Adds a maximum control value to the PIDBuilder
         * @param max The maximum being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithMax(double max);

        /**
         * Adds a maximum integral controller value to the PIDBuilder
         * @param integralLimit The limiter being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithIntegralLimit(double integralLimit);

        /**
         * Adds a starting target value to the PIDBuilder
         * @param startTarget The initial target being added
         * @return The builder for build chaining
         */
        PIDBuilder* WithStartTarget(double startTarget);

        /**
         * Builds the PID controller using the PIDBuilder's stored data
         * @return The new PID controller
         */
        PID* Build();
    };

    /**
     * Builder constructor for PID
     * @param builder The builder being used for construction
     */
    PID(PIDBuilder* builder);

    /**
     * Default destructor for PID
     */
    ~PID();

    /**
     * Gets the control value from the controller
     * @param currentValue The current value of the system being controlled
     * @return The control value for the system
     */
    double GetControlValue(double currentValue);

    /**
     * Sets the target of the controller
     * @param targetValue The new target for the system
     */
    void SetTargetValue(double targetValue);
};

#endif