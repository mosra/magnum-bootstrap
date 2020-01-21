

#include <gtkmm/application.h>
#include <gtkmm/glarea.h>


class MagnumWidget : public Gtk::GLArea {

public:


private:


};


int main(int argc, char **argv) {

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    return app->run();
}