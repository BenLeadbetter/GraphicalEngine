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
    stage.setRenderMode(RenderMode::FILL);
    stage.scale(2.0f); 
    

    /*
    // test a particle
    Particle testParticle(meshManager);
    testParticle.setVelocity(Vector3(3.2f, 3.1f, -5.8f));
    testParticle.setRadius(0.4f);
    testParticle.setRenderMode(RenderMode::FILL);
    testParticle.scale(0.5f);
    */

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
        //drawer.draw(testParticle);
        window.swapBuffers();
    }

    return 0;
}

