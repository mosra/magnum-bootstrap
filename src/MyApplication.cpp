#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Platform/GLContext.h>
#include <Magnum/Math/Color.h>

#include <gtkmm/application.h>
#include <gtkmm/glarea.h>
#include <gtkmm/window.h>


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

    /* This widget will re-render everything every time it needs to be drawn */
    set_auto_render();

    /* Setting size requests and scaling behavior */
    set_hexpand();
    set_vexpand();
    set_halign(Gtk::ALIGN_FILL);
    set_valign(Gtk::ALIGN_FILL);
    set_size_request(500, 500);

    /* Setting desired OpenGL version */
    set_required_version(4, 5);

    /* Connecting signals to their respective handlers */
    signal_realize().connect(sigc::mem_fun(this, &MagnumWidget::onRealize));
    signal_render().connect(sigc::mem_fun(this, &MagnumWidget::onRender));
    signal_resize().connect(sigc::mem_fun(this, &MagnumWidget::onResize));
    signal_unrealize().connect(sigc::mem_fun(this, &MagnumWidget::onUnrealize));
}

void MagnumWidget::onRealize() {

    /* Makes sure the OpenGL context is current before configuring it */
    make_current();
    _context.create();

    /* TODO: Add your initialization code here */

}

bool MagnumWidget::onRender(const Glib::RefPtr<Gdk::GLContext> &context) {

    /* Retrieves the ID of the relevant framebuffer */
    GLint framebufferID;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebufferID);

    /* Attaches Magnum's framebuffer manager to the framebuffer provided by Gtkmm */
    auto gtkmmDefaultFramebuffer = GL::Framebuffer::wrap(framebufferID, {{}, {get_width(), get_height()}});

    /* Reset state to avoid Gtkmm affecting Magnum */
    GL::Context::current().resetState(GL::Context::State::ExitExternal);

    /* Clears the frame */
    GL::Renderer::setClearColor(Color4{0.5, 0, 0, 1});
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

    auto app = Gtk::Application::create(argc, argv, "graphics.magnum.bootstrap.base-gtkmm");

    auto widget = MagnumWidget(context);
    auto window = Gtk::Window();
    window.add(widget);

    window.show_all_children();

    return app->run(window);
}