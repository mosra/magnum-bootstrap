#include <Corrade/Corrade.h>

#ifdef CORRADE_TARGET_APPLE
#include <Magnum/Platform/WindowlessCglApplication.h>
#elif defined(CORRADE_TARGET_UNIX)
#include <Magnum/Platform/WindowlessGlxApplication.h>
#elif defined(CORRADE_TARGET_WINDOWS)
#include <Magnum/Platform/WindowlessWglApplication.h>
#else
#error No windowless application available on this platform
#endif

using namespace Magnum;

class MyApplication: public Platform::WindowlessApplication {
    public:
        explicit MyApplication(const Arguments& arguments);

        int exec() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::WindowlessApplication{arguments} {
    /* TODO: Add your initialization code here */
}

int MyApplication::exec() {
    /* TODO: Add your processing code here */
    return 0;
}

MAGNUM_WINDOWLESSAPPLICATION_MAIN(MyApplication)
