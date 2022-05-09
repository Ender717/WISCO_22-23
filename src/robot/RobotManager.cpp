// Included libraries
#include "robot/RobotManager.hpp"

// Constructor definitions -----------------------------------------------------
RobotManager::RobotManager()
{
    robot = nullptr;
}

// Destructor definitions ------------------------------------------------------
RobotManager::~RobotManager()
{
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }
}

// Private method definitions --------------------------------------------------
void RobotManager::CreateBlueRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }

    // Create the PID controllers
    PID::PIDBuilder* pidBuilder = new PID::PIDBuilder();
	PID* clawPID = pidBuilder->WithKp(2.3)->WithKi(0.05)->WithKd(0.05)->WithIntegralLimit(65.0)->Build();
	PID* distancePID = pidBuilder->WithKp(10.3)->WithKi(0.0)->WithKd(1.3)->WithMax(80.0)->Build();
    PID* anglePID = pidBuilder->WithKp(3.9)->WithKi(0.0)->WithKd(0.0)->Build();
    PID* turnPID = pidBuilder->WithKp(9.5)->WithKi(0.0)->WithKd(0.5)->Build();
	PID* liftPID = pidBuilder->WithKp(13.5)->WithKi(0.1)->WithKd(1.31)->WithIntegralLimit(90.0)->WithStartTarget(140.0)->Build();
	delete pidBuilder;
	pidBuilder = nullptr;
	
    // Create the position tracking
	Position::PositionBuilder* positionBuilder = new Position::PositionBuilder();
	Position* position = positionBuilder->WithLeftDistance(BlueConfig::DRIVE_LEFT_TRACKING_DISTANCE)->
		WithRightDistance(BlueConfig::DRIVE_RIGHT_TRACKING_DISTANCE)->
		WithStrafeDistance(BlueConfig::DRIVE_STRAFE_TRACKING_DISTANCE)->
		Build();
	delete positionBuilder;
	positionBuilder = nullptr;

    // Create the carrier
	Carrier::CarrierBuilder* carrierBuilder = new Carrier::CarrierBuilder();
	Carrier* carrier = carrierBuilder->WithPiston(new pros::ADIDigitalOut(BlueConfig::CARRIER_1_PORT))->
		Build();
	delete carrierBuilder;
	carrierBuilder = nullptr;

    // Create the claw
	Claw::ClawBuilder* clawBuilder = new Claw::ClawBuilder();
	Claw* claw = clawBuilder->WithPiston(new pros::ADIDigitalOut(BlueConfig::CLAW_1_PORT))->
		Build();
	delete clawBuilder;
	clawBuilder = nullptr;

    // Create the drive
	Drive::DriveBuilder* driveBuilder = new Drive::DriveBuilder();
	Drive* drive = driveBuilder->WithLeftMotor(new pros::Motor(BlueConfig::LEFT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
		WithLeftMotor(new pros::Motor(BlueConfig::LEFT_DRIVE_2_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(BlueConfig::LEFT_DRIVE_3_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(BlueConfig::LEFT_DRIVE_4_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_DRIVE_2_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_DRIVE_3_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_DRIVE_4_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithLeftTrackingSensor(new pros::Rotation(BlueConfig::LEFT_DRIVE_TRACKING_PORT))->
        WithRightTrackingSensor(new pros::Rotation(BlueConfig::RIGHT_DRIVE_TRACKING_PORT))->
        WithStrafeTrackingSensor(new pros::Rotation(BlueConfig::STRAFE_DRIVE_TRACKING_PORT))->
        WithInertialSensor(new pros::Imu(BlueConfig::INERTIAL_PORT))->
        WithDistancePID(distancePID)->
        WithAnglePID(anglePID)->
        WithTurnPID(turnPID)->
        WithPosition(position)->
        WithWheelSize(BlueConfig::DRIVE_TRACKING_WHEEL_SIZE)->
        Build();
	delete driveBuilder;
	driveBuilder = nullptr;

    // Create the intake
	Intake::IntakeBuilder* intakeBuilder = new Intake::IntakeBuilder();
	Intake* intake = intakeBuilder->WithMotor(new pros::Motor(BlueConfig::INTAKE_1_PORT, E_MOTOR_GEARSET_06, true, 
            E_MOTOR_ENCODER_COUNTS))->
        Build();
	delete intakeBuilder;
	intakeBuilder = nullptr;

    // Create the lift
	Lift::LiftBuilder* liftBuilder = new Lift::LiftBuilder();
	Lift* lift = liftBuilder->WithLeftMotor(new pros::Motor(BlueConfig::LEFT_LIFT_1_PORT, pros::E_MOTOR_GEARSET_36, true, 
            E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(BlueConfig::LEFT_LIFT_2_PORT, pros::E_MOTOR_GEARSET_36, false, 
            E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_LIFT_1_PORT, pros::E_MOTOR_GEARSET_36, false, 
            E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(BlueConfig::RIGHT_LIFT_2_PORT, pros::E_MOTOR_GEARSET_36, true, 
            E_MOTOR_ENCODER_COUNTS))->
        WithPID(liftPID)->
        WithStartAngle(BlueConfig::LIFT_START_POSITION)->
        WithMinAngle(BlueConfig::LIFT_BOTTOM_POSITION)->
        WithMaxAngle(BlueConfig::LIFT_TOP_POSITION)->
        WithCountsPerDegree(BlueConfig::LIFT_COUNTS_PER_DEGREE)->
        Build();
	delete liftBuilder;
	liftBuilder = nullptr;

    // Create the robot
    Robot::RobotBuilder* robotBuilder = new Robot::RobotBuilder();
    robot = robotBuilder->WithConfiguration(new RobotConfigs(RobotConfigs::BLUE))->
        WithCarrier(carrier)->
        WithClaw(claw)->
        WithDrive(drive)->
        WithIntake(intake)->
        WithLift(lift)->
        Build();
    delete robotBuilder;
    robotBuilder = nullptr;

    // Reset the pointers
    carrier = nullptr;
    claw = nullptr;
    drive = nullptr;
    intake = nullptr;
    lift = nullptr;
}

void RobotManager::CreateOrangeRobot()
{
    // Reset the robot
    if (robot != nullptr)
    {
        delete robot;
        robot = nullptr;
    }

    // Create the PID controllers
    PID::PIDBuilder* pidBuilder = new PID::PIDBuilder();
	PID* clawPID = pidBuilder->WithKp(2.3)->WithKi(0.05)->WithKd(0.05)->WithIntegralLimit(65.0)->Build();
	PID* distancePID = pidBuilder->WithKp(10.3)->WithKi(0.0)->WithKd(1.3)->WithMax(80.0)->Build();
    PID* anglePID = pidBuilder->WithKp(3.9)->WithKi(0.0)->WithKd(0.0)->Build();
    PID* turnPID = pidBuilder->WithKp(9.5)->WithKi(0.0)->WithKd(0.5)->Build();
	PID* liftPID = pidBuilder->WithKp(13.3)->WithKi(0.1)->WithKd(1.32)->WithIntegralLimit(90.0)->WithStartTarget(140.0)->Build();
	delete pidBuilder;
	pidBuilder = nullptr;
	
    // Create the position tracking
	Position::PositionBuilder* positionBuilder = new Position::PositionBuilder();
	Position* position = positionBuilder->WithLeftDistance(OrangeConfig::DRIVE_LEFT_TRACKING_DISTANCE)->
		WithRightDistance(OrangeConfig::DRIVE_RIGHT_TRACKING_DISTANCE)->
		WithStrafeDistance(OrangeConfig::DRIVE_STRAFE_TRACKING_DISTANCE)->
		Build();
	delete positionBuilder;
	positionBuilder = nullptr;

    // Create the carrier
	Carrier::CarrierBuilder* carrierBuilder = new Carrier::CarrierBuilder();
	Carrier* carrier = carrierBuilder->WithPiston(new pros::ADIDigitalOut(OrangeConfig::CARRIER_1_PORT))->
		Build();
	delete carrierBuilder;
	carrierBuilder = nullptr;

    // Create the claw
	Claw::ClawBuilder* clawBuilder = new Claw::ClawBuilder();
	Claw* claw = clawBuilder->WithPiston(new pros::ADIDigitalOut(OrangeConfig::CLAW_1_PORT))->
		Build();
	delete clawBuilder;
	clawBuilder = nullptr;

    // Create the drive
	Drive::DriveBuilder* driveBuilder = new Drive::DriveBuilder();
	Drive* drive = driveBuilder->WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
		WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_DRIVE_2_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_DRIVE_3_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_DRIVE_4_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_DRIVE_1_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_DRIVE_2_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_DRIVE_3_PORT, pros::E_MOTOR_GEARSET_06, 
            true, E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_DRIVE_4_PORT, pros::E_MOTOR_GEARSET_06, 
            false, E_MOTOR_ENCODER_COUNTS))->
        WithLeftTrackingSensor(new pros::Rotation(OrangeConfig::LEFT_DRIVE_TRACKING_PORT))->
        WithRightTrackingSensor(new pros::Rotation(OrangeConfig::RIGHT_DRIVE_TRACKING_PORT))->
        WithStrafeTrackingSensor(new pros::Rotation(OrangeConfig::STRAFE_DRIVE_TRACKING_PORT))->
        WithInertialSensor(new pros::Imu(OrangeConfig::INERTIAL_PORT))->
        WithDistancePID(distancePID)->
        WithAnglePID(anglePID)->
        WithTurnPID(turnPID)->
        WithPosition(position)->
        WithWheelSize(OrangeConfig::DRIVE_TRACKING_WHEEL_SIZE)->
        Build();
	delete driveBuilder;
	driveBuilder = nullptr;

    // Create the intake
	Intake::IntakeBuilder* intakeBuilder = new Intake::IntakeBuilder();
	Intake* intake = intakeBuilder->WithMotor(new pros::Motor(OrangeConfig::INTAKE_1_PORT, E_MOTOR_GEARSET_06, true, 
            E_MOTOR_ENCODER_COUNTS))->
        Build();
	delete intakeBuilder;
	intakeBuilder = nullptr;

    // Create the lift
	Lift::LiftBuilder* liftBuilder = new Lift::LiftBuilder();
	Lift* lift = liftBuilder->WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_LIFT_1_PORT, pros::E_MOTOR_GEARSET_36, true, 
            E_MOTOR_ENCODER_COUNTS))->
        WithLeftMotor(new pros::Motor(OrangeConfig::LEFT_LIFT_2_PORT, pros::E_MOTOR_GEARSET_36, false, 
            E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_LIFT_1_PORT, pros::E_MOTOR_GEARSET_36, false, 
            E_MOTOR_ENCODER_COUNTS))->
        WithRightMotor(new pros::Motor(OrangeConfig::RIGHT_LIFT_2_PORT, pros::E_MOTOR_GEARSET_36, true, 
            E_MOTOR_ENCODER_COUNTS))->
        WithPID(liftPID)->
        WithStartAngle(OrangeConfig::LIFT_START_POSITION)->
        WithMinAngle(OrangeConfig::LIFT_BOTTOM_POSITION)->
        WithMaxAngle(OrangeConfig::LIFT_TOP_POSITION)->
        WithCountsPerDegree(OrangeConfig::LIFT_COUNTS_PER_DEGREE)->
        Build();
	delete liftBuilder;
	liftBuilder = nullptr;

    // Create the robot
    Robot::RobotBuilder* robotBuilder = new Robot::RobotBuilder();
    robot = robotBuilder->WithConfiguration(new RobotConfigs(RobotConfigs::ORANGE))->
        WithCarrier(carrier)->
        WithClaw(claw)->
        WithDrive(drive)->
        WithIntake(intake)->
        WithLift(lift)->
        Build();
    delete robotBuilder;
    robotBuilder = nullptr;

    // Reset the pointers
    carrier = nullptr;
    claw = nullptr;
    drive = nullptr;
    intake = nullptr;
    lift = nullptr;
}

// Public method definitions --------------------------------------------------
void RobotManager::CreateRobot(RobotConfigs config)
{
    switch (config)
    {
        case RobotConfigs::BLUE:
            CreateBlueRobot();
            break;
        case RobotConfigs::ORANGE:
            CreateOrangeRobot();
            break;
    }
}

Robot* RobotManager::GetRobot()
{
    return robot;
}