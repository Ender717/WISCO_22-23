// Inclusion guard
#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

// Included libraries
#include "./main.h"
#include <vector>

/**
 * @brief This class manages tasks for the V5 system
 *
 * @author Nathan Sandvig
 */
class TaskManager
{
private:
    /**
     * @brief The list of tasks stored in the manager
     */
    static std::vector<pros::Task> taskList;

public:
    /**
     * @brief Adds a task to the list of tasks
     *
     * @param task
     */
    static void addTask(pros::Task task);

    static void removeTask(std::string taskName);

    static void clearTasks();
};

#endif