#include "pch.h"
#include "Device.h"


Device::Device()
{
	if (sensor_status == 1) {
		setupNIdevice();
	}
}


Device::~Device()
{
	//  ------------------------- Stopping and Clearing the DAQ -------------------------
	// close the configuration and device handles
	DAQmxStopTask(taskHandle_AI);
	DAQmxClearTask(taskHandle_AI);
}

void Device::setupNIdevice()
{
	/*********************************************/
// DAQmx Configure Code
	this->checkForErrors(DAQmxCreateTask("", &taskHandle_AI));
	this->checkForErrors(DAQmxCreateAIVoltageChan(taskHandle_AI, "Dev2/ai0:5", "Voltage", DAQmx_Val_Diff, -10.0, 10.0, DAQmx_Val_Volts, NULL));
	this->checkForErrors(DAQmxSetSampTimingType(taskHandle_AI, DAQmx_Val_OnDemand));
	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	this->checkForErrors(DAQmxStartTask(taskHandle_AI));
	/*********************************************/
}

void Device::readNIdata() 
{
	this->checkForErrors(DAQmxReadAnalogF64(taskHandle_AI, 1, 10.0, DAQmx_Val_GroupByChannel, data, 6, &read, NULL));
}

double Device::getTime()
{
	LARGE_INTEGER timeCounts, timeFrequency;
	QueryPerformanceCounter(&timeCounts);
	QueryPerformanceFrequency(&timeFrequency);
	return double(timeCounts.QuadPart) / double(timeFrequency.QuadPart) * 1000;
}

void Device::checkForErrors(int32 error)
{
	if (DAQmxFailed(error))
		//DAQmxGetExtendedErrorInfo(errBuff, 2048);
		if (taskHandle_AI != 0) {
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(taskHandle_AI);
			DAQmxClearTask(taskHandle_AI);
		}
	if (DAQmxFailed(error)) {
		DAQmxStopTask(taskHandle_AI);
		DAQmxClearTask(taskHandle_AI);
		//printf("DAQmx Error: %s\n", errBuff);
		printf("DAQmx Error\n");
		printf("End of program, press Enter key to quit\n");
		getchar();
	}

}
