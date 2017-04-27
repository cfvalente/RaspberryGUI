#pragma once
#include <wiringPi.h>
#include <list>
#include <vector>

class GPIO_Controller
{
public:
	GPIO_Controller();
	~GPIO_Controller();

	void ToggleRelay();
	int GetRelayPinVal();
	std::vector<double> ReadAnalogData(int Channel);
	double UpdateMeanValue(int Channel);


private:
	int RelayPin = 17;

	int BaseChannel = 100;
	int Channel = 0;
	unsigned int MaxListLength = 300;
	std::vector<double> MeanVal;

	std::list<double> DataPoints[8];
};

