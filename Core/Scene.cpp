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

void ParticleCollider::detectParticleCollisions()
{

}