#pragma once
#include <gtkmm.h>
#include "GPIO_Controller.h"
#include <thread>
#include <vector>

class GUI : public Gtk::Window
{
public:
	GUI();
	~GUI();

protected:
	//Signal handlers:
	void OnRelayButtonClicked();

	//Member widgets:
	Gtk::Grid *Grid;
	Gtk::Label *Title;
	Gtk::ToggleButton *RelayButton;
	Gtk::Label *SensorData;

	GPIO_Controller RaspberryGPIO;

private:
	char *GenerateRelayLabelText(int RelayVal);
	static bool Active;
	std::thread SensorThread;

	static void T_UpdateSensorData(int Channel, Gtk::Label *Output, GPIO_Controller RaspberryGPIO);
	void UpdateLabel();
};

