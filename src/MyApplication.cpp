#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/TimeStl.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Ui/Application.h>
#include <Magnum/Ui/Theme.h>
#include <Magnum/Ui/UserInterfaceGL.h>

using namespace Magnum;

namespace {

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void viewportEvent(ViewportEvent& event) override;
        void drawEvent() override;
        void pointerPressEvent(PointerEvent& event) override;
        void pointerReleaseEvent(PointerEvent& event) override;
        void pointerMoveEvent(PointerMoveEvent& event) override;
        void scrollEvent(ScrollEvent& event) override;
        void keyPressEvent(KeyEvent& event) override;
        void keyReleaseEvent(KeyEvent& event) override;
        void textInputEvent(TextInputEvent& event) override;

        Ui::UserInterfaceGL _ui;
};

Nanoseconds now() {
    return Nanoseconds{std::chrono::steady_clock::now()};
}

MyApplication::MyApplication(const Arguments& arguments):
    Platform::Application{arguments, Configuration{}
        .addWindowFlags(Configuration::WindowFlag::Resizable)},
    _ui{*this, Ui::DarkTheme{Ui::DarkTheme::Feature::Animations}}
{
    /* UI requires premultiplied alpha */
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::One,
                                   GL::Renderer::BlendFunction::OneMinusSourceAlpha);

    /* TODO: Add your UI and other initialization code here */
}

void MyApplication::viewportEvent(ViewportEvent& event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    _ui.setSize(event);
}

void MyApplication::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your other drawing code here, if any */

    _ui
        .advanceAnimations(now())
        .draw();

    swapBuffers();
    if(_ui.state())
        redraw();
}

void MyApplication::pointerPressEvent(PointerEvent& event) {
    _ui.pointerPressEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::pointerReleaseEvent(PointerEvent& event) {
    _ui.pointerReleaseEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::pointerMoveEvent(PointerMoveEvent& event) {
    _ui.pointerMoveEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::scrollEvent(ScrollEvent& event) {
    _ui.scrollEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::keyPressEvent(KeyEvent& event) {
    _ui.keyPressEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::keyReleaseEvent(KeyEvent& event) {
    _ui.keyReleaseEvent(event, now());

    if(_ui.state())
        redraw();
}

void MyApplication::textInputEvent(TextInputEvent& event) {
    _ui.textInputEvent(event, now());

    if(_ui.state())
        redraw();
}

}

MAGNUM_APPLICATION_MAIN(MyApplication)
