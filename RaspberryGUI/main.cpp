#include "GUI.h"
#include <wiringPi.h>

int main(int argc, char *argv[])
{
	wiringPiSetupGpio();
	auto app = Gtk::Application::create(argc, argv, "Rasp.GPIO");
	GUI window;
	return app->run(window);
}