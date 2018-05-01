#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation2D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation2D> Object2D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation2D> Scene2D;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void drawEvent() override;

        Scene2D _scene;
        Object2D* _cameraObject;
        SceneGraph::Camera2D* _camera;
        SceneGraph::DrawableGroup2D _drawables;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application{arguments} {
    /* Configure camera */
    _cameraObject = new Object2D{&_scene};
    _camera = new SceneGraph::Camera2D{*_cameraObject};
    _camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix3::projection({4.0f/3.0f, 1.0f}))
        .setViewport(GL::defaultFramebuffer.viewport().size());

    /* TODO: Prepare your objects here and add them to the scene */
}

void MyApplication::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    _camera->draw(_drawables);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
