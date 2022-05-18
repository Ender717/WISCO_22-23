// Standard inclusion guard
#ifndef DATABASE_HPP
#define DATABASE_HPP

// Included libraries
#include <list>
#include "./main.h"

/**
 * This class is used to manage access to any system which follows the classical database problem
 */
class Database
{
private:
    /**
     * The list of tasks waiting to read data from the database
     */
    std::list<pros::Task> readerList;

    /**
     * The list of tasks waiting to write data to the database
     */
    std::list<pros::Task> writerList;

    /**
     * The number of processes reading data
     */
    int readerCount;

    /**
     * Whether or not a process is writing data
     */
    bool isWriting;

public:
    /**
     * Default constructor for the database class
     */
    Database();

    /**
     * Starts a reader task
     */
    void startReading();

    /**
     * Stops a reader task
     */
    void stopReading();

    /**
     * Starts a writer task
     */
    void startWriting();

    /**
     * Stops a writer task
     */
    void stopWriting();
};

#endif