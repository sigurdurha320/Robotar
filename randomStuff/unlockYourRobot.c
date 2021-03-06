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


/*
this is a robot controlled by a VEX controller, exept before you can controlle it you must input a certen password.
this password is an array of values and then those values are matched with the sensors of the robot.
for example: the robot must be in the dark or in the light, the weals need to be rotated X many degrees,
press the limitswith and have an X distance from the sonar sensor.

for this lock it's moust conveanent to lay it on it's back and block the light sensor with cloth to creaet darkness
press the limit switch and put your hand 20cm from the sonar sensor infront of it, rotate the right weal 90 degrees
clock-wize and the left weal 90 degrees counter-clock-wize and put the arm to it's highest possition.
*/



#include "Clawbot.h"
//const int BASETIME = 305;
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int key[] = {0,0,0,0,0,0,0};
int lock[] = {600,2900,2900,20,3400,90,-90};

task myMain()
{
	bool stopTakki = true;
	while(stopTakki)
	{
		if(abs(vexRT[Ch3])>20)
		{
			motor[LeftMotor]  = vexRT[Ch3];
		}
		else{motor[LeftMotor]=0;}

		if(abs(vexRT[Ch2])>20)
		{
			motor[RightMotor] = vexRT[Ch2];
		}
		else {motor[RightMotor]=0;}
		/*motor[LeftMotor]  = (vexRT[Ch2] + vexRT[Ch1])/2;
		motor[RightMotor] = (vexRT[Ch2] - vexRT[Ch1])/2;*/

		if(vexRT[Btn5U] == 1)
		{
			motor[Arm] = -127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			if(SensorValue[LimitSwitch]==0)
			{
				motor[Arm] = 127;
			}
		}
		else
		{
			motor[Arm] = 0;
		}

		if(vexRT[Btn6U] == 1)
		{
			motor[Claw] = -127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[Claw] = 127;
		}
		else
		{
			motor[Claw] = 0;
		}
		if(SensorValue(Bumper)==1 || vexRT[Btn8D]==1)
		{
			stopTakki = false;
		}
	}
}

task main()
{
	SensorValue(IncoderL)=0;
	SensorValue(IncoderR)=0;
	while(abs(key[0]-lock[0])>300 || abs(key[1]-lock[1])>300 || abs(key[2]-lock[2])>300 || abs(key[3]-lock[3])>10 || abs(key[4]-lock[4])>200
		 ||  abs(key[5]-lock[5])>20 || abs(key[6]-lock[6])>20)
	{
		key[0] =SensorValue(RightLF);//100
		key[1] =SensorValue(LeftLF);//100
		key[2] =SensorValue(CenterLF);//100
		key[3] =SensorValue(Sonar);//10
		key[4] =SensorValue(ArmStatus);//200
		key[5] =SensorValue(IncoderL);//20
		key[6] =SensorValue(IncoderR);//20
	}
	motor[RightMotor]=20;
	wait1Msec(300);

	StartTask(myMain);//run the program

	while(vexRT[Btn8D]!=true&&Bumper!=true){}//don't stop untill we say so

	StopAllTasks();//stop everything!
}
