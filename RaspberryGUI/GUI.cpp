#include <iostream>
#include "GUI.h"

GUI::GUI()
{
	RelayButton = new Gtk::Button(GenerateRelayLabelText(RaspberryGPIO.GetRelayPinVal()));
	set_border_width(10);
	RelayButton->signal_clicked().connect(sigc::mem_fun(*this, &GUI::OnRelayButtonClicked));

	// This packs the button into the Window (a container).
	add(*RelayButton);
	// The final step is to display this newly created widget...
	RelayButton->show();
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
		return "Deactivate Relay";
	}
	return "Activate Relay";
}
