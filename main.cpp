// #define CATCH_CONFIG_MAIN
// #include <catch.hpp>

#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"
#include "Core/Particle.hpp"

#include "Core/Stopwatch.hpp"

#include <cmath>
#include <unistd.h>

#include <iostream>

int main()
{
    /*
    *   Try out our new classes
    */
    Window window;
    Drawer drawer;
    MeshManager meshManager;

    
    Drawable stage(meshManager.getMesh(MeshID::CUBE));
    stage.setRenderMode(RenderMode::LINE);
    stage.scale(10.0f); 
    


    // test a particle
    Particle testParticle(meshManager);
    testParticle.setVelocity(Vector3(3.2f, 3.1f, -5.8f));
    testParticle.setRadius(0.4f);
    testParticle.setRenderMode(RenderMode::LINE);
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
        
            
        drawer.setView(
            ViewData(
                glm::vec3(5.0 * std::sin((float)glfwGetTime()), 5.0 * std::cos((float)glfwGetTime()), 3.5f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
            )
        );
        drawer.updateShader();
        /*
        *   Render 
        */ 

        window.clear();
        drawer.draw(testParticle);
        drawer.draw(stage);
        window.swapBuffers();
    }

    return 0;
}

