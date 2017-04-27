#include "GPIO_Controller.h"

#include <mcp3004.h>


GPIO_Controller::GPIO_Controller()
{
	mcp3004Setup(BaseChannel, Channel);
	MeanVal.resize(8);
	for (int i = 0; i < 8; i++)
	{
		MeanVal[i] = 0;
	}
}


GPIO_Controller::~GPIO_Controller()
{
	for (int i = 0; i < 8; i++)
	{
		DataPoints[i].clear();
	}
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

std::vector<double> GPIO_Controller::ReadAnalogData(int Channel)
{
	double NewVal = (1023.0 - analogRead(BaseChannel + Channel)) * 3.3 / 1023.0;
	double OldVal = 0.0;
	DataPoints[Channel].push_back(NewVal);
	if (DataPoints[Channel].size() > MaxListLength)
	{
		OldVal = DataPoints[Channel].front();
		DataPoints[Channel].pop_front();
	}
	// Possívelmente instável
	MeanVal[Channel] = MeanVal[Channel] - (OldVal * 300.0) + (NewVal * 300.0);
	return MeanVal;
}

/// Atualiza a média. Usadao para manter a estabilidade númerica
double GPIO_Controller::UpdateMeanValue(int Channel)
{
	if (DataPoints[Channel].size() > 0)
	{
		MeanVal[Channel] = 0.0;
		for (std::list<double>::iterator it = DataPoints[Channel].begin(); it != DataPoints[Channel].end(); ++it)
		{
			MeanVal[Channel] += *it;
		}
		MeanVal[Channel] = MeanVal[Channel] / DataPoints[Channel].size();
		return MeanVal[Channel];
	}
	return 0.0;
}

