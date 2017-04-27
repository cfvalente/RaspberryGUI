#include <iostream>
#include <string>
#include <sstream>

#include "GUI.h"

bool GUI::Active = false;
std::vector<double> GUI::SensorOutput;
std::mutex GUI::SensorMutex;



GUI::GUI()
{
	set_title("Raspberry GPIO Controller");
	set_border_width(12);
	set_default_size(1280, 1024);

	Grid = new Gtk::Grid();
	Grid->set_row_homogeneous(true);
	Grid->set_column_homogeneous(true);

	Title = new Gtk::Label("Raspberry GPIO Controller", Gtk::Align::ALIGN_CENTER, Gtk::Align::ALIGN_CENTER);

	RelayButton = new Gtk::ToggleButton();
	RelayButton->set_label(GenerateRelayLabelText(RaspberryGPIO.GetRelayPinVal()));
	RelayButton->signal_clicked().connect(sigc::mem_fun(*this, &GUI::OnRelayButtonClicked));

	SensorData = new Gtk::Label("Not Initialized", Gtk::Align::ALIGN_CENTER, Gtk::Align::ALIGN_CENTER);


	Grid->attach(*Title, 0, 0, 2, 1);
	Grid->attach(*RelayButton, 0, 1, 1, 1);
	Grid->attach(*SensorData, 1, 1, 1, 1);
	add(*Grid);


	Grid->show_all();

	//sigc::slot<bool> Slot = sigc::bind(sigc::mem_fun(*this, &GUI::UpdateLabel), 1000);
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &GUI::UpdateLabel), 1000);
	//Glib::signal_timeout().bind(sigc::mem_fun(*this, &GUI::UpdateLabel), 1000);
	//sigc::connection  Glib::SignalIdle::connect(const sigc::slot<bool>& slot, int priority = Glib::PRIORITY_DEFAULT_IDLE);


	SensorThread = std::thread(GUI::T_UpdateSensorData, 0, RaspberryGPIO);
}


GUI::~GUI()
{
	delete Grid;
	delete Title;
	delete RelayButton;
	if (Active)
	{
		Active = false;
		SensorThread.join();
	}
}

void GUI::OnRelayButtonClicked()
{
	RaspberryGPIO.ToggleRelay();
	RelayButton->set_label(GenerateRelayLabelText(RaspberryGPIO.GetRelayPinVal()));
}

char * GUI::GenerateRelayLabelText(int RelayVal)
{
	if (RelayVal)
	{
		return (char *)"Deactivate Relay";
	}
	return (char *)"Activate Relay";
}

void GUI::T_UpdateSensorData(int Channel, GPIO_Controller RaspberryGPIO)
{
	Active = true;
	while (Active)
	{
		SensorMutex.lock();
		SensorOutput = RaspberryGPIO.ReadAnalogData(Channel);
		SensorMutex.unlock();
		delay(10);
	}
}

bool GUI::UpdateLabel()
{
	SensorMutex.lock();
	double Val = SensorOutput[0];

	std::ostringstream strs;
	strs.precision(6);
	strs << Val << "V\n";
	std::string str = strs.str();

	SensorData->set_label(str);
	SensorMutex.unlock();
	return true;
}