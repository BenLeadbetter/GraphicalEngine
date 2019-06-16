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
    Window window;
    Drawer drawer;
    MeshManager meshManager;
    Stopwatch stopwatch;
    drawer.setView(
        ViewData(
            Vector3(8.0f, 5.0f, 5.5f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f)
        )
    );
    
    Particle particle1(meshManager);
    particle1.setVelocity(Vector3(3.2f, 0.1f, 1.8f));
    particle1.setRenderMode(RenderMode::FILL);
    particle1.scale(0.5f);

    Particle particle2(meshManager);
    particle2.setVelocity(Vector3(1.2f, -2.1f, -0.8f));
    particle2.setRenderMode(RenderMode::FILL);
    particle2.scale(0.5f);
    particle2.setDisplaceMent(Vector3(-3.0f, 3.0f, 0.0f));
    particle2.setColor(Vector3(0.0f, 0.0f, 1.0f));
    
    Particle particle3(meshManager);
    particle3.setVelocity(Vector3(1.2f, 2.1f, -0.8f));
    particle3.setRenderMode(RenderMode::FILL);
    particle3.scale(0.5f);
    particle3.setDisplaceMent(Vector3(1.0f, -2.0f, -2.0f));
    particle3.setColor(Vector3(0.0f, 1.0f, 0.0f));

    Particle particle4(meshManager);
    particle4.setVelocity(Vector3(1.2f, 2.1f, -0.8f));
    particle4.setRenderMode(RenderMode::FILL);
    particle4.scale(0.5f);
    particle4.setDisplaceMent(Vector3(-1.0f, -2.5f, -2.0f));
    particle4.setColor(Vector3(1.0f, 1.0f, 0.0f));

    Particle particle5(meshManager);
    particle5.setVelocity(Vector3(1.2f, 2.1f, -0.8f));
    particle5.setRenderMode(RenderMode::FILL);
    particle5.scale(0.5f);
    particle5.setDisplaceMent(Vector3(1.8f, -2.9f, 2.0f));
    particle5.setColor(Vector3(0.0f, 1.0f, 1.0f));

    Particle particle6(meshManager);
    particle6.setVelocity(Vector3(0.2f, 1.1f, -3.8f));
    particle6.setRenderMode(RenderMode::FILL);
    particle6.scale(0.5f);
    particle6.setDisplaceMent(Vector3(2.0f, -1.0f, -2.5f));
    particle6.setColor(Vector3(1.0f, 0.0f, 1.0f));

    Particle particle7(meshManager);
    particle7.setVelocity(Vector3(1.2f, 2.1f, -0.8f));
    particle7.setRenderMode(RenderMode::FILL);
    particle7.scale(0.5f);
    particle7.setDisplaceMent(Vector3(-1.8f, -2.1f, -2.9f));
    particle7.setColor(Vector3(0.8f, 0.8f, 0.6f));
    
    ParticleCollider particleCollider(meshManager);
    particleCollider.addParticle(std::make_shared<Particle>(particle1));
    particleCollider.addParticle(std::make_shared<Particle>(particle2));
    particleCollider.addParticle(std::make_shared<Particle>(particle3));
    particleCollider.addParticle(std::make_shared<Particle>(particle4));
    particleCollider.addParticle(std::make_shared<Particle>(particle5));
    particleCollider.addParticle(std::make_shared<Particle>(particle6));
    particleCollider.addParticle(std::make_shared<Particle>(particle7));

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
        particleCollider.update(dtSeconds);

        /*
        *   Render 
        */ 

        window.clear();
        particleCollider.draw(drawer);
        window.swapBuffers();
    }

    return 0;
}

