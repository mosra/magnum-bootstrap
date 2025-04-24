#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/GLContext.h>

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/sizer.h>
#include <wx/version.h>

using namespace Magnum;

class MyApplication: public wxApp {
    public:
        bool OnInit();
};

class MainFrame: public wxFrame {
    public:
        explicit MainFrame(int argc, char** argv);
        ~MainFrame();

    private:
        void OnPaint(wxPaintEvent& event);

        wxGLCanvas* _wxGlCanvas;
        wxGLContext* _wxGlContext;
        Platform::GLContext _glContext;
};

wxIMPLEMENT_APP(MyApplication);

bool MyApplication::OnInit() {
    MainFrame *frame = new MainFrame{argc, argv};
    frame->Show(true);
    return true;
}

MainFrame::MainFrame(int argc, char** argv): wxFrame{nullptr, wxID_ANY, "Magnum wxWidgets Application"}, _glContext{NoCreate, argc, argv} {
    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer{wxVERTICAL};

    #if (wxMAJOR_VERSION == 3) && (wxMINOR_VERSION >= 1)
    wxGLAttributes attributes;
    attributes.PlatformDefaults()
              .BufferSize(24)
              .MinRGBA(8, 8, 8, 0)
              .Depth(24)
              .Stencil(0)
              .DoubleBuffer()
              .EndList();
    _wxGlCanvas = new wxGLCanvas{this, attributes, wxID_ANY, wxDefaultPosition, wxSize{800, 600}};
    #elif (wxMAJOR_VERSION == 3) && (wxMINOR_VERSION == 0)
    int attributes[] = { WX_GL_RGBA,
                         WX_GL_DOUBLEBUFFER,
                         WX_GL_DEPTH_SIZE, 24,
                         WX_GL_STENCIL_SIZE, 0,
                         0 };
    _wxGlCanvas = new wxGLCanvas{this, wxID_ANY, &attributes[0], wxDefaultPosition, wxSize{800, 600}};
    #else
    #error You need wxWidgets version 3.0 or later.
    #endif

    _wxGlContext = new wxGLContext{_wxGlCanvas};
    Show();
    _wxGlCanvas->SetCurrent(*_wxGlContext);
    _glContext.create();

    bSizer->Add(_wxGlCanvas, 1, wxALL|wxEXPAND, 5);
    SetSizer(bSizer);

    Layout();

    bSizer->Fit(this);

    Centre(wxBOTH);

    _wxGlCanvas->Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint), nullptr, this);

    /* TODO: Add your initialization code here */
}

MainFrame::~MainFrame() {
    _wxGlCanvas->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint), nullptr, this);
}

void MainFrame::OnPaint(wxPaintEvent&) {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your drawing code here */

    _wxGlCanvas->SwapBuffers();
}
