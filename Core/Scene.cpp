#include "Scene.hpp"
#define GRAVITATIONAL_CONST 100.0

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
    applyGravitationalForces();

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
    Vector3 centre1_to_centre2 = particle2.getDisplacement() - particle1.getDisplacement();
    float distance_from_particle2 = centre1_to_centre2.magnitude();
    
    if(distance_from_particle2 < 2.0f)
    {
        float overlapDistance = 2.0f - distance_from_particle2;
        static float stiffnessScaleFactor = 45;
        Vector3 collisionForce = -1.0f * overlapDistance * stiffnessScaleFactor * centre1_to_centre2.unitVector();

        particle1.applyForce(collisionForce);
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

void apply_gravity(Particle& particle1, const Particle& particle2)
{
    Vector3 centre1_to_centre2 = particle2.getDisplacement() - particle1.getDisplacement();
    float square_distance = centre1_to_centre2.squareMagnitude();
    centre1_to_centre2.normalise();
    Vector3 graviationalForce = (GRAVITATIONAL_CONST * particle1.getMass() * particle2.getMass() / square_distance) * centre1_to_centre2;
    particle1.applyForce(graviationalForce);
}

void ParticleCollider::applyGravitationalForces()
{
    for(vecSize i = 0; i != particles.size(); ++i)
    {
        for(vecSize j = 0; j != particles.size(); ++j)
        {
            if(i != j)
            {
                apply_gravity(*particles[i], *particles[j]);
            }
        }
    }
}