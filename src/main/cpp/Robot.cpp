/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace frc;
Robot::Robot(){
//  WPI_TalonSRX * motor2 = new WPI_TalonSRX(2);
//  WPI_TalonSRX * motor1 = new WPI_TalonSRX(1);




}
void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //motor.Set(ControlMode::PercentOutput,.1);
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {

updateEncoderCount();
leftDistanceTraveledFt = (( M_PI * wheelDiameterFt)/ encoderCPR) * leftEncoderCount;
rightDistanceTraveledFt = ((M_PI * wheelDiameterFt)/ encoderCPR) * rightEncoderCount;

if (rightDistanceTraveledFt < goalDistance && leftDistanceTraveledFt < goalDistance){
  drivetrain.ArcadeDrive(-0.5,0);
}else {
  drivetrain.ArcadeDrive(0,0);
}

  // if (m_autoSelected == kAutoNameCustom) {
  //   // Custom Auto goes here
  // } else {
  //   // Default Auto goes here
  // }
}

void Robot::TeleopInit() {
  time.Start();
}

void Robot::TeleopPeriodic() {
  double currentTime = time.Get();
  double leftX = controller.GetX(GenericHID::JoystickHand::kLeftHand);
  double leftY = controller.GetY(GenericHID::JoystickHand::kLeftHand);
  double filtX = (1 - a) * prevLeftX + a*leftX;
  double filtY = (1 - a) * prevLeftY + a*leftY;
  prevLeftX = filtX;
  prevLeftY = filtY;


  // std::cout << "joy:" << controller.GetX( GenericHID::JoystickHand::kLeftHand) << std::endl;
  // std::cout << "filtX" << filtX << std::endl;
  // std::cout << "filtY" <<filtY << std::endl;
  // std::cout << "a = " << a << std::endl;
  //std :: cout
  // std::cout << controller.GetX(0) << std::endl;
  
//  if (controller.GetAButton() == true){
//    shooterMotor.Set(ControlMode::PercentOutput, 0.25);
//    std::cout<<"25%"<<std::endl;

//  }else if (controller.GetBButton() == true) {
//    shooterMotor.Set(ControlMode::PercentOutput, 0.5);
//    std::cout<<"50%"<<std::endl;

//  }else if (controller.GetYButton() == true){
//    shooterMotor.Set(ControlMode::PercentOutput, 0.75);
//    std::cout<<"75%"<<std::endl;

//  }else if (controller.GetXButton() == true){
//    shooterMotor.Set(ControlMode::PercentOutput, 1.0);
//    std::cout<<"100%"<<std::endl;

//  }else{
//   shooterMotor.Set(ControlMode::PercentOutput,0);
//   std::cout<<"0%"<<std::endl;
//    }

 if (controller.GetAButton() == true){
   if (currentTime - buttonPressedTime > 0.2){
   buttonPressedTime = currentTime;
   aunkrModeState = !aunkrModeState;
   }
 }
   if (aunkrModeState == true){
   filtY = filtY/2;
   filtX = filtX/2;
   }
  
    
 
  std::cout<<frontRightMotor.GetSelectedSensorPosition()<<std::endl;
  drivetrain.ArcadeDrive(filtY,filtX);

}

// if (controller.GetX() == true){
//   rawModeState
// }
void Robot::updateEncoderCount(){
double currentEncoderCount = frontLeftMotor.GetSelectedSensorPosition();
leftEncoderCount += currentEncoderCount - prevLeftEncoderCount;
prevLeftEncoderCount = currentEncoderCount;

currentEncoderCount = frontRightMotor.GetSelectedSensorPosition();
rightEncoderCount += currentEncoderCount - prevRightEncoderCount;
prevRightEncoderCount = currentEncoderCount;

}
void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
