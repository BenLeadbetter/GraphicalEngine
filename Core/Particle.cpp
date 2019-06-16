#include "Particle.hpp"
#define DAMPING 0.9999

Particle::Particle(MeshManager& meshManager) :
Drawable(meshManager.getMesh(MeshID::SMOOTH_SPHERE)),
mass(1.0f),
radius(1.0f),
displacement(Vector3(0.0f, 0.0f, 0.0f)),
velocity(Vector3(0.0f, 0.0f, 0.0f)),
force(Vector3(0.0f, 0.0f, 0.0f))
{
    setColor(Vector3(1.0f, 0.0f, 0.0f));
    setRenderMode(RenderMode::FILL);
}

void Particle::setDisplaceMent(const Vector3& disp)
{
    displacement = disp;
    setPosition(displacement);
}

void Particle::setVelocity(const Vector3& velo)
{
    velocity = velo;
}

void Particle::setMass(const float& m)
{
    mass = m;
}

void Particle::setRadius(const float& rad)
{
    radius = rad;
    this->scale(rad / getRadius());
}

void Particle::setColor(const Vector3& color)
{
    setColorData(
        ObjectColorData(
            Vector3(color),
            Vector3(1.0f, 1.0f, 1.0f),
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(color),
            15
        )
    );
}

Vector3 Particle::getDisplacement() const
{
    return displacement;
}

Vector3 Particle::getVelocity() const
{
    return velocity;
}

Vector3 Particle::getForce() const
{
    return force;
}

float Particle::getMass() const
{
    return mass;
}

float Particle::getRadius() const
{
    return radius;
}

void Particle::applyForce(const Vector3& fc)
{
    force += fc;
}

void Particle::applyImpulse(const Vector3& imp)
{
    velocity += imp / mass;
}

void Particle::update(const float& dtime)
{
    displacement += velocity * dtime;
    velocity += (force / mass) * dtime;
    velocity = DAMPING * velocity;
    clearForce();

    this->setPosition(displacement);
}

void Particle::clearForce()
{
    force = Vector3(0.0f, 0.0f, 0.0f);
}