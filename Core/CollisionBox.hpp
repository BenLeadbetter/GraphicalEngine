#ifndef GUARD_COLLISION_BOX_HPP
#define GUARD_COLLISION_BOX_HPP

#include "Drawable.hpp"
#include "Particle.hpp"
#include "../Maths/Vector3.hpp"

class CollisionBox : public Drawable
{
    public:
        CollisionBox(MeshManager&);
        Vector3 collisionDir(const Particle&) const;
        float collisionOverlap(const Particle&) const;
    
    private:
        const float BOX_WIDTH = 8.0f;

        struct boxBoundaries{
            float xMin;
            float xMax;
            float yMin;
            float yMax;
            float zMin;
            float zMax;
        } boundaries;
};

#endif