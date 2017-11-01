#pragma config(Sensor, in1,    RightLF,        sensorLineFollower)
#pragma config(Sensor, in2,    CenterLF,       sensorLineFollower)
#pragma config(Sensor, in3,    LeftLF,         sensorLineFollower)
#pragma config(Sensor, in4,    LightSensor,    sensorReflection)
#pragma config(Sensor, in5,    ArmStatus,      sensorPotentiometer)
#pragma config(Sensor, dgtl4,  Bumper,         sensorTouch)
#pragma config(Sensor, dgtl5,  LimitSwitch,    sensorTouch)
#pragma config(Sensor, dgtl7,  Sonar,          sensorSONAR_cm)
#pragma config(Sensor, dgtl9,  IncoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl11, IncoderR,       sensorQuadEncoder)
#pragma config(Motor,  port2,           LeftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           Claw,          tmotorVex269, openLoop)
#pragma config(Motor,  port8,           Arm,           tmotorVex269, openLoop)
#pragma config(Motor,  port9,           RightMotor,    tmotorVex393, openLoop)

#include "Clawbot.h"

int armstatusinn=SensorValue(ArmStatus);
int son=SensorValue(Sonar);
int RC;
int CC;
int LC;
bool fin = false;

task phase1()
{
	int threshold = 1300;

	int right = 0;
	int left = 0;

	while(true)
	{
		son=SensorValue(Sonar);
		left=0;
		right=0;
		RC=SensorValue(RightLF);
		CC=SensorValue(CenterLF);
		LC=SensorValue(LeftLF);
    if(SensorValue(RightLF) > threshold)
    {
      // counter-steer right:
      left  	+= 30;
      right 	-= 30;
    }
    // CENTER sensor sees dark:
    if(SensorValue(CenterLF) > threshold)
    {
      // go straight
      left  += 30;
      right  += 30;
    }
    // LEFT sensor sees dark:
    if(SensorValue(LeftLF) > threshold)
    {
      // counter-steer left:
      left  	-= 30;
      right 	+= 30;
    }
		motor[LeftMotor]  = left;
    motor[RightMotor] = right;

	}
}
task phase2()
{
	motor[LeftMotor]  = 0;
  motor[RightMotor] = 0;
	motor[Arm] = 30;
	wait1Msec(500);
	motor[Arm] = 0;
	wait1Msec(1000);
	motor[Claw] = -20;
	wait1Msec(2000);
	motor[Arm] = -90;
	while(SensorValue(ArmStatus)<2000){}
	motor[Arm] =0;
	//turn around
	SensorValue[IncoderL] = 0;
	while( SensorValue[IncoderL]<180*3.1731)
	{
			motor[RightMotor] = -60;
			motor[LeftMotor]  = +60;
	}

	int threshold = 1300;

		int right = 0;
	int left = 0;

	while(true)
	{
		left=0;
		right=0;
		RC=SensorValue(RightLF);
		CC=SensorValue(CenterLF);
		LC=SensorValue(LeftLF);
		if(RC<threshold&&CC<threshold&&LC<threshold)
		{
			fin=true;
		}
    if(SensorValue(RightLF) > threshold)
    {
      // counter-steer right:
      left  	+= 30;
      right 	-= 30;
    }
    // CENTER sensor sees dark:
    if(SensorValue(CenterLF) > threshold)
    {
      // go straight
      left  += 30;
      right  += 30;
    }
    // LEFT sensor sees dark:
    if(SensorValue(LeftLF) > threshold)
    {
      // counter-steer left:
      left  	-= 30;
      right 	+= 30;
    }
		motor[LeftMotor]  = left;
    motor[RightMotor] = right;

	}
}

void DefaultSetting()
{
	motor[Claw] = -40;
	wait1Msec(600);
	motor[Claw] = 0;
	wait1Msec(1000);
	motor[Claw] = 40;
	wait1Msec(1000);
	armstatusinn=SensorValue(ArmStatus);
	while(abs(SensorValue(ArmStatus)-1500)>70)
	{
		while(abs(SensorValue(ArmStatus)-1500)>70)
		{
			if(SensorValue(ArmStatus)>1500)
			{
				motor[Arm] = 90;
			}
			else
			{
				motor[Arm] = -90;
			}
			armstatusinn=SensorValue(ArmStatus);
		}
		motor[Arm]=0;
		wait1Msec(2000);
	}
}
task main()
{
	while(vexRT[Btn8L]==0){}//start

	DefaultSetting();

//phase 1
	StartTask(phase1);

	while((vexRT[Btn8D]!=true&&Bumper!=true) && (SensorValue(Sonar)>SensorToClaw||SensorValue(Sonar)==-1)){}

	StopTask(phase1);

//phase 2
	StartTask(phase2);

	while((vexRT[Btn8D]!=true&&Bumper!=true) && fin==false){}

	StopTask(phase2);


			motor[LeftMotor]  = 0;
	    motor[RightMotor] = 0;
	    motor[Claw] = 20;
	    wait1Msec(100);
	    motor[Claw] = 0;
}
