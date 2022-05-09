// Inclusion guard
#ifndef CLAW_HPP
#define CLAW_HPP

// Included libraries
#include <list>
#include <cfloat>
#include "./processes/PID.hpp"
#include "./main.h"

/**
 * This class manages a Claw subsystem
 */
class Claw
{
private:
    /**
     * The motors on the claw
     */
    std::list<pros::Motor*>* motorList;

    /**
     * The pistons on the claw
     */
    std::list<pros::ADIDigitalOut*>* pistonList;

    /**
     * The PID controller for the claw
     */
    PID* clawPID;

    /**
     * The bounding positions of the claw
     */
    double* minPosition;
    double* maxPosition;

    /**
     * The position of the claw when it is open
     */
    double* openPosition;

    /**
     * The position of the claw when it is closed
     */
    double* closedPosition;

    /**
     * Whether the claw is open or not
     */
    bool* isOpen;

public:
    /**
     * Builder class for Claw
     */
    class ClawBuilder
    {
    public:
        /**
         * The data being used to build the Claw
         */
        std::list<pros::Motor*>* motorList;
        std::list<pros::ADIDigitalOut*>* pistonList;
        PID* clawPID;
        double* minPosition;
        double* maxPosition;
        double* openPosition;
        double* closedPosition;

        /**
         * Default constructor for ClawBuilder
         */
        ClawBuilder();

        /**
         * Default destructor for ClawBuilder
         */
        ~ClawBuilder();

        /**
         * Adds a motor to the builder data
         * @param motor The motor being added
         * @return The builder for build chaining
         */
        ClawBuilder* WithMotor(pros::Motor* motor);

        /**
         * Adds a piston to the builder data
         * @param piston The piston being added
         * @return The builder for build chaining
         */
        ClawBuilder* WithPiston(pros::ADIDigitalOut* piston);

        /**
         * Adds a PID controller to the builder data
         * @param pid The PID controller being added
         * @return The buider for build chaining
         */
        ClawBuilder* WithPID(PID* pid);

        /**
         * Adds a minimum position for the claw to the builder data
         * @param minPosition The minimum position being added
         * @return The builder for build chaining
         */
        ClawBuilder* WithMinPosition(double minPosition);

        /**
         * Adds a maximum position for the claw to the builder data
         * @param maxPosition The maximum position being added
         * @return The builder for build chaining
         */
        ClawBuilder* WithMaxPosition(double maxPosition);

        /**
         * Adds the position of the claw when it is open to the builder data
         * @param openPosition The position of the claw when it is open
         * @return The builder for build chaining
         */
        ClawBuilder* WithOpenPosition(double openPosition);

        /**
         * Adds the position of the claw when it is closed to the builder data
         * @param closedPosition The position of the claw when it is closed
         * @return The builder for build chaining
         */
        ClawBuilder* WithClosedPosition(double closedPosition);

        /**
         * Builds the Claw using the stored data
         * @return The new Claw
         */
        Claw* Build();
    };

    /**
     * Builder constructor for Claw
     * @param builder The builder being used for construction
     */
    Claw(ClawBuilder* builder);

    /**
     * Default destructor for Claw
     */
    ~Claw();

    /**
     * Initializes the claw
     */
    void Initialize();

    /**
     * Sets the motors on the claw to the designated power level
     * @param power The power level the motors are being set to
     */
    void SetClaw(double power);

    /**
     * Opens the claw
     */
    void Open();

    /**
     * Closes the claw
     */
    void Close();

    /**
     * Holds the current position of the claw
     */
    void HoldPosition();

    /**
     * Gets the current position of the claw
     * @return The current position of the claw
     */
    double GetPosition();

    /**
     * Sets the claw to the open position
     */
    void SetOpen();

    /**
     * Sets the claw to the closed position
     */
    void SetClosed();

    /**
     * Toggles the position of the claw between open and closed
     */
    void TogglePosition();

    /**
     * Checks if the claw is currently open or not
     * @return True if the claw is open, false if not
     */
    bool IsOpened();

    /**
     * Checks if the claw is currently closed or not
     * @return True if the claw is closed, false if not
     */
    bool IsClosed();
};

#endif