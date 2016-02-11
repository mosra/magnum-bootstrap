#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

using namespace Magnum;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application{arguments,
    Configuration{}.setWindowFlags(Configuration::WindowFlag::Resizable
        #ifdef CORRADE_TARGET_IOS
        |Configuration::WindowFlag::Borderless|Configuration::WindowFlag::AllowHighDpi
        #endif
    )}
{
    /* TODO: Add your initialization code here */
}

void MyApplication::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    /* TODO: Add your drawing code here */

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
