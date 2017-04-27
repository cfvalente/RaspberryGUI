#pragma once
#include <gtkmm.h>
#include "GPIO_Controller.h"
#include <thread>
#include <vector>
#include <mutex>

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

	std::thread SensorThread;
	static bool Active;
	static std::mutex SensorMutex;
	static std::vector<double> SensorOutput;
	static void T_UpdateSensorData(int Channel, GPIO_Controller RaspberryGPIO);
	bool UpdateLabel();
};

