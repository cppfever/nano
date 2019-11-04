#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NANOVG_GL2_IMPLEMENTATION
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>


using namespace std;


class Window
{
public:

    Window()
    {
        if(!::glfwInit())
            std::runtime_error("Could not init GLFW.");

        ::glfwSetErrorCallback(ErrorCallback);

        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        ::glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        ::glfwWindowHint(GLFW_SAMPLES, 4);

        mWindow = ::glfwCreateWindow(800, 600, "NanoVG Test", nullptr, nullptr);
        ::glViewport(0, 0, 800, 600);

        ::glfwMakeContextCurrent(mWindow);

        glewExperimental=GL_TRUE;

/////////////////////////////////////////////////////////////////////////////////////////
///GLEW MUST INITIALIZED ONLY IN THIS PLACE. AFTER 'glfwMakeContextCurrent' FUNCTION CALL
/////////////////////////////////////////////////////////////////////////////////////////
        if(::glewInit() != GLEW_OK)
            std::runtime_error("Could not init GLEW.");

        mVG = ::nvgCreateGL2(NVG_STENCIL_STROKES | NVG_ANTIALIAS | NVG_DEBUG);
        mImage = ::nvgCreateImage(mVG, "icons/icon1.png", 0);


    }

    void Run()
    {
        while(!::glfwWindowShouldClose(mWindow))
        {
             ::glfwPollEvents();
        }
    }

private:

    GLFWwindow* mWindow;
    NVGcontext* mVG;
    int mImage;

    static void ErrorCallback(int error, const char* desc)
    {
        std::cout << "GLFW error:" << desc << std::endl;
    }

};

int main()
{
    try
    {
        Window window;
        window.Run();
    }
    catch(...)
    {
        std::cout << "Some NANO troubles ..." << std::endl;
    }


    return 0;
}
