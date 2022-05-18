#include "processes/Database.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

// Constructor definitions ----------------------------------------------------
Database::Database()
{
    readerCount = 0;
    isWriting = false;
}

// Public method definitions --------------------------------------------------
void Database::startReading()
{
    if (isWriting || !writerList.empty())
    {
        pros::Task thisTask = pros::Task::current();
        readerList.push_back(thisTask);
        thisTask.suspend();
    }
    readerCount++;
}

void Database::stopReading()
{
    readerCount--;
    if (readerCount == 0 && !writerList.empty())
        writerList.front().resume();
}

void Database::startWriting()
{
    if (readerCount > 0 || isWriting)
    {
        pros::Task thisTask = pros::Task::current();
        writerList.push_back(thisTask);
        thisTask.suspend();
    }
    isWriting = true;
}

void Database::stopWriting()
{
    isWriting = false;
    if (!writerList.empty())
        writerList.front().resume();
    else if (!readerList.empty())
        for (std::list<pros::Task>::iterator iterator = readerList.begin(); 
        iterator != readerList.end(); iterator++)
        iterator->resume();
}