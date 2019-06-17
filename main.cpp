#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/Stopwatch.hpp"
#include "Core/Scene.hpp"
#include "Core/BufferData.hpp"
#include "Core/ObjLoader.h"
#include "Core/render.hpp"

int main(int argc, char** argv)
{
    Window window;
    MeshManager meshManager;
    Stopwatch stopwatch;
    Scene scene;

    if(argc > 1)
        scene.loadArbitraryMesh(argv[1]);

    RenderingMode renderingMode = decideRenderingMode(argc, argv);
    
    std::unique_ptr<Drawer> drawer = getDrawer(renderingMode);
    
    drawer->setView(
        ViewData(
            Vector3(0.0f, 5.0f, 5.5f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f)
        )
    );

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
        drawer->updateShader();

        /*
        *   Render 
        */ 
        window.clear();
        scene.draw(drawer);
        window.swapBuffers();
    }

    return 0;
}

