#include <Magnum/GL/Framebuffer.h>
#include <Magnum/Platform/GLContext.h>
#include <Magnum/Math/Color.h>

#include <gtkmm/application.h>
#include <gtkmm/glarea.h>
#include <gtkmm/window.h>

using namespace Magnum;

class MagnumWidget : public Gtk::GLArea {

public:

    explicit MagnumWidget(Platform::GLContext &context) : Gtk::GLArea(), _context(context) {

        /* This widget will re-render everything every time it needs to be drawn */
        set_auto_render();

        /* Setting size requests and scaling behavior */
        set_hexpand();
        set_vexpand();
        set_halign(Gtk::ALIGN_FILL);
        set_valign(Gtk::ALIGN_FILL);
        set_size_request(1024, 1024);

        /* Setting desired OpenGL version */
        set_required_version(4, 6);

        /* Connecting signals to their respective handlers */
        signal_realize().connect(sigc::mem_fun(this, &MagnumWidget::onRealize));
        signal_render().connect(sigc::mem_fun(this, &MagnumWidget::onRender));
        signal_unrealize().connect(sigc::mem_fun(this, &MagnumWidget::onUnrealize));
    }


protected:

    void onRealize() {
        _context.create();

        /* TODO: Add your initialization code here */

    }

    bool onRender(const Glib::RefPtr<Gdk::GLContext> &context) {

        /* Reset state to avoid Gtkmm affecting Magnum */
        GL::Context::current().resetState(GL::Context::State::ExitExternal);

        /* FIXME: How do I get the default framebuffer ID? */
        auto gtkmmDefaultFramebuffer = GL::Framebuffer::wrap(0, {{}, {get_width(), get_height()}});

        gtkmmDefaultFramebuffer.clear(GL::FramebufferClear::Color);

        /* TODO: Add your drawing code here */

        /* Clean up Magnum state and back to Gtkmm */
        GL::Context::current().resetState(GL::Context::State::EnterExternal);

        return true;
    }

    void onUnrealize() {

        /* TODO Clean up here */
    }

private:

    Platform::GLContext &_context;

};


int main(int argc, char **argv) {

    Platform::GLContext context{NoCreate, argc, argv};

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    auto widget = MagnumWidget(context);
    auto window = Gtk::Window();
    window.add(widget);

    return app->run(window);
}