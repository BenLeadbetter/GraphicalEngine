#include "Scene.hpp"

void Scene::draw(Drawer& drawer) const
{
    vecSize nDrawables = drawables.size();

    for(vecSize i = 0; i != nDrawables; ++i)
        drawer.draw(*drawables[i]);
}

void Scene::addDrawable(std::shared_ptr<Drawable> pDrawable)
{
    drawables.push_back(pDrawable);
}

ParticleCollider::ParticleCollider(MeshManager& meshManager)
{
    std::shared_ptr<CollisionBox> collBox = std::make_shared<CollisionBox>(meshManager);
    addDrawable(collBox);
    pCollisionBox = collBox;
}

void ParticleCollider::update(const float& dtime)
{
    detectWallCollisions();
    detectParticleCollisions();


    for(auto itr = particles.begin(); itr != particles.end(); ++itr)
        (*itr)->update(dtime);
}

void ParticleCollider::addParticle(std::shared_ptr<Particle> pDrawable)
{
    addDrawable(pDrawable);
    particles.push_back(pDrawable);
}

void ParticleCollider::detectWallCollisions()
{
    for(vecSize i = 0; i != particles.size(); ++i)
    {
        Vector3 collisionNormal = pCollisionBox->collisionDir(*particles[i]);
        Vector3 particleVelocity = particles[i]->getVelocity();

        if(dot(particleVelocity, collisionNormal) < 0)
        {
            particles[i]->setVelocity(particleVelocity - 2 * dot(particleVelocity, collisionNormal) * collisionNormal);
        }
    }
}

void collide_particle(Particle& particle1, const Particle& particle2)
{
    Vector3 centre2_to_centre1 = particle1.getDisplacement() - particle2.getDisplacement();
    float distance_from_particle2 = centre2_to_centre1.magnitude();
    
    if(distance_from_particle2 < 1.0f)
    {
        centre2_to_centre1.normalise();
        Vector3 velocity1 = particle1.getVelocity();

        velocity1 = velocity1 - 2 * dot(velocity1, centre2_to_centre1) * centre2_to_centre1;
        particle1.setVelocity(velocity1);
    }
}

void ParticleCollider::detectParticleCollisions()
{
    for(vecSize i = 0; i != particles.size(); ++i)
    {
        for(vecSize j = 0; j != particles.size(); ++j)
        {
            if(i != j)
            {
                collide_particle(*particles[i], *particles[j]);
            }
        }
    }
}