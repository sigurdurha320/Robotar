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


bool keyrsla = true;
int RC;
int CC;
int LC;
task main()
{
	while(vexRT[Btn8L]==0){}//starts when a button is pressed

	  	int threshold = 1300;

				int R = 0;
				int L = 0;

	  	while(keyrsla)
			{
				L=0;
				R=0;
				RC=SensorValue(RightLF);
				CC=SensorValue(CenterLF);
				LC=SensorValue(LeftLF);
		    if(SensorValue(RightLF) < threshold)
		    {
		      // counter-steer right:
		      L  	+= 30;
		      R 	-= 30;
		    }
		    // CENTER sensor sees dark:
		    if(SensorValue(CenterLF) < threshold)
		    {
		      // go straight
		      L  += 30;
		      R  += 30;
		    }
		    // LEFT sensor sees dark:
		    if(SensorValue(LeftLF) < threshold)
		    {
		      // counter-steer left:
		      L  	-= 30;
		      R 	+= 30;
		    }
  			motor[LeftMotor]  = L;
		    motor[RightMotor] = R;

	if(vexRT[Btn8D]==1)
		{
			keyrsla=false;
		}
	}
}
