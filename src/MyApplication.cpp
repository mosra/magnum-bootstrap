#include <Platform/GlutApplication.h>
#include <DefaultFramebuffer.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/MatrixTransformation3D.h>
#include <SceneGraph/Camera3D.h>
#include <SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    protected:
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;

    private:
        Scene3D scene;
        Object3D* cameraObject;
        SceneGraph::Camera3D* camera;
        SceneGraph::DrawableGroup3D drawables;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application(arguments) {
    /* Configure camera */
    cameraObject = new Object3D(&scene);
    cameraObject->translate(Vector3::zAxis(-5.0f));
    camera = new SceneGraph::Camera3D(*cameraObject);
    camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setPerspective(35.0_degf, 4.0f/3.0f, 0.001f, 100.0f)
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
