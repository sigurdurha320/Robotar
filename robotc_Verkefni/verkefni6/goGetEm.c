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

int RC;
int CC;
int LC;
bool nafn = false;
int threshold = 1300;
int waitTime = 750;
bool isRunningWait=false;

task wait()
{
	isRunningWait=true;
	wait1Msec(waitTime);
	nafn = true;
}

void phase1()
{
	int right = 0;
	int left = 0;
	while(SensorValue(Sonar)>SensorToClaw||SensorValue(Sonar)==-1)
	{
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
      left  += 10;
      right  += 10;
    }
    // LEFT sensor sees dark:
    if(SensorValue(LeftLF) > threshold)
    {
      // counter-steer left:
      left  	-= 30;
      right 	+= 30;
    }
    if(SensorValue(LeftLF) < threshold&&SensorValue(CenterLF) > threshold&&SensorValue(RightLF) < threshold)
    {
      // go straight
      left  += 30;
      right  += 30;
    }

		motor[LeftMotor]  = left;
    motor[RightMotor] = right;
	}
}
void phase2()
{
	motor[LeftMotor]  = 0;
  motor[RightMotor] = 0;
	wait1Msec(300);
	motor[Claw] = -20;
	wait1Msec(2000);
	motor[Arm] = -90;
	while(SensorValue(ArmStatus)<2000){}
	motor[Arm] =0;
	//turn around

	int threshold = 1300;
	StartTask(wait);
	while(RC<threshold&&CC<threshold&&LC<threshold||nafn==false)
	{
		RC=SensorValue(RightLF);
		CC=SensorValue(CenterLF);
		LC=SensorValue(LeftLF);
			motor[RightMotor] = -60;
			motor[LeftMotor]  = +60;
	}



	int right = 0;
	int left = 0;
	nafn = false;
	waitTime=1000;
	while((RC>threshold||CC>threshold||LC>threshold)||nafn==false)
	{
		left=0;
		right=0;
		RC=SensorValue(RightLF);
		CC=SensorValue(CenterLF);
		LC=SensorValue(LeftLF);
    if(RC > threshold)
    {
      // counter-steer right:
      left  	+= 30;
      right 	-= 30;
    }
    // CENTER sensor sees dark:
    if(CC > threshold)
    {
      // go straight
      left   += 10;
      right  += 10;
    }
    // LEFT sensor sees dark:
    if(LC > threshold)
    {
      // counter-steer left:
      left  	-= 30;
      right 	+= 30;
    }
    if(SensorValue(LeftLF) < threshold&&SensorValue(CenterLF) > threshold&&SensorValue(RightLF) < threshold)
    {
      // go straight
      left   += 30;
      right  += 30;
    }
		motor[LeftMotor]  = left;
    motor[RightMotor] = right;
		if((RC<threshold&&CC<threshold&&LC<threshold)&&isRunningWait==false)
		{
			StartTask(wait);
		}
		else if(isRunningWait==true)
		{
			StopTask(wait);
			nafn=false;
			isRunningWait=false;
		}
	}
	motor[LeftMotor]  = 0;
  motor[RightMotor] = 0;
  motor[Claw] = 40;
  wait1Msec(1000);
  motor[Claw] = 0;
}

void DefaultSetting()
{
	nafn = false;
	waitTime=750;
	int armStada = 1350;
	motor[Claw] = -20;
	wait1Msec(700);
	motor[Claw] = 0;
	wait1Msec(1000);
	motor[Claw] = 40;
	wait1Msec(1000);
	motor[Claw] = 0;
	while(abs(SensorValue(ArmStatus)-armStada)>70)
	{
		while(abs(SensorValue(ArmStatus)-armStada)>70)
		{
			if(SensorValue(ArmStatus)>armStada)
			{
				motor[Arm] = 90;
			}
			else
			{
				motor[Arm] = -90;
			}
		}
		motor[Arm]=0;
		wait1Msec(500);
	}
}

task kerisla()
{
	DefaultSetting();

//phase 1
	phase1();

//phase 2
  phase2();
}



task main()
{
	while(vexRT[Btn8D]!=true&&Bumper!=true){
		if(vexRT[Btn8L]==1)
		{
			StartTask(kerisla);
		}//start
	}

	StopAllTasks();
}
