// LSI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Device.h"
#include <iostream>

int main()
{
	int stopSign = 0;
	int frequency = 200; //Hz
	double period = 1000 / (double)frequency; //in milliseconds
	double currentTime = 0.0;
	double startTime = 0.0;
	double lastTime = 0.0;
	int BEGIN = 0;
    
	Device Stapler;
	Stapler.sensor_status = 1;
	startTime = Stapler.getTime();
	// ------------------------- Recording the file -------------------------
	std::string fileName = std::to_string(Stapler.getTime());
	std::ofstream file("logs" + fileName + ".csv");

	while (stopSign == 0)
	{
		currentTime = (Stapler.getTime() - startTime);
		if (currentTime >= period + lastTime)
		{
			if (Stapler.sensor_status == 1) {
				Stapler.readNIdata();
				file << Stapler.data[0] << "," << Stapler.data[1] << "," << Stapler.data[2] << "," << Stapler.data[3] << "," << Stapler.data[4] << "," << Stapler.data[5];
			}
			file << std::endl;

			lastTime = currentTime;

			if (BEGIN == 0) {
				BEGIN = 1;
				Stapler.Flag = 0;
			}
		}
		if (currentTime > 200 * 1000) {
			Stapler.Flag = 0;
		}
	};

	return 0;
}
