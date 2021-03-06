#pragma config(Sensor, S1,     colorSensorA,   sensorColorNxtFULL)
#pragma config(Sensor, S2,     colorSensorB,   sensorNone)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          motorL,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorR,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// void leftparking()// did all this assuming motorA is left, motorB is right, colorSensorA is left, colorSensorB is right
task sonarFunction()
	{
		while(1==1)
		{
			motor[motorC] = 45; //estimate
			nMotorEncoder[motorA] = 0;
			nMotorEncoderTarget[motorC] = 90;
			wait1Msec(100);
			nMotorEncoderTarget[motorC] = -90;
			wait1Msec(100);
		}

	}
task leftparking()
	{
		if (SensorValue(sonarSensor) <= 75)
			{
				motor[motorL] = 75;                                          // lego group x*y x=diamter, y=width
				motor[motorR] = 75;
		 	}
		else
			{
				motor[motorL] = 0;
				motor[motorR] = 90;
				wait1Msec(100);
				nMotorEncoder[motorL] = 0;
				nMotorEncoder[motorR] = 0;
				motor[motorL] = 75;
				motor[motorR] = 75;
				nMotorEncoderTarget[motorL] = 2122;
				nMotorEncoderTarget[motorR] = 2122;
			}
	}
task rightparking()
	{
		if(SensorValue(sonarSensor) <= 75)
			{
				motor[motorL] = 75; // lego group x*y x=diamter, y=width
				motor[motorR] = 75;
		 	}
		else
			{
				motor[motorL] = 90;
				motor[motorR] = 0;
				wait1Msec(100);
				nMotorEncoder[motorL] = 0;
				nMotorEncoder[motorR] = 0;
				motor[motorL] = 75;
				motor[motorR] = 75;
				nMotorEncoderTarget[motorL] = 2122;
				nMotorEncoderTarget[motorR] = 2122;
			}
	}
task main()
	{
		startTask (sonarFunction);
		if (SensorValue(colorSensorA)>60 && SensorValue(colorSensorA) <65) // Don't know what color blue is. 60 I think?
		{
			motor[motorL] = 0;
			motor[motorR] = 0;
			startTask (leftparking);
		}
		else if (SensorValue(colorSensorB) > 55 && SensorValue(colorSensorB) <65)
		{
			motor[motorL] = 0;
			motor[motorR] = 0;
			startTask (rightparking);
		}
		else
		{
			motor[motorL] = 75; // I don't know normal speed of robot
			motor[motorR] = 75;
		}
	}
