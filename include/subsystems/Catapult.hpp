// Inclusion guard
#ifndef CATAPULT_HPP
#define CATAPULT_HPP

// Included libraries
#include <list>
#include <cfloat>
#include <cmath>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class manages a Catapult subsystem
 */
class Catapult
{
private:
    /**
     * The default number of counts per cycle for a catapult
     * 1800 counts per rotation on a 100rpm cartridge + 1:5 torque ratio
     */
    const double DEFAULT_COUNTS_PER_CYCLE = 9000.0;

    /**
     * The default loaded position for a catapult
     */
    const double DEFAULT_LOADED_POSITION = 0.0;

    /**
     * The allowed error margin for loading
     */
    const double LOAD_ERROR_MARGIN = 50.0;

    /**
     * The motors on the catapult
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The PID controller for the catapult
     */
    PID* catapultPID;

    /**
     * The current position of the catapult
     */
    double currentPosition;

    /**
     * The number of encoder counts per launch cycle
     */
    double countsPerCycle;

    /**
     * The position of the catapult when it is loaded
     */
    double loadedPosition;

public:
    /**
     * Builder class for Catapult
     */
    class CatapultBuilder
    {
    public:
        /**
         * The data being used to build the Catapult
         */
        std::list<pros::Motor*>* motorList;
        PID* catapultPID;
        double* countsPerCycle;
        double* loadedPosition;

        /**
         * Default constructor for CatapultBuilder
         */
        CatapultBuilder();

        /**
         * Default destructor for CatapultBuilder
         */
        ~CatapultBuilder();

        /**
         * Adds a motor to the builder data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        CatapultBuilder* withMotor(pros::Motor* motor);

        /**
         * Adds a PID controller to the builder data
         * @param pid The PID controller being added
         * @return The buider for build chaining
         */
        CatapultBuilder* withPID(PID* pid);

        /**
         * Adds a number of encoder counts per cycle for the catapult to the builder data
         * @param countsPerCycle The number of counts per cycle being added
         * @return The builder for build chaining
         */
        CatapultBuilder* withCountsPerCycle(double countsPerCycle);

        /**
         * Adds a loaded position for the catapult to the builder data
         * @param loadedPosition The loaded position being added
         * @return The builder for build chaining
         */
        CatapultBuilder* withLoadedPosition(double loadedPosition);

        /**
         * Builds the Catapult using the stored data
         * @return The new Catapult
         */
        Catapult* build();
    };

    /**
     * Builder constructor for Catapult
     * @param builder The builder being used for construction
     */
    Catapult(CatapultBuilder* builder);

    /**
     * Default destructor for Catapult
     */
    ~Catapult();

    /**
     * Initializes the catapult
     */
    void initialize();

    /**
     * Sets the motors on the catapult to the designated power level
     * @param power The power level the motors are being set to
     */
    void setCatapult(double power);

    /**
     * Loads the catapult
     */
    void load();

    /**
     * Holds the current position of the catapult
     */
    void holdPosition();

    /**
     * Gets the current position of the catapult
     * @return The current position of the catapult
     */
    double getPosition();

    /**
     * Checks if the catapult is currently loaded or not
     * @return True if the catapult is loaded, false if not
     */
    bool isLoaded();
};

#endif