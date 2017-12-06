#pragma config(Sensor, in1,    RightLF,        sensorLineFollower)
#pragma config(Sensor, in2,    CenterLF,       sensorLineFollower)
#pragma config(Sensor, in3,    LeftLF,         sensorLineFollower)
#pragma config(Sensor, in4,    LightSensor,    sensorReflection)
#pragma config(Sensor, in5,    ArmStatus,      sensorPotentiometer)
#pragma config(Sensor, in7,    gyro,           sensorGyro)
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
int x=0;
int y=0;
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

short sum(short pk)
{
	short combined =0;
	for(int i = 0;i<4;i++)
	{
		combined += logicGates[pk][i];
	}
	return combined;
}
char * min(string kr, string sw)
{
	if(sizeof(kr)>sizeof(sw))
	{
		return kr;
	}
	else
	{
		return sw;
	}
}

short kek = sum(2);

short maze[8][8];

	//logicGate[maze[x][y]];//how to reference a logic gate

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
	]
	logicGate[maze[3][1]][2]=logicGate[maze[3][2]][0]
	logicGate[maze[3][1]][1]=logicGate[maze[4][1]][3]
	*/

//the robot has found his exit once maze[x][y] is out of range

//how to navigate to null value gates
/*
function(string)
check if loops
if so: return string+'z';
resault;
swap;
	for(sum(ligicgate))
	{
		swap =	function(string+i);
		if(swap[swap.length-1]!='z')
		{
			resalut = min(resalut,swap);
	}
return resault;
run the string;*/
//return example: "12101301"

//backdrack deadEnd gates
/*
	while where he is sum of open gates<2
	go back(to the open side
	close the open gate in the logic gate
*/
void rotate(int g)
{
	//null stilla incoderana
	SensorValue[IncoderR] = 0;
  SensorValue[IncoderL] = 0;
  int right =0;
  int left =0;
  float slow = 1;
  while(SensorValue[gyro]-g < 5)
  {
  	if(abs(SensorValue[IncoderR])>abs(SensorValue[IncoderL]))
  	{
  		left = 50;
  		right = 40;
  	}
  	else if (abs(SensorValue[IncoderR])<abs(SensorValue[IncoderL]))
  	{
  		left = 40;
  		right = 50;
  	}
  	else
  	{
  		left = 45;
  		right = 45;
  	}
  	if(SensorValue[gyro]-g < 50)
  	{
  		slow= 0.5;
  	}

  	motor[RightMotor] = right*(SensorValue[gyro]-g)/abs(SensorValue[gyro]-g)*slow;
		motor[LeftMotor]  = left*(g-SensorValue[gyro])/abs(g-SensorValue[gyro])*slow;
  }
}
void setLogicGate()
{
	float values[4] = {0,0,0,0};
	int i;
	for(i=0; i<4; i++){
		rotate(900*i);
		values[i] =	SensorValue(Sonar);
		wait1Msec(750);
	}

	short gate = 0;
	if(values[0]>50)//if it's open "up"
	{
		gate=8
	}
	if(values[1]>50)//if it's open "right"
	{
		gate=gate+4;
	}
	if(values[2]>50)//if it's open "down"
	{
		gate=gate+2;
	}
	if(values[3]>50)//if it's open "left"
	{
		gate=gate+1;
	}
	maze[x][y]=gate;//(must keep track on x and y)
}
void navigate()
{

}
char * nextNull(char * rout)//"012103"
{
	int tempX=x;//x cord for instance
	int tempY=y;//y cord for instance
	string shortestPath="";
	string swap ="";
	for(int i =0;i<sizeof(rout);i++)//what's the current gate of the instance
	{
		if(rout[i]==0)
		{
			tempY-=1;
		}
		else if(rout[i]==1)
		{
			tempX+=1;
		}
		else if(rout[i]==2)
		{
			tempY+=1;
		}
		else if(rout[i]==3)
		{
			tempX-=1;
		}
	}
	if(maze[tempX][tempY]==NULL)
	{
		return rout;
	}
	else
	{
		int restrictor[4]={2,3,0,1};
		for(int i = 0; i<4;i++)
		{
			if(logicGates[maze[tempX][tempY]][i]==1 && rout[strlen(rout)-1]!=restrictor[i])
			{
				swap = nextNull(rout+i);//<-?
				if(shortestPath=="")
				{
					shortestPath=swap;
				}
				else
				{
					shortestPath=min(shortestPath,swap);
				}
			}
		}
		return shortestPath;
	}
}

task solveMaze()
{
		while(true)
		{
			setLogicGate();
			navigate();
		}
}
task closeOffDeadEnds()
{
	while(true)
	{
		for(int xCord=0;xCord<sizeof(maze);xCord++)
		{
			for(int yCord=0;yCord<sizeof(maze[0]);yCord++)
			{
				if(xCord!=x&&yCord!=y)
				{
					if(logicGates[maze[xCord][yCord]]==1)
					{
						maze[xCord][yCord]=0;
						maze[xCord-1][yCord]=	maze[xCord-1][yCord]-4;
					}
					else if(logicGates[maze[xCord][yCord]]==2)
					{
						maze[xCord][yCord]=0;
						maze[xCord][yCord+1]=	maze[xCord][yCord+1]-8;
					}
					else if(logicGates[maze[xCord][yCord]]==4)
					{
						maze[xCord][yCord]=0;
						maze[xCord+1][yCord]=	maze[xCord+1][yCord]-1;
					}
					else if (logicGates[maze[xCord][yCord]]==8)
					{
						maze[xCord][yCord]=0;
						maze[xCord][yCord-1]=	maze[xCord-1][yCord]-2;
					}
				}
			}
		}
	}
}

task main()
{
	SensorType[gyro] = sensorNone;
  wait1Msec(1000);
  SensorType[gyro] = sensorGyro;
  wait1Msec(2000);

	StartTask(solveMaze);
	while(vexRT[Btn8D]!=true&&Bumper!=true){}
	StopAllTasks();
}
