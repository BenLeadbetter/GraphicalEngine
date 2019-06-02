#ifndef GUARD_WINDOW_HPP
#define GUARD_WINDOW_HPP

/*
*
*   Header file for the Window class 
*
*   This class will be responsible for creating and managing
*   the application window using the GLFW (GLFramework).
*
*   It will manage state of the GL state machine through 
*   simple interface calls.
*
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Drawable.hpp"
#include "Stopwatch.hpp"

class Window
{
    
    private:

        // GL Interface
        void initializeGLFW() const;
        void loadGLAD() const;
        void createWindow();
    
    public:

        //
        Window();
        ~Window();

        // deleted functions
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        //
        bool shouldClose() const;
        void processInput() const;
        void swapBuffers() const;
        void pollEvents() const;
        void clear() const;
        float elapsedTimeInMilliseconds() const;
    
    private:
        
        GLFWwindow* window;
        Stopwatch stopwatch;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif