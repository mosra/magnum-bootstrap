/* Magnum GL headers must always be included before Qt ones */
#include <Magnum/OpenGL.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Context.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QOpenGLWidget>

using namespace Magnum;

class MyApplication: public QOpenGLWidget {
    public:
        explicit MyApplication(QWidget* parent = nullptr, Qt::WindowFlags f = 0);

    private:
        void initializeGL() override;
        void paintGL() override;

        std::optional<Platform::Context> _context;
};

MyApplication::MyApplication(QWidget* parent, Qt::WindowFlags f): QOpenGLWidget{parent, f} {
    /* TODO: Add your context format setup code here */
}

void MyApplication::initializeGL() {
    _context = Platform::Context{};

    /* TODO: Add your initialization code here */
}

void MyApplication::paintGL() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    /* TODO: Add your drawing code here */
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MyApplication w;
    w.show();

    return app.exec();
}
