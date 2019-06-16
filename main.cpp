#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/Stopwatch.hpp"
#include "Core/Scene.hpp"
#include "Core/BufferData.hpp"
#include "Core/ObjLoader.h"

int main(int argc, char** argv)
{
    Window window;
    Drawer drawer;
    MeshManager meshManager;
    Stopwatch stopwatch;
    Scene scene;
    drawer.setView(
        ViewData(
            Vector3(0.0f, 5.0f, 5.5f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f)
        )
    );

    if(argc > 1)
    {   
        ObjLoader loader(argv[1]);
        std::shared_ptr<BufferData> pObject = std::make_shared<BufferData>(loader.getData());
        std::shared_ptr<Drawable> pDrawable = std::make_shared<Drawable>(pObject);
        scene.addDrawable(pDrawable);
    }

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        /*
         *  Input 
         */ 
        double dtSeconds = (double)(stopwatch.elapsed_time<int, std::chrono::microseconds>()) / 1000000;
        stopwatch.restart();

        window.processInput();
        window.processCameraInput(drawer, dtSeconds);
        window.pollEvents();

        /*
         *  Update
         */ 
        drawer.updateShader();

        /*
        *   Render 
        */ 
        window.clear();
        scene.draw(drawer);
        window.swapBuffers();
    }

    return 0;
}

