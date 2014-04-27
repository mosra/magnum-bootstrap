#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation2D.h>
#include <Magnum/SceneGraph/Camera2D.h>
#include <Magnum/SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation2D> Object2D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation2D> Scene2D;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void drawEvent() override;

        Scene2D scene;
        Object2D* cameraObject;
        SceneGraph::Camera2D* camera;
        SceneGraph::DrawableGroup2D drawables;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application(arguments) {
    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new SceneGraph::Camera2D(*cameraObject);
    camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjection({4.0f/3.0f, 1.0f})
        .setViewport(defaultFramebuffer.viewport().size());

    /* TODO: Prepare your objects here and add them to the scene */
}

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    camera->draw(drawables);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
