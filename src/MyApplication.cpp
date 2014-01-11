#include <Magnum/Platform/GlutApplication.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera3D.h>
#include <Magnum/SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void drawEvent() override;

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

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    camera->draw(drawables);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
