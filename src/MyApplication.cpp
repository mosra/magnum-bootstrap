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

        make_current();
        _context.create();

    }

    bool onRender(const Glib::RefPtr<Gdk::GLContext>& context) {

        GL::Context::current().resetState(GL::Context::State::ExitExternal);


        GL::Context::current().resetState(GL::Context::State::EnterExternal);

        return true;
    }

    void onUnrealize() {

    }

private:

    Platform::GLContext& _context;

};


int main(int argc, char **argv) {

    Platform::GLContext context{NoCreate, argc, argv};

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    auto widget = MagnumWidget(context);
    auto window = Gtk::Window();
    window.add(widget);

    return app->run(window);
}