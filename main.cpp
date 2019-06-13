#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"
#include "Core/Particle.hpp"

#include "Core/Stopwatch.hpp"

#include <cmath>


long unsigned int tickCount = 0;

int main()
{
    /*
    *   Try out our new classes
    */
    Window window;
    Drawer drawer;
    MeshManager meshManager;

    // test out a stopwatch
    Stopwatch stopwatch;
    
    Drawable stage(meshManager.getMesh(MeshID::CUBE));
    stage.setRenderMode(RenderMode::LINE);
    stage.scale(8.0f); 
    

    
    // test a particle
    Particle testParticle(meshManager);
    testParticle.setVelocity(Vector3(0.2f, 0.1f, -0.8f));
    testParticle.setRadius(0.4f);
    testParticle.setRenderMode(RenderMode::FILL);
    testParticle.scale(0.5f);
    

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        /*
         *  Input 
         */ 
        
        window.processInput();
        window.pollEvents();

        /*
         *  Update
         */ 
        double dtSeconds = (double)(stopwatch.elapsed_time<int, std::chrono::microseconds>()) / 1000000;
        stopwatch.restart();

        testParticle.update(dtSeconds);
            
        drawer.setView(
            ViewData(
                Vector3((5.0f * std::sin((float)glfwGetTime())), 5.0f * std::cos((float)glfwGetTime()), 3.5f),
                Vector3(0.0f, 0.0f, 0.0f),
                Vector3(0.0f, 0.0f, 1.0f)
            )
        );

        drawer.updateShader();
        /*
        *   Render 
        */ 

        window.clear();
        drawer.draw(stage);
        drawer.draw(testParticle);
        window.swapBuffers();
    }

    return 0;
}

