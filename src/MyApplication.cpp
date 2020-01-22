#include <Magnum/GL/Framebuffer.h>
#include <Magnum/Platform/GLContext.h>
#include <Magnum/Math/Color.h>

#include <gtkmm/application.h>
#include <gtkmm/glarea.h>
#include <gtkmm/window.h>

using namespace Magnum;

class MagnumWidget : public Gtk::GLArea {

public:

    explicit MagnumWidget(Platform::GLContext& context) : Gtk::GLArea(), _context(context) {

        set_auto_render();
        set_size_request(1024, 1024);

        signal_realize().connect(sigc::mem_fun(this, &MagnumWidget::onRealize));
        signal_render().connect(sigc::mem_fun(this, &MagnumWidget::onRender));
        signal_unrealize().connect(sigc::mem_fun(this, &MagnumWidget::onUnrealize));
    }


protected:

    void onRealize() {
        _context.create();

    }

    bool onRender(const Glib::RefPtr<Gdk::GLContext>& context) {


        GL::Context::current().resetState(GL::Context::State::ExitExternal);
        {

            // FIXME How do I get the default framebuffer ID?
            auto gtkmmDefaultFramebuffer = GL::Framebuffer::wrap(0, {{}, {get_width(), get_height()}});


            gtkmmDefaultFramebuffer.clearColor(0, Color4{0, 0.5, 1, 1});

            gtkmmDefaultFramebuffer
                    .clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth)
                    .bind();
        }
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