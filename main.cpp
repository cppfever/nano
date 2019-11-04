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
//        ::glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
//        ::glfwWindowHint(GLFW_SAMPLES, 4);
//        ::glfwWindowHint(GLFW_RED_BITS, 8);
//        ::glfwWindowHint(GLFW_GREEN_BITS, 8);
//        ::glfwWindowHint(GLFW_BLUE_BITS, 8);
//        ::glfwWindowHint(GLFW_ALPHA_BITS, 8);

        mWindow = ::glfwCreateWindow(800, 600, "NanoVG Test", nullptr, nullptr);
        ::glViewport(0, 0, 800, 600);

        ::glfwMakeContextCurrent(mWindow);

        glewExperimental=GL_TRUE;

/////////////////////////////////////////////////////////////////////////////////////////
///GLEW MUST INITIALIZED ONLY IN THIS PLACE. AFTER 'glfwMakeContextCurrent' FUNCTION CALL
/////////////////////////////////////////////////////////////////////////////////////////
        if(::glewInit() != GLEW_OK)
            std::runtime_error("Could not init GLEW.");

        ::glClearColor(0.7, 0.7, 0.7, 0.5);
        mVG = ::nvgCreateGL2(NVG_STENCIL_STROKES | NVG_ANTIALIAS | NVG_DEBUG);

        mImage = ::nvgCreateImage(mVG, "icons/icon6.png", 0);
        int width = 0;
        int height = 0;
        ::nvgImageSize(mVG, mImage, &width, &height);


        ::glfwSetWindowUserPointer(mWindow, this);

        ::glfwSetWindowSizeCallback(mWindow,
            [](GLFWwindow *glfw_window, int width, int height)
        {
            ::glfwMakeContextCurrent(glfw_window);
            ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

            Window* window = Window::GetWindow(glfw_window);
            window->OnPaint();
        });

        ::glfwSetWindowRefreshCallback(mWindow,
            [](GLFWwindow *glfw_window)
        {
            ::glfwMakeContextCurrent(glfw_window);
            ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

            Window* window = Window::GetWindow(glfw_window);
            window->OnPaint();
        });

    }

    void Run()
    {
        while(!::glfwWindowShouldClose(mWindow))
        {
             ::glfwPollEvents();
        }
    }

    virtual void OnPaint()
    {
        int width, height;
        ::glfwGetFramebufferSize(mWindow, &width, &height);
        float ratio = float(width) / float(height);

        ::glViewport(0, 0, width, height);

        ::nvgBeginFrame(mVG, width, height, ratio);

        ::nvgBeginPath(mVG);
        NVGpaint paint = ::nvgImagePattern(mVG, 30.0f, 30.0f, float(width)-60.0f, float(height)-60.0f, 0.0f, mImage, 0.5f);
        ::nvgRoundedRect(mVG, 30.0f, 30.0f, float(width)-60.0f, float(height)-60.0f, 30.0f);
        ::nvgFillPaint(mVG, paint);
        ::nvgFill(mVG);

        ::nvgEndFrame(mVG);
        ::glfwSwapBuffers(mWindow);
    }

private:

    GLFWwindow* mWindow {nullptr};
    NVGcontext* mVG {nullptr};
    int mImage {0};

    static void ErrorCallback(int error, const char* desc)
    {
        std::cout << "GLFW error:" << desc << std::endl;
    }

    static Window* GetWindow(GLFWwindow* glfw_window)
    {
        return static_cast<Window*>(::glfwGetWindowUserPointer(glfw_window));
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
