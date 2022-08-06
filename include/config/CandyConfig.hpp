// Inclusion guard
#ifndef CANDY_CONFIG_HPP
#define CANDY_CONFIG_HPP

// Included libraries
#include "./main.h"

/**
 * This namespace manages the configuration of the candy robot
 */
namespace CandyConfig
{
    /**
     * The number of encoder counts for the catapult per cycle
     */
    extern const double CATAPULT_COUNTS_PER_CYCLE;

    /**
     * The position of the catapult when loaded
     */
    extern const double CATAPULT_LOADED_POSITION;
    
    /**
     * The ports for the left drive motors
     */
    extern const int LEFT_DRIVE_1_PORT;
    extern const int LEFT_DRIVE_2_PORT;

    /**
     * The ports for the right drive motors
     */
    extern const int RIGHT_DRIVE_1_PORT;
    extern const int RIGHT_DRIVE_2_PORT;

    /**
     * The ports for the catapult motors
     */
    extern const int CATAPULT_1_PORT;
}

#endif