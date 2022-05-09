#include "autonomous/autons.hpp"
#include "autonomous/AutonController.hpp"

namespace Autons
{
    // Constants
    const int NUM_AUTONS = 8;

    // Variables
    int selectedAuton;

    // Functions
    void ProgrammingSkillsBlue()
    {

    }

    void ProgrammingSkillsOrange()
    {

    }

    void LeftAutonBlue()
    {
        AutonController::DoLeftStartTaskBlue();
        AutonController::DoDistanceTask(5.5, 6.0, 110.0, true, false, false);
        AutonController::DoTurnTask(96.0, 110.0, true, true, false);
        pros::delay(100);
    }

    void MiddleAutonBlue()
    {
        AutonController::DoMiddleStartTaskBlue();
    }

    void RightAutonBlue()
    {
        AutonController::DoRightStartTaskBlue();
        pros::delay(100);
        AutonController::DoDistanceTask(10.0, 0.0, 110.0, true, false, false);
        pros::delay(100);
        AutonController::DoTurnTask(90.0, 110.0, true, true, false);
        pros::delay(100);
        AutonController::DoThroughDistanceTask(-15.0, 75.0, 40.0, 110.0, true, true, false);
        pros::delay(100);
        AutonController::DoDistanceTask(5.0, 90.0, 110.0, true, false, false);
        pros::delay(100);
        AutonController::DoTurnTask(180.0, 110.0, true, true, false);
        pros::delay(100);
        AutonController::DoThroughDistanceTask(-10.0, 180.0, 40.0, 110.0, true, true, false);
        AutonController::DoThroughDistanceTask(-2.0, 180.0, 40.0, 110.0, true, false, false);
        AutonController::DoDistanceTask(10.0, 180.0, 110.0, true, false, true);
        pros::delay(1000);
        for (int i = 0; i < 2; i++)
        {
            AutonController::DoThroughDistanceTask(10.0, 180.0, 40.0, 110.0, true, false, true);
            AutonController::DoThroughDistanceTask(-10.0, 180.0, 40.0, 110.0, true, false, true);
        }
        pros::delay(100);
        AutonController::DoThroughDistanceTask(15.0, 180.0, 40.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoDistanceTask(-10.0, 180.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoTurnTask(270.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoThroughDistanceTask(15.0, 180.0, 40.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoDistanceTask(-17.0, 270.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoTurnTask(360.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoDistanceTask(16.0, 360.0, 110.0, true, false, true);
        pros::delay(100);
        AutonController::DoThroughDistanceTask(15.0, 360.0, 30.0, 110.0, true, false, true);;
        pros::delay(100);
        AutonController::DoDistanceTask(-30.0, 0.0, 110.0, true, false, true);
    }

    void LeftAutonOrange()
    {
        //AutonController::robot->drive->SetPosition(-54.5, -36.0, 0.0);
        //pros::Task positionTask(PositionTask);

        AutonController::DoLeftStartTaskOrange();
        AutonController::DoDistanceTask(5.5, 6.0, 110.0, true, false, false);
        AutonController::DoTurnTask(96.0, 110.0, true, true, false);
        pros::delay(100);

        //positionTask.remove();
    }

    void MiddleAutonOrange()
    {
        AutonController::DoMiddleStartTaskOrange();
    }

    void RightAutonOrange()
    {
        AutonController::DoRightStartTaskOrange();
        AutonController::DoDistanceTask(33.5, 0.0, 110.0, true, false, false);
        AutonController::DoTurnTask(75.0, 110.0, true, true, false);
        AutonController::DoDistanceTask(-9.5, 75.0, 110.0, true, true, false);
        pros::delay(100);
        AutonController::DoTurnTask(180.0, 110.0, true, false, false);
    }
}