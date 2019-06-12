#include "Particle.hpp"

Particle::Particle(MeshManager& meshManager) :
Drawable(meshManager.getMesh(MeshID::SPHERE)),
mass(1.0f),
radius(1.0f),
displacement(Vector3(0.0f, 0.0f, 0.0f)),
velocity(Vector3(0.0f, 0.0f, 0.0f)),
force(Vector3(0.0f, 0.0f, 0.0f))
{
    setColorData(
        ObjectColorData(
            Vector4(1.0f, 0.0f, 0.0f, 1.0f),
            Vector4(0.8f, 0.8f, 0.8f, 1.0f),
            Vector4(1.0f, 1.0f, 1.0f, 1.0f),
            Vector4(0.0f, 0.0f, 0.0f, 0.0f),
            5.0f
        )
    );
}

void Particle::setDisplaceMent(const Vector3& disp)
{
    displacement = disp;
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

void Particle::update(float time)
{
    displacement += velocity * time / 1000;
    velocity += (force / mass) * time / 1000;
    clearForce();

    this->setPosition(displacement);
}

void Particle::clearForce()
{
    force = Vector3(0.0f, 0.0f, 0.0f);
}