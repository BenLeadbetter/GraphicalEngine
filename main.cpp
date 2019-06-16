#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"
#include "Core/Particle.hpp"
#include "Core/CollisionBox.hpp"
#include "Core/Stopwatch.hpp"
#include "Core/Scene.hpp"
#include <cstdlib>

int main(int argc, char** argv)
{
    Window window;
    Drawer drawer;
    MeshManager meshManager;
    Stopwatch stopwatch;
    ParticleCollider particleCollider(meshManager);
    drawer.setView(
        ViewData(
            Vector3(8.0f, 5.0f, 5.5f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f)
        )
    );

    unsigned int nParticles;
    if(argc > 1)
        nParticles = std::stoi(argv[1]);
    else
        nParticles = 3;    
    
    for(unsigned int i = 0; i != nParticles; ++i)
    {
        std::srand(i*stopwatch.elapsed_time<int, std::chrono::milliseconds>());
        Particle newParticle(meshManager);
        newParticle.setVelocity(Vector3((float)(rand() % 8 - 4), (float)(2*rand() % 8 - 4), (float)(3*rand() % 8 - 4)));
        newParticle.setDisplaceMent(Vector3((float)((4*rand()) % 25 - 12.5f) / 10.0f, (float)((5*rand()) % 25 - 12.5f) / 10.0f, (float)((6*rand()) % 25 - 12.5f) / 10.0f));
        newParticle.setColor(Vector3((float)(7*rand() % 100) / 100.0f, (float)(8*rand() % 100) / 100.0f, (float)(9*rand() & 100) / 100.0f));

        particleCollider.addParticle(std::make_shared<Particle>(newParticle));
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

