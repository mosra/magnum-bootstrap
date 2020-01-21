#include <Magnum/GL/Framebuffer.h>
#include <Magnum/Platform/GLContext.h>

#include <gtkmm/application.h>
#include <gtkmm/glarea.h>
#include <gtkmm/window.h>

using namespace Magnum;

class MagnumWidget : public Gtk::GLArea {

public:

    explicit MagnumWidget(Platform::GLContext& context) : Gtk::GLArea(), _context(context) {

        set_size_request(1024, 1024);

        signal_realize().connect(sigc::mem_fun(this, &MagnumWidget::onRealize));
        signal_render().connect(sigc::mem_fun(this, &MagnumWidget::onRender));
        signal_unrealize().connect(sigc::mem_fun(this, &MagnumWidget::onUnrealize));
    }


protected:

    void onRealize() {

    }

    bool onRender(const Glib::RefPtr<Gdk::GLContext>& context) {

    }

    void onUnrealize() {

    }

private:

    Platform::GLContext& _context;

};


int main(int argc, char **argv) {

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    auto widget = MagnumWidget();
    auto window = Gtk::Window();
    window.add(widget);

    return app->run(window);
}