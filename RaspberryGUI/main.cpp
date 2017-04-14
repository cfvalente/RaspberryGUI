#include "GUI.h"



int main(int argc, char *argv[])
{


	auto app = Gtk::Application::create(argc, argv, "Rasp.GPIO");
	GUI window;
	return app->run(window);
}