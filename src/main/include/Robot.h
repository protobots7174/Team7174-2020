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
 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

 bool aunkrModeState = false;
 bool rawModeState = false;

double encoderCPR = 2048 * 10.71; //one wheel rotation
double wheelDiameterFt = 6/12; //6 inches
double rightDistanceTraveledFt = 0;
double leftDistanceTraveledFt = 0;
double goalDistance = 10;



  Timer time;
  double buttonPressedTime = 0;

  XboxController controller{0};

  WPI_TalonSRX shooterMotor{000000000000000000000};

  WPI_TalonSRX frontLeftMotor{1};
  WPI_TalonSRX backLeftMotor{2};
  SpeedControllerGroup leftSideMotors{frontLeftMotor, backLeftMotor};

  WPI_TalonSRX frontRightMotor{3};
  WPI_TalonSRX backRightMotor{4};
  SpeedControllerGroup rightSideMotors{frontRightMotor, backRightMotor};

  DifferentialDrive drivetrain{leftSideMotors, rightSideMotors};

  double leftEncoderCount = 0;
  double rightEncoderCount = 0;
  double prevLeftEncoderCount = frontLeftMotor.GetSelectedSensorPosition();
  double prevRightEncoderCount = frontRightMotor.GetSelectedSensorPosition();


  double prevLeftX = 0;
  double prevLeftY = 0;
  // double prevRightX = 0;
  // double prevRightY = 0;
  double Tf = 0.25;

  double Ts = 1.0/50.0;
  double a = Ts/(Tf + Ts);

  //DifferentialDrive * difDrive = new DifferentialDrive(motor1, motor2);

};
