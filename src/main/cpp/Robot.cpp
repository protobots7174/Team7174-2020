

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

void Robot::RobotPeriodic() {

}

void Robot::AutonomousInit() {
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //     kAutoNameDefault);
    // std::cout << "Auto selected: " << m_autoSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here

    }
}

void Robot::AutonomousPeriodic() {
    updateEncoderCount();
    leftDistanceTraveledFt = (( M_PI * wheelDiameterFt)/ encoderCPR) * -leftEncoderCount;
    rightDistanceTraveledFt = ((M_PI * wheelDiameterFt)/ encoderCPR) * rightEncoderCount;

    if (rightDistanceTraveledFt < goalDistance && leftDistanceTraveledFt < goalDistance){
        drivetrain.ArcadeDrive(-0.5,0);
    }else {
        drivetrain.ArcadeDrive(0,0);
    }
    frc::SmartDashboard::PutNumber("Distance traveled left",leftDistanceTraveledFt);
    frc::SmartDashboard::PutNumber("Distance traveled right",rightDistanceTraveledFt);
    frc::SmartDashboard::PutNumber("Right encoder count", rightEncoderCount);
    frc::SmartDashboard::PutNumber("Left encoder count", leftEncoderCount);

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
    double rightX = controller.GetX(GenericHID::JoystickHand::kRightHand);
    double leftY = controller.GetY(GenericHID::JoystickHand::kLeftHand);
    double filtX = (1 - a) * prevRightX + a * rightX;
    double filtY = (1 - a) * prevLeftY + a * leftY;
    prevRightX = filtX;
    prevLeftY = filtY;

                                                                 //Ankur mode control.
    //set state 
    if (controller.GetAButton()){
        if (currentTime - buttonPressedTime > 0.2){
            buttonPressedTime = currentTime;
            aunkrModeState = !aunkrModeState;
            climbModeState = false;
        }
    } else if (controller.GetStartButton()){
        if(currentTime - buttonPressedTime > 0.2){
            buttonPressedTime = currentTime;
            climbModeState = !climbModeState;
            aunkrModeState = false;
        }
    }
    
    //set drive speed
    if (aunkrModeState){
           driveSpeed = leftY * 0.5;
           turnSpeed = rightX * 0.5;
           

    } else if (climbModeState){
        driveSpeed = leftY * 0.3;
        turnSpeed = rightX * 0.3;

    } else {
        driveSpeed = filtY;
        turnSpeed = filtX;
    }
    std::cout << driveSpeed << std::endl;
    //Raw mode control.
    // if (controller.GetX() == true){
    //   rawModeState
    // }

                                                                //Feeder Motor control.
    frc::SmartDashboard::PutNumber("feed on",feedON);
    frc::SmartDashboard::PutNumber("feedElapsedTime",feedElpasedTime);
    // if (controller.GetAButton()){
    //   feedPeriodic();
    // }else{
    //   feedON = false;
    //   feedElpasedTime = 0;
    //   prevFeedTime = time.Get();
    //   feederMotor.Set(ControlMode::PercentOutput,0.0);
    //  }

    if (controller2.GetTriggerAxis(GenericHID::JoystickHand::kLeftHand) > .1){
        feederMotor.Set(ControlMode::PercentOutput, controller2.GetTriggerAxis(GenericHID::JoystickHand::kLeftHand));
        // std::cout<<"FEEDER MOTOR ON"<<std::endl;

    }else if (controller2.GetBumper(GenericHID::JoystickHand::kLeftHand) == true){
        // std::cout<<"FEEDER MOTOR REVERSE"<<std::endl;
        feederMotor.Set(ControlMode::PercentOutput,-0.5);

    }else {
        feederMotor.Set(ControlMode::PercentOutput,0);
        // std::cout<<"FEEDER MOTOR OFF"<<std::endl;

    }
                                                                    //Intake Motor control.
        if(controller.GetYButton()){
                intakeMotor.Set(ControlMode::PercentOutput,1);
                std::cout<<"intakeeeeee"<<std::endl;
        }else	{
            intakeMotor.Set(ControlMode::PercentOutput,0);
            std::cout<<"offffffffffffff"<<std::endl;
    }


                                                                    //Shooter motor control.
    //
    // double speednew = 0;

    // if (controller.GetBButton()){
    //     speed = speed + .01;
    // }else if (controller.GetAButton()){
    //     speed= speed - .01 ;
    // }

    // if(controller.GetAButton() == true){
    //   shooterMotor.Set(ControlMode::PercentOutput,speed);
    // }else
    // {
    //   shooterMotor.Set(ControlMode::PercentOutput,0);
    // }
    // frc::SmartDashboard::PutNumber("shootermotor speed", speed);


    if (controller2.GetTriggerAxis(GenericHID::JoystickHand::kRightHand) > .1 ){
        shooterMotor.Set(ControlMode::PercentOutput,-controller2.GetTriggerAxis(GenericHID::JoystickHand::kRightHand));
        // std::cout<<"SHOOTER MOTOR ON"<<std::endl;

    } else if (controller2.GetBumper(GenericHID::JoystickHand::kRightHand) == true){
        shooterMotor.Set(ControlMode::PercentOutput, .5);
        // std::cout<<"SHOOTER MOTOR REVERSE"<<std::endl;

    }else{
        shooterMotor.Set(ControlMode::PercentOutput, 0);
        // std::cout<<"SHOOTER MOTOR OFF"<<std::endl;

    }

    frc::SmartDashboard::PutNumber("Shooter Motor", controller2.GetTriggerAxis(GenericHID::JoystickHand::kRightHand));

                                                                        //Elvator Motor control.
    if (controller.GetBumper(GenericHID::JoystickHand::kLeftHand)){
        elevatorMotor.Set(ControlMode::PercentOutput, -0.15);

    }else if (controller.GetTriggerAxis(GenericHID::JoystickHand::kLeftHand)) {
        elevatorMotor.Set(ControlMode::PercentOutput, 0.25);

    }else{
        elevatorMotor.Set(ControlMode::PercentOutput,0.0);
    }

                                                                        //Climber Motor control
    if(controller.GetTriggerAxis(GenericHID::JoystickHand::kRightHand)){
        climberMotor.Set(ControlMode::PercentOutput,1.0);

    }else if (controller.GetBumper(GenericHID::JoystickHand::kRightHand)){
        climberMotor.Set(ControlMode::PercentOutput, -0.75);

    }else{
        climberMotor.Set(ControlMode::PercentOutput, 0.0);

    }
    
    


                                                                        //limelight code
    double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
    double targetArea = table->GetNumber("ta",0.0);
    double targetSkew = table->GetNumber("ts",0.0);

    frc::SmartDashboard::PutNumber("ta",targetArea);




    // if (controller2.GetAButton() == true){
    //     elevatorMotor.Set(ControlMode::PercentOutput, 0.50);
    //     std::cout<<"25%"<<std::endl;

    // }else if (controller2.GetBButton() == true) {
    //     elevatorMotor.Set(ControlMode::PercentOutput, 0.5);
    //     std::cout<<"50%"<<std::endl;

    // }else if (controller2.GetYButton() == true){
    //     climberMotor.Set(ControlMode::PercentOutput, -0.75);
    //     std::cout<<"75%"<<std::endl;

    // }else if (controller2.GetXButton() == true){
    //     climberMotor.Set(ControlMode::PercentOutput, 1.0);
    //     std::cout<<"100%"<<std::endl;

    // }else{
    //     climberMotor.Set(ControlMode::PercentOutput,0);
    //     elevatorMotor.Set(ControlMode::PercentOutput,0);
    //     std::cout<<"0%"<<std::endl;
    // }
    drivetrain.ArcadeDrive(-driveSpeed,turnSpeed);

}

void Robot::updateEncoderCount(){
    double currentEncoderCount = frontLeftMotor.GetSelectedSensorPosition();
    leftEncoderCount += currentEncoderCount - prevLeftEncoderCount;
    prevLeftEncoderCount = currentEncoderCount;

    currentEncoderCount = frontRightMotor.GetSelectedSensorPosition();
    rightEncoderCount += currentEncoderCount - prevRightEncoderCount;
    prevRightEncoderCount = currentEncoderCount;

}


void Robot::feedPeriodic(){
    double currentFeedTime = time.Get();
    feedElpasedTime = feedElpasedTime + (currentFeedTime - prevFeedTime);
    prevFeedTime = currentFeedTime;

    if(feedON && feedElpasedTime > feedOnTime){
        feedON = false;
        feedElpasedTime = 0.0;

    }else if (!feedON && feedElpasedTime > feedOffTime){
        feedON = true;
        feedElpasedTime = 0.0;

    }
    if (feedON){
        feederMotor.Set(ControlMode::PercentOutput,0.2);

    }else{
        feederMotor.Set(ControlMode::PercentOutput, 0.0);

    }
    // std::cout<<"Feed Periodic!!!"<<std::endl;
}

void Robot::TestPeriodic() {

}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
