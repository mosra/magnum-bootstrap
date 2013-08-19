#include <Platform/GlutApplication.h>
#include <DefaultFramebuffer.h>

using namespace Magnum;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    protected:
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application(arguments) {}

void MyApplication::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);
    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
