#ifndef GUARD_PARTICLE_HPP
#define GUARD_PARTICLE_HPP

#include "Drawable.hpp"
#include "../Maths/Vector3.hpp"
#include "MeshManager.hpp"

class Particle : public Drawable
{
    public:
        Particle(MeshManager&);

        void setDisplaceMent(const Vector3&);
        void setVelocity(const Vector3&);
        void setMass(const float&);
        void setRadius(const float&);
        void setColor(const Vector3&);

        Vector3 getDisplacement() const;
        Vector3 getVelocity() const;
        Vector3 getForce() const;
        float getMass() const;
        float getRadius() const;

        void applyForce(const Vector3&);
        void applyImpulse(const Vector3&);
        void update(const float&);

    private:

        void clearForce();

        float mass;
        float radius;
        Vector3 displacement;
        Vector3 velocity;
        Vector3 force;
};

#endif