#ifndef GUARD_SCENE_HPP
#define GUARD_SCENE_HPP

#include <vector>
#include <memory>
#include "Drawable.hpp"
#include "Drawer.hpp"
#include "MeshManager.hpp"
#include "CollisionBox.hpp"

class Scene
{
    protected:
        using vecSize = std::vector<std::shared_ptr<Drawable>>::size_type;

    public:
        Scene() {};
        void draw(Drawer&) const;
        void addDrawable(std::shared_ptr<Drawable>); 

    protected:
        std::vector<std::shared_ptr<Drawable>> drawables;
};

class ParticleCollider : public Scene
{
    public:
        ParticleCollider(MeshManager&);
        void update(const float&);
        void addParticle(std::shared_ptr<Particle>);
    
    private:
        void detectWallCollisions();
        void detectParticleCollisions();
        void applyGravitationalForces();
    
    private:
        std::shared_ptr<CollisionBox> pCollisionBox;
        std::vector<std::shared_ptr<Particle>> particles;
};

#endif