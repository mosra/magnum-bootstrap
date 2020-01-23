
#include <Magnum/Platform/GLContext.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/glarea.h>

using namespace Magnum;

class MagnumWidget : public Gtk::GLArea {
public:
    explicit MagnumWidget(Platform::GLContext &context);

private:
    void onRealize();
    bool onRender(const Glib::RefPtr<Gdk::GLContext> &context);
    void onResize(int width, int height);
    void onUnrealize();

    Platform::GLContext &_context;
};

MagnumWidget::MagnumWidget(Platform::GLContext &context) : Gtk::GLArea(), _context(context) {

    /* Automatically re-render everything every time it needs to be drawn */
    set_auto_render();

    /* Set size requests and scaling behavior */
    set_hexpand();
    set_vexpand();
    set_halign(Gtk::ALIGN_FILL);
    set_valign(Gtk::ALIGN_FILL);
    set_size_request(500, 500);

    /* Set desired OpenGL version */
    set_required_version(4, 5);

    /* Connect signals to their respective handlers */
    signal_realize().connect(sigc::mem_fun(this, &MagnumWidget::onRealize));
    signal_render().connect(sigc::mem_fun(this, &MagnumWidget::onRender));
    signal_resize().connect(sigc::mem_fun(this, &MagnumWidget::onResize));
    signal_unrealize().connect(sigc::mem_fun(this, &MagnumWidget::onUnrealize));
}

void MagnumWidget::onRealize() {

    /* Make sure the OpenGL context is current then configure it */
    make_current();
    _context.create();

    /* TODO: Add your initialization code here */

}

bool MagnumWidget::onRender(const Glib::RefPtr<Gdk::GLContext> &context) {

    /* Retrieve the ID of the relevant framebuffer */
    GLint framebufferID;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebufferID);

    /* Attache Magnum's framebuffer manager to the framebuffer provided by Gtkmm */
    auto gtkmmDefaultFramebuffer = GL::Framebuffer::wrap(framebufferID, {{}, {get_width(), get_height()}});

    /* Reset state to avoid Gtkmm affecting Magnum */
    GL::Context::current().resetState(GL::Context::State::ExitExternal);

    /* Clear the frame */
    gtkmmDefaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your drawing code here */

    /* Clean up Magnum state and back to Gtkmm */
    GL::Context::current().resetState(GL::Context::State::EnterExternal);

    return true;
}

void MagnumWidget::onResize(int width, int height) {

    /* TODO: Add your window-resize handling code here */
}

void MagnumWidget::onUnrealize() {

    /* TODO: Add your clean-up code here */
}


int main(int argc, char **argv) {

    Platform::GLContext context{NoCreate, argc, argv};

    /* Create an application with a reasonable application ID */
    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    /* Create a window for the application */
    Gtk::Window window{};

    /* Create a graphics widget and add it to the window */
    MagnumWidget widget{context};
    window.add(widget);
    widget.show();

    /* Hand over control to Gtk */
    return app->run(window);
}
