// Included libraries
#include "robot/RobotManager.hpp"
#include "config/TestConfig.hpp"
#include "pros/motors.h"

// Constructor definitions -----------------------------------------------------
RobotManager::RobotManager()
{
    robot = nullptr;
}

// Destructor definitions ------------------------------------------------------
RobotManager::~RobotManager()
{
    robot = nullptr;
}

// Private method definitions --------------------------------------------------
void RobotManager::createMatchBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createMatchOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createSkillsBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createSkillsOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

void RobotManager::createTestRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }

    // Create the PID controllers
    PID::PIDBuilder* pidBuilder = new PID::PIDBuilder();
    PID* drivePID = pidBuilder->withKp(1.0)->withKi(0.0)->withKd(0.0)->build();
    PID* flywheelPID = pidBuilder->withKp(0.05)->withKi(0.08)->withKd(0.01)->withIntegralLimit(130.0)->withMin(0.0)->withMax(127.0)->build();
    PID* turretPID = pidBuilder->withKp(0.14)->withKi(0.02)->withKd(0.002)->withMin(-127.0)->withMax(127.0)->build();

    // Create the position system
    PositionSystem::PositionSystemBuilder* positionSystemBuilder = new PositionSystem::PositionSystemBuilder();
    PositionSystem* positionSystem = positionSystemBuilder->
        withWheelSize(TestConfig::DRIVE_TRACKING_WHEEL_SIZE)->
        withLinearSensor(new pros::Rotation(TestConfig::LINEAR_DRIVE_TRACKING_PORT))->
        withLinearTrackingMultiplier(TestConfig::DRIVE_LINEAR_TRACKING_MULTIPLIER)->
        withLinearDistance(TestConfig::DRIVE_LINEAR_TRACKING_DISTANCE)->
        withStrafeSensor(new pros::Rotation(TestConfig::STRAFE_DRIVE_TRACKING_PORT))->
        withStrafeTrackingMultiplier(TestConfig::DRIVE_STRAFE_TRACKING_MULTIPLIER)->
        withStrafeDistance(TestConfig::DRIVE_STRAFE_TRACKING_DISTANCE)->
        withInertialSensor(new pros::Imu(TestConfig::DRIVE_INERTIAL_PORT))->
        withInertialMultiplier(TestConfig::DRIVE_INERTIAL_MULTIPLIER)->
        build();
    delete positionSystemBuilder;
    positionSystemBuilder = nullptr;

    // Create the holo drive
    HoloDrive::HoloDriveBuilder* holoDriveBuilder = new HoloDrive::HoloDriveBuilder();
    HoloDrive* holoDrive = holoDriveBuilder->
        withLeftFrontMotor(new pros::Motor(TestConfig::LEFT_FRONT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withLeftRearMotor(new pros::Motor(TestConfig::LEFT_REAR_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withRightFrontMotor(new pros::Motor(TestConfig::RIGHT_FRONT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS))->
        withRightRearMotor(new pros::Motor(TestConfig::RIGHT_REAR_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS))->
        build();
    delete holoDriveBuilder;
    holoDriveBuilder = nullptr;

    // Create the flywheel
    Flywheel::FlywheelBuilder* flywheelBuilder = new Flywheel::FlywheelBuilder();
    Flywheel* flywheel = flywheelBuilder->
        withMotor(new pros::Motor(TestConfig::FLYWHEEL_1_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withPID(flywheelPID)->
        withWheelSize(TestConfig::FLYWHEEL_WHEEL_SIZE)->
        withCountsPerRevolution(TestConfig::FLYWHEEL_COUNTS_PER_REVOLUTION)->
        withMaxRPM(TestConfig::FLYWHEEL_MAX_RPM)->
        build();
    delete flywheelBuilder;
    flywheelBuilder = nullptr;

    // Create the turret
    Turret::TurretBuilder* turretBuilder = new Turret::TurretBuilder();
    Turret* turret = turretBuilder->
        withMotor(new pros::Motor(TestConfig::TURRET_1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS))->
        withPID(turretPID)->
        withStartAngle(TestConfig::TURRET_START_ANGLE)->
        withCountsPerDegree(TestConfig::TURRET_COUNTS_PER_DEGREE)->
        withMinAngle(TestConfig::TURRET_MIN_ANGLE)->
        withMaxAngle(TestConfig::TURRET_MAX_ANGLE)->
        build();
    delete turretBuilder;
    turretBuilder = nullptr;

    // Create the robot
    Robot::RobotBuilder* robotBuilder = new Robot::RobotBuilder();
    robot = robotBuilder->
        withPositionSystem(positionSystem)->
        withHoloDrive(holoDrive)->
        withFlywheel(flywheel)->
        withTurret(turret)->
        build();
    delete robotBuilder;
    robotBuilder = nullptr;
}

void RobotManager::createCandyRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }

    // Create the tank drive
    TankDrive::TankDriveBuilder* tankDriveBuilder = new TankDrive::TankDriveBuilder();
    TankDrive *tankDrive =
        tankDriveBuilder
            ->withLeftMotor(new pros::Motor(CandyConfig::LEFT_DRIVE_1_PORT,
                                            pros::E_MOTOR_GEARSET_06, false,
                                            pros::E_MOTOR_ENCODER_COUNTS))
            ->withLeftMotor(new pros::Motor(CandyConfig::LEFT_DRIVE_2_PORT,
                                            pros::E_MOTOR_GEARSET_06, false,
                                            pros::E_MOTOR_ENCODER_COUNTS))
            ->withLeftMotor(new pros::Motor(CandyConfig::LEFT_DRIVE_3_PORT,
                                            pros::E_MOTOR_GEARSET_06, false,
                                            pros::E_MOTOR_ENCODER_COUNTS))
            ->withRightMotor(new pros::Motor(CandyConfig::RIGHT_DRIVE_1_PORT,
                                             pros::E_MOTOR_GEARSET_06, true,
                                             pros::E_MOTOR_ENCODER_COUNTS))
            ->withRightMotor(new pros::Motor(CandyConfig::RIGHT_DRIVE_2_PORT,
                                             pros::E_MOTOR_GEARSET_06, true,
                                             pros::E_MOTOR_ENCODER_COUNTS))
            ->withRightMotor(new pros::Motor(CandyConfig::RIGHT_DRIVE_3_PORT,
                                             pros::E_MOTOR_GEARSET_06, true,
                                             pros::E_MOTOR_ENCODER_COUNTS))
            ->build();
    delete tankDriveBuilder;
    tankDriveBuilder = nullptr;

    // Create the robot
    Robot::RobotBuilder* robotBuilder = new Robot::RobotBuilder();
    robot = robotBuilder->
        withTankDrive(tankDrive)->
        build();
    delete robotBuilder;
    robotBuilder = nullptr;
}

// Public method definitions --------------------------------------------------
void RobotManager::createRobot(Menu::Configurations config)
{
    switch (config)
    {
        case Menu::Configurations::MATCH_BLUE:
            createMatchBlueRobot();
            break;
        case Menu::Configurations::MATCH_ORANGE:
            createMatchOrangeRobot();
            break;
        case Menu::Configurations::SKILLS_BLUE:
            createSkillsBlueRobot();
            break;
        case Menu::Configurations::SKILLS_ORANGE:
            createSkillsOrangeRobot();
            break;
        case Menu::Configurations::TEST:
            createTestRobot();
            break;
        case Menu::Configurations::CANDY:
            createCandyRobot();
            break;
    }
}

Robot* RobotManager::getRobot()
{
    return robot;
}