#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"
#include "Core/Particle.hpp"
#include "Core/CollisionBox.hpp"
#include "Core/Stopwatch.hpp"
#include "Core/Scene.hpp"

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
    
    std::unique_ptr<CollisionBox> pCollisionBox = std::make_unique<CollisionBox>(meshManager);
    

    
    // test some particles
    
    Particle particle1(meshManager);
    particle1.setVelocity(Vector3(0.2f, 0.1f, -0.8f));
    particle1.setRenderMode(RenderMode::FILL);
    particle1.scale(0.5f);

    Particle particle2(meshManager);
    particle2.setVelocity(Vector3(0.2f, 0.1f, -0.8f));
    particle2.setRenderMode(RenderMode::FILL);
    particle2.scale(0.5f);
    particle2.setDisplaceMent(Vector3(-3.0f, 3.0f, 0.0f));
    particle2.setColor(Vector3(0.0f, 0.0f, 1.0f));
    
    Particle particle3(meshManager);
    particle3.setVelocity(Vector3(0.2f, 0.1f, -0.8f));
    particle3.setRenderMode(RenderMode::FILL);
    particle3.scale(0.5f);
    particle3.setDisplaceMent(Vector3(2.0f, -2.0f, -2.0f));
    particle3.setColor(Vector3(0.0f, 1.0f, 0.0f));
    

    Scene scene;
    scene.addDrawable(std::move(pCollisionBox));
    scene.addDrawable(std::make_unique<Particle>(std::move(particle1)));
    scene.addDrawable(std::make_unique<Particle>(std::move(particle2)));
    scene.addDrawable(std::make_unique<Particle>(std::move(particle3)));

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
        scene.draw(drawer);
        window.swapBuffers();
    }

    return 0;
}

