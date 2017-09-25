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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Clawbot.h"
//const int BASETIME = 305;

void rotate(int g) //+ er klukkuhringur og - er ofugdur klukkuhringur
{
	SensorValue[IncoderR] = 0;
  SensorValue[IncoderL] = 0;
	if(g>0)
	{
		while( SensorValue[IncoderL]<g*3.1731)//360=U
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

void navigate()
{
	motor[RightMotor] = 0;
	motor[LeftMotor]  = 0;
	wait1Msec(500);
	int R;
	int L;
	rotate(90);
	R=SensorValue(Sonar);
	wait1Msec(200);
	rotate(-180);
	L = SensorValue(Sonar);
	wait1Msec(200);
	if(L<40 && L != -1 && R < 40 && R != -1)
	{
		rotate(-90);
	}
	else if((L<R&&L!=-1)||R==-1)
	{
		rotate(180);
	}down
}

void drive()
{
	SensorValue[IncoderL]=0;
	SensorValue[IncoderR]=0;
	while((SensorValue(Sonar) > 40 || SensorValue(Sonar)==-1)&&(SensorValue[IncoderL]<360/U*100)//drives one meter or untill he finds a blockcade
	{
		if(abs(SensorValue[IncoderR]) == abs(SensorValue[IncoderL]))
		{
			motor[RightMotor] = 80;
			motor[LeftMotor]  = 80;
		}
		else if(abs(SensorValue[IncoderR]) < abs(SensorValue[IncoderL]))
		{
			motor[RightMotor] = 90;
			motor[LeftMotor]  = 70;
		}
		else
		{
			motor[RightMotor] = 70;
			motor[LeftMotor]  = 90;
		}
	}
}

bool keirla = true;
task main()
{
	while(keirla)
	{
		if(SensorValue(LightSensor)<400)//check for light
		{
				drive();
				navigate();
		}
		else{//if it's too dark, stop
				motor[RightMotor] = 0;
				motor[LeftMotor]  = 0;
		}
		if(vexRT[Btn8D]==1)
		{
			keirla=false;
		}
	}
}