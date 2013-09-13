#include <Platform/GlutApplication.h>
#include <DefaultFramebuffer.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/MatrixTransformation2D.h>
#include <SceneGraph/Camera2D.h>
#include <SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation2D> Object2D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation2D> Scene2D;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    protected:
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;

    private:
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

void MyApplication::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
    camera->setViewport(size);
}

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    camera->draw(drawables);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
