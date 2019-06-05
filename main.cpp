#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"
#include "Core/Particle.hpp"

#include <cmath>

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
    stage.scale(8.0f); 
    


    // test a particle
    Particle testParticle(meshManager);
    testParticle.setVelocity(Vector3(3.2f, 3.1f, -5.8f));
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
        
            
        drawer.setView(
            ViewData(
                Vector3(5.0 * std::sin((float)glfwGetTime()), 5.0 * std::cos((float)glfwGetTime()), 3.5),
                Vector3(0.0f, 0.0f, 0.0f),
                Vector3(0.0f, 0.0f, 1.0f)
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

