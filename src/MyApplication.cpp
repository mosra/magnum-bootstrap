#include <Corrade/Containers/Optional.h>
/* Magnum GL headers always have to be included before Qt ones */
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/Platform/GLContext.h>

/* If your application is using anything from QtGui, you might get warnings
   about GLEW and errors regarding GLclampf. If that's the case, uncomment the
   following and place it as early as possible (but again *after* including
   Magnum GL headers) */
#if 0
typedef GLfloat GLclampf;
#undef __glew_h__ /* shh, Qt, shh */
#undef __GLEW_H__
#include <QtGui/qopenglfunctions.h>
#endif

#include <QtWidgets/QApplication>
#include <QtWidgets/QOpenGLWidget>

using namespace Magnum;

class MyApplication: public QOpenGLWidget {
    public:
        explicit MyApplication(Platform::GLContext& context, QWidget* parent = nullptr, Qt::WindowFlags f = nullptr);

    private:
        void initializeGL() override;
        void paintGL() override;

        Platform::GLContext& _context;
};

MyApplication::MyApplication(Platform::GLContext& context, QWidget* parent, Qt::WindowFlags f): QOpenGLWidget{parent, f}, _context(context) {
    /* TODO: Add your context format setup code here */
}

void MyApplication::initializeGL() {
    _context.create();

    /* TODO: Add your initialization code here */

    /* Clean up Magnum state when giving control back to Qt */
    GL::Context::current().resetState(GL::Context::State::EnterExternal);
}

void MyApplication::paintGL() {
    /* Reset state to avoid Qt affecting Magnum */
    GL::Context::current().resetState(GL::Context::State::ExitExternal);

    /* Using framebuffer provided by Qt as default framebuffer */
    auto qtDefaultFramebuffer = GL::Framebuffer::wrap(defaultFramebufferObject(), {{}, {width(), height()}});

    qtDefaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your drawing code here */

    /* Clean up Magnum state when giving control back to Qt */
    GL::Context::current().resetState(GL::Context::State::EnterExternal);
}

int main(int argc, char** argv) {
    Platform::GLContext context{NoCreate, argc, argv};
    QApplication app{argc, argv};

    MyApplication w{context};

    /* On macOS, this is needed in order to use GL 4.1 instead of GL 2.1. Qt
       doesn't do that on its own, sorry. If you get only GL 3.0 on Mesa, try
       uncommenting this as well -- however be aware that with the below code,
       AMD and NVidia GPUs will get stuck at the version that's specified in
       setVersion() (such as 4.1) instead of using the latest available (4.6).
       To fix that, you'd need to detect the driver used and then either set
       the version or not depending on what the particular driver likes best.
       It's a total mess, right? */
    #ifdef CORRADE_TARGET_APPLE
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    w.setFormat(format);
    #endif

    w.show();

    return app.exec();
}
