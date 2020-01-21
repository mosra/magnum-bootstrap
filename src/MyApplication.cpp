

#include <gtkmm/application.h>


int main(int argc, char **argv) {

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    return app->run();
}