#pragma once
#include <wiringPi.h>

class GPIO_Controller
{
public:
	GPIO_Controller();
	~GPIO_Controller();

	void ToggleRelay();
	int GetRelayPinVal();

private:
	int RelayPin = 17;
};

