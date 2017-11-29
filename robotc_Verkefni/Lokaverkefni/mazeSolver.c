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

bool logicGates[16][4]=
	{
		{0,0,0,0},
		{0,0,0,1},
		{0,0,1,0},
		{0,0,1,1},
		{0,1,0,0},
		{0,1,0,1},
		{0,1,1,0},
		{0,1,1,1},
		{1,0,0,0},
		{1,0,0,1},
		{1,0,1,0},
		{1,0,1,1},
		{1,1,0,0},
		{1,1,0,1},
		{1,1,1,0},
		{1,1,1,1}
	};
short maze[8][8];

	//logicGate[maze[x][y]];//how to reference a logic gate
	//logicGate[maze[x][y]][z];//how to reference a direction in a logic gate

/*how to set a logic gate:
short meh =0;
if(values[0]>50)//if it's open "up"
{
	meh=8
}
if(values[1]>50)//if it's open "right"
{
	meh=meh+4;
}
if(values[2]>50)//if it's open "down"
{
	meh=meh+2;
}
if(values[3]>50)//if it's open "left"
{
	meh=meh+1;
}
maze[x][y]=meh;//(must keep track on x and y
*/

/*[//0 2 tengjast og 1 3 tenjast
		[0110, 0011, 0100, 0011],
		[1110, 1001, 0110, 1001],
		[1110, 0011, 1110, 0001],
		[1000, 0011, 1101, 0101]
	]*/
//the robot has found his exit once maze[x][y] is out of range

//how to navigate to null value gates


//backdrack deadEnd gates
/*
	while where he is sum of open gates<2
	go back(to the open side
	close the open gate in the logic gate
/*


task main()
{


}
