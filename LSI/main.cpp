// LSI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Device.h"
#include <iostream>

void main()
{
	int stopSign = 0;
	int frequency = 200; //Hz
	double period = 1000 / (double)frequency; //in milliseconds
	double currentTime = 0.0;
	double startTime = 0.0;
	double lastTime = 0.0;
	double push_button_v = 0.0;
	double button_high = 4.5;
	double button_low = 2.0;
	bool button_on;
	bool output=true;
	int BEGIN = 0;

	Device Stapler;
	Stapler.sensor_status = 1;
	std::cout << "Stapler initialized\n";
	startTime = Stapler.getTime();
	// ------------------------- Recording the file -------------------------
	std::string fileName = std::to_string(Stapler.getTime());
	std::ofstream file("logs" + fileName + ".csv");

	if (output > 4.5) {
		output == true;
	}
	else if (output < 2.0) {
		output == false;
	}

	while (stopSign == 0)
	{
		currentTime = (Stapler.getTime() - startTime);
		if (currentTime >= period + lastTime)
		{
			if (Stapler.sensor_status == 1) {
				Stapler.readNIdata();
				file << Stapler.data[0] << "," << Stapler.data[1] << "," << Stapler.data[2] << "," << Stapler.data[3] << "," << Stapler.data[4] << "," << Stapler.data[5];


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
		}
		


		push_button_v = Stapler.data[0];
		if (push_button_v > button_high) {
			button_on = true;
			if (output) {
				std::cout << "Button On" << std::endl;
				output = false;
			}
		}

		if (push_button_v < button_low) {
			button_on = false;
			if (!output) {
				std::cout << "Button Off" << std::endl;
				output = true;

			}
			
		}
		
	}

}