#include "GPIO_Controller.h"



GPIO_Controller::GPIO_Controller()
{
	wiringPiSetupGpio();
}


GPIO_Controller::~GPIO_Controller()
{
}

void GPIO_Controller::ToggleRelay()
{
	digitalWrite(RelayPin, 1 - digitalRead(RelayPin));
	return;
}

int GPIO_Controller::GetRelayPinVal()
{
	return digitalRead(RelayPin);
}


