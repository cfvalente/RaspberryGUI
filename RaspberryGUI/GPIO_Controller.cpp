#include "GPIO_Controller.h"



GPIO_Controller::GPIO_Controller()
{
}


GPIO_Controller::~GPIO_Controller()
{
}

void GPIO_Controller::ToggleRelay()
{
	int CurrentValue = digitalRead(RelayPin);
	digitalWrite(RelayPin, 1 - CurrentValue);
	return;
}

int GPIO_Controller::GetRelayPinVal()
{
	return digitalRead(RelayPin);
}


