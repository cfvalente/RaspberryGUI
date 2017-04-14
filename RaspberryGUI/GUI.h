#pragma once
#include <gtkmm.h>
#include "GPIO_Controller.h"


class GUI : public Gtk::Window
{
public:
	GUI();
	~GUI();

protected:
	//Signal handlers:
	void OnRelayButtonClicked();

	//Member widgets:
	Gtk::Button *RelayButton;
	//Gtk::Button m_button; // Usando lista de construtores

	GPIO_Controller RaspberryGPIO;

private:
	char *GenerateRelayLabelText(int RelayVal);
};

