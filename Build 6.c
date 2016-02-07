#pragma config(Sensor, S1,     SensorL,        sensorColorNxtFULL)
#pragma config(Sensor, S2,     SensorM,        sensorColorNxtFULL)
#pragma config(Sensor, S3,     SensorR,        sensorColorNxtFULL)
#pragma config(Sensor, S4,     SensorSonar,        sensorSONAR)
#pragma config(Motor,  motorA,          MotorL,        tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          MotorR,        tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//sensor reading estimation
int whiteA (){
	return SensorValue(SensorL) % 70;
}
int whiteC(){
	
	retun SensorValue(SensorR) % 70;
}
int redB() {
	return SensorValue(SensorM) % 55;
}
int blackA(){
	return SensorValue(SensorL);
	}	//Need a formula for estimation
int blackC(){
	return SensorValue(SensorR);
}
bool sensorOff = false;


//Movement Parts
		//Forward (Left Wheel)
task leftForward ()
{
		if (whiteA <=10 && whiteC <=10)	//Might become a rough estimation around a certain range
		{
			setMotorTarget(motorL,360,50) ;
		}
		else if (whiteA >= 10 && blackA == 7)			//This section needs revist, possible backing up before adjusting
		{
		 setMotorTarget(motorL,2,25);
		}
		else (whiteC >=10 && blackC == 7);			// So is this
		{
		 setMotorTarget(motorL,0,0);
		}
}

	//Forward(Right Wheel)
task rightForward ()
{
		if (whiteA <=10 && whiteC <=10)
			{
				setMotorTarget(motorR,360,50) ;
			}
		else if (whiteA >= 10 && blackA == 7)							//This section needs revist, possible backing up before adjusting
			{
			 setMotorTarget(motorR,0,0);
			}
		else (whiteC >= 10 && blackC == 7);						// So is this
			{
			 setMotorTarget(motorR,3,25);
			}
}

	//Forward Circular Path 1(Left Wheel)
task leftForwardLoop ()
{
		if (whiteA <=10 && whiteC <=10)
		{
			setMotorTarget(motorL,360,50) ;		//Distance requires offset for turning
		}
		else if (whiteA >= 10 && blackA == 7)			//This section needs revist, possible backing up before adjusting
		{
		 setMotorTarget(motorL,2,25);
		}
		else (whiteC >= 10 && blackC == 7);			// So is this
		{
		 setMotorTarget(motorL,0,0);
		}
}

	//Forward Circular Path 1(Right Wheel)
task rightForwardLoop ()
{
		if (whiteA <=10 && whiteC <=10)
			{
				setMotorTarget(motorR,360,50) ;		//Distance requires offset for turning
			}
		else if (whiteA >= 10 && blackA == 7)							//This section needs revist, possible backing up before adjusting
			{
			 setMotorTarget(motorR,0,0);
			}
		else (whiteC >= 10 && blackC == 7);						// So is this
			{
			 setMotorTarget(motorR,3,25);
			}
}

	//Forward Circular Path 2(Left Wheel)
task leftForwardSemi ()
{
		if (whiteA <=10 && whiteC <=10)
		{
			setMotorTarget(motorL,360,50) ;		//Distance requires offset for turning
		}
		else if (whiteA >= 10 && blackA == 7)			//This section needs revist, possible backing up before adjusting
		{
		 setMotorTarget(motorL,2,25);
		}
		else (whiteC >= 10 && blackC == 7);			// So is this
		{
		 setMotorTarget(motorL,0,0);
		}
}

	//Forward Circular Path 2(Right Wheel)
task rightForwardSemi ()
{
		if (whiteA <=10 && whiteC <=10)
			{
				setMotorTarget(motorR,360,50) ;		//Distance requires offset for turning
			}
		else if (whiteA >= 10 && blackA == 7)							//This section needs revist, possible backing up before adjusting
			{
			 setMotorTarget(motorR,0,0);
			}
		else (whiteC >= 10 && blackC == 7);						// So is this
			{
			 setMotorTarget(motorR,3,25);
			}
}

		//Left Turn (Left wheel)
task leftLeftTurn ()
{
	setMotorTarget(MotorL,30,25);
}

		//Left Turn (Right wheel)
task rightLeftTurn ()
{
	setMotorTarget(MotorR,90,25);
}

		//Right Turn (Left wheel)
task leftRightTurn ()
{
	setMotorTarget(MotorL,90,25);
}

		//Left Turn (Right wheel)
task rightRightTurn ()
{
	setMotorTarget(MotorR,60,25);
}




//General Movement
	//Forward Module
 task moveForward (){
	while (redB <= 10)
	{
		startTask(leftForward);
		startTask(rightForward);
	}
}

	//Circular Path 1 Forward Module
 task moveForwardLoop ()
{
	while (redB<= 10)
	{
		startTask(leftForwardLoop);
		startTask(rightForwardLoop);
	}
}

	//Circular Path 2 Forward Module
 task moveForwardSemi ()
{
	while (redB<= 10)
	{
		startTask(leftForwardSemi);
		startTask(rightForwardSemi);
	}
}

	//Left Turn
task leftTurn()	//Distance require calculation
{
	startTask(leftLeftTurn);
	startTask(rightLeftTurn);
}

	//Right Turn
task rightTurn		//Distance require calculation
{
	startTask(leftRightTurn);
	startTask(rightRightTurn);
}

			//Distance sensing module
task sensor()
{
	if (sensorOff == false)
	{
		while (SensorValue(SensorD) <= 20) //possible change in distance
			{
				suspendTask(leftTurn);
				suspendTask(rightTurn);
				suspendTask(moveForwardLoop);
				suspendTask(moveForwardSemi);
				suspendTask(moveForward);	//Add more along the way
				sensorOff = true;
			}
	}
	else
	{
	startTask (sensor);
	sensorOff = false;
	}
}


task main()
{
	startTask (moveForward);			//Input "startTask();"
	startTask (moveForwardLoop);
	startTask (leftTurn);
	startTask (rightTurn);
	startTask (moveForwardSemi);
	startTask (sensor);
}
