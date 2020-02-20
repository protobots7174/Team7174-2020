/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "ctre/Phoenix.h"
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/XboxController.h>
#include <frc/Timer.h>
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

using namespace frc;

class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void updateEncoderCount();
  void feedPeriodic();

 private:
    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

    XboxController driveController{0};
    XboxController controlController{1};
//CONTROLLER VALUES
bool driveButtonA = driveController.GetAButton();
bool driveButtonB = driveController.GetBButton();
bool driveButtonY = driveController.GetYButton();
bool driveButtonX = driveController.GetXButton();

bool controlButtonA = controlController.GetAButton();
bool controlButtonB = controlController.GetBButton();
bool controlButtonY = controlController.GetYButton();
bool controlButtonX = controlController.GetXButton();

// 
//main robot/
//DRIVETRAIN
    WPI_TalonSRX frontLeftMotor{5}; 
    WPI_TalonSRX backLeftMotor{6};  
    SpeedControllerGroup leftSideMotors{frontLeftMotor, backLeftMotor};

    WPI_TalonSRX frontRightMotor{1};  
    WPI_TalonSRX backRightMotor{0}; 
    SpeedControllerGroup rightSideMotors{frontRightMotor, backRightMotor};

    DifferentialDrive drivetrain{leftSideMotors, rightSideMotors};
//
//DRIVETRAIN STATES    
    bool aunkrModeState = false;
    bool rawModeState = false;
    bool climbModeState = false;
//
//ACTIONARY MOTORS
    WPI_TalonSRX shooterMotor{2}; 
    WPI_TalonSRX feederMotor{3}; 
    WPI_TalonSRX climberMotor{8};  
    WPI_TalonSRX elevatorMotor{7};
    WPI_TalonSRX intakeMotor{9};
//
    double encoderCPR = 2048.0 * 10.71; //one wheel rotation
    double wheelDiameterFt = 0.5; //6 inches
    double rightDistanceTraveledFt = 0.0;
    double leftDistanceTraveledFt = 0.0;
    double goalDistance = 10.0; 

    double driveSpeed = 0;
    double turnSpeed = 0;

    Timer time;
    double buttonPressedTime = 0;

    double prevFeedTime = 0.0;
    double feedOffTime = 1.0;
    double feedOnTime = 1.0;
    double feedElpasedTime = 0.0;
    bool feedON= false;




    //practice.
    // WPI_TalonSRX shooterMotor{0}; 
    // WPI_TalonSRX feederMotor{0}; 
    // WPI_TalonSRX climberMotor{0};  

    // WPI_TalonSRX frontLeftMotor{4}; 
    // WPI_TalonSRX backLeftMotor{3};  
    // SpeedControllerGroup leftSideMotors{frontLeftMotor, backLeftMotor};

    // WPI_TalonSRX frontRightMotor{1};  
    // WPI_TalonSRX backRightMotor{2}; 
    // SpeedControllerGroup rightSideMotors{frontRightMotor, backRightMotor};

    // DifferentialDrive drivetrain{leftSideMotors, rightSideMotors};


    //Auton Values.
    double leftEncoderCount = 0;
    double rightEncoderCount = 0;
    double prevLeftEncoderCount = frontLeftMotor.GetSelectedSensorPosition();
    double prevRightEncoderCount = frontRightMotor.GetSelectedSensorPosition();

    double prevRightX = 0;
    double prevLeftY = 0;
    // double prevRightX = 0;
    // double prevRightY = 0;
    double Tf = 0.30;
 
    double Ts = 1.0/50.0;
    double a = Ts/(Tf + Ts);

    //DifferentialDrive * difDrive = new DifferentialDrive(motor1, motor2);


    double speed = 0.50;

};
