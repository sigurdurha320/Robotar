#pragma config(Sensor, in1,    RightLF,        sensorLineFollower)
#pragma config(Sensor, in2,    CenterLF,       sensorLineFollower)
#pragma config(Sensor, in3,    LeftLF,         sensorLineFollower)
#pragma config(Sensor, in4,    LightSensor,    sensorReflection)
#pragma config(Sensor, in5,    ArmStatus,      sensorPotentiometer)
#pragma config(Sensor, dgtl4,  Bumper,         sensorTouch)
#pragma config(Sensor, dgtl5,  LimitSwitch,    sensorTouch)
#pragma config(Sensor, dgtl7,  Sonar,          sensorSONAR_mm)
#pragma config(Sensor, dgtl9,  IncoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl11, IncoderR,       sensorQuadEncoder)
#pragma config(Motor,  port2,           LeftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           Arm,           tmotorVex269, openLoop)
#pragma config(Motor,  port8,           Claw,          tmotorVex269, openLoop)
#pragma config(Motor,  port9,           RightMotor,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Clawbot.h"
//const int BASETIME = 305;
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void drive_f_t(int k)
{
	motor[RightMotor]=127;
	motor[LeftMotor]=127;
	wait1Msec(k);
	motor[RightMotor]=0;
	motor[LeftMotor]=0;
}
void drive_b_t(int k)
{
	motor[RightMotor]=-127;
	motor[LeftMotor]=-127;
	wait1Msec(k);
	motor[RightMotor]=0;
	motor[LeftMotor]=0;
}

void drive_f_d(int k)//distance in cm
{
	SensorValue[IncoderR] = 0;
  SensorValue[IncoderL] = 0;
	while(k/U > SensorValue[IncoderR]/360 && k/U > SensorValue[IncoderL]/360)
	{
		if(abs(SensorValue[IncoderR]) == abs(SensorValue[IncoderL])) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[RightMotor] = 80;		    // Right Motor is run at power level 80
			motor[LeftMotor]  = 80;		    // Left Motor is run at power level 80
		}
		else if(abs(SensorValue[IncoderR]) > abs(SensorValue[IncoderL]))	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[RightMotor] = 60;		    // Right Motor is run at power level 60
			motor[LeftMotor]  = 80;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[RightMotor] = 80;		    // Right Motor is run at power level 80
			motor[LeftMotor]  = 60;		    // Left Motor is run at power level 60
		}
	}
	motor[RightMotor]=0;
	motor[LeftMotor]=0;
}
void drive_b_d(int k)//distance in cm
{
	SensorValue[IncoderR] = 0;
  SensorValue[IncoderL] = 0;
	while(k/U > SensorValue[IncoderR]/360 && k/U > SensorValue[IncoderL]/360)
	{
		if(abs(SensorValue[IncoderR]) == abs(SensorValue[IncoderL])) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[RightMotor] = -80;		    // Right Motor is run at power level 80
			motor[LeftMotor]  = -80;		    // Left Motor is run at power level 80
		}
		else if(abs(SensorValue[IncoderR]) > abs(SensorValue[IncoderL]))	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[RightMotor] = -60;		    // Right Motor is run at power level 60
			motor[LeftMotor]  = -80;		    // Left Motor is run at power level 80
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[RightMotor] = -80;		    // Right Motor is run at power level 80
			motor[LeftMotor]  = -60;		    // Left Motor is run at power level 60
		}
	}
	motor[RightMotor]=0;
	motor[LeftMotor]=0;
}

void rotate(int g) //+ er klukkuhringur og - er ofugdur klukkuhringur
{
	SensorValue[IncoderR] = 0;
  SensorValue[IncoderL] = 0;
	if(g>0)
	{
		while( SensorValue[IncoderL]<g*3.1731)
		{
				motor[RightMotor] = -60;
				motor[LeftMotor]  = +60;
		}
	}
	else
	{
		while(SensorValue[IncoderL]>g*3.1731)
		{
				motor[RightMotor] = +60;
				motor[LeftMotor]  = -60;
		}
	}
	motor[RightMotor] = 0;
	motor[LeftMotor]  = 0;
}

task main()
{
	drive_f_d(20);
	wait1Msec(500);
	rotate(-90);
	wait1Msec(500);
	drive_f_d(20);
	wait1Msec(500);
	rotate(90);
	wait1Msec(500);
	drive_f_d(20);
	wait1Msec(500);
	rotate(90);
	wait1Msec(500);
	drive_f_d(20);
}
