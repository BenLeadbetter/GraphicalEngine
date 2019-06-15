
#include "Scene.hpp"
#include "CollisionBox.hpp"

void Scene::draw(Drawer& drawer) const
{
    vecSize nDrawables = drawables.size();

    for(vecSize i = 0; i != nDrawables; ++i)
        drawer.draw(*drawables[i]);
}

void Scene::addDrawable(std::shared_ptr<Drawable>&& pDrawable)
{
    drawables.push_back(pDrawable);
}

ParticleCollider::ParticleCollider(MeshManager& meshManager)
{
    addDrawable(std::make_shared<CollisionBox>(meshManager));
}

void ParticleCollider::update(const float& dtime)
{
    detectWallCollisions();
    detectParticleCollisions();

    for(auto itr = drawables.begin(); itr != drawables.end(); ++itr)
        (*itr)->update(dtime);
}

void ParticleCollider::detectWallCollisions()
{
    for(vecSize i = 1; i != drawables.size(); ++i)
    {

    }
}

void ParticleCollider::detectParticleCollisions()
{
    
}