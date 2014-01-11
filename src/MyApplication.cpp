#include <Magnum/Platform/WindowlessGlxApplication.h>

using namespace Magnum;

class MyApplication: public Platform::WindowlessApplication {
    public:
        explicit MyApplication(const Arguments& arguments);

        int exec() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::WindowlessApplication(arguments) {
    /* TODO: Add your initialization code here */
}

int MyApplication::exec() {
    /* TODO: Add your processing code here */
    return 0;
}

MAGNUM_WINDOWLESSAPPLICATION_MAIN(MyApplication)
