#include <iostream>
#include "GUI.h"

GUI::GUI()
{
	set_title("Raspberry GPIO Controller");
	set_border_width(12);

	Grid = new Gtk::Grid();
	Grid->set_row_homogeneous(true);
	Grid->set_column_homogeneous(true);

	Title = new Gtk::Label("Raspberry GPIO Controller", Gtk::Align::ALIGN_CENTER, Gtk::Align::ALIGN_CENTER);

	RelayButton = new Gtk::Button(GenerateRelayLabelText(RaspberryGPIO.GetRelayPinVal()));
	RelayButton->signal_clicked().connect(sigc::mem_fun(*this, &GUI::OnRelayButtonClicked));

	Grid->attach(*Title, 0, 0, 2, 1);
	Grid->attach(*RelayButton, 0, 1, 1, 1);

	add(*Grid);


	Grid->show_all();
}


GUI::~GUI()
{
	delete RelayButton;
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
