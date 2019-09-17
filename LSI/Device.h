#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Windows.h" 
#include <string>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <conio.h>

//NIDAQmx functionality:
#include "NIDAQmx.h"

class Device
{
public:
	Device();
	~Device();

	void setupNIdevice();
	void readNIdata();
	double getTime();

	int sensor_status = 1;
	TaskHandle  taskHandle_AI = 0;
	int32       read;
	float64     data[6];

	INT32     pos_motor_1;
	INT32     pos_motor_2;
	DOUBLE    vel_motor_1;
	DOUBLE    vel_motor_2;
	DOUBLE    acc_motor_1;
	DOUBLE    acc_motor_2;
	INT16     torque_motor_1;
	INT16     torque_motor_2;
	INT16	  Flag;

protected:
	void checkForErrors(int32 error);
};

