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

/*
The robot is programmed to solve a maze, it will drive forward until there is a hinderence,
then it will turn 90 degrees in a random direction, right or left.
If the robort reaches a point where he cant turn, it will go back
the way he came and proceed to take paths he has not taken before until he has solved the maze.
*/


task main()
{
	float maze[8][8];//x,y.1011   y-floor(y)*1000
	[//0 2 tengjast og 1 3 tenjast
	[0110, 0011, 0100, 0011
	1110, 1001, 0110, 1001
	1110, 0011, 1110, 0001
	1000, 0011, 1101, 0101]
}
