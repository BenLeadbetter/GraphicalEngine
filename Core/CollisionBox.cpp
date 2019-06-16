#include "CollisionBox.hpp"
#include "MeshManager.hpp"
#include <algorithm>

CollisionBox::CollisionBox(MeshManager& meshManager): 
    Drawable(meshManager.getMesh(MeshID::CUBE))
{
    setRenderMode(RenderMode::LINE);
    scale(BOX_WIDTH);

    boundaries.xMin = - (BOX_WIDTH / 2 - 1.0f);
    boundaries.xMax = (BOX_WIDTH / 2 - 1.0f);
    boundaries.yMin = - (BOX_WIDTH / 2 - 1.0f);
    boundaries.yMax = (BOX_WIDTH / 2 - 1.0f);
    boundaries.zMin = - (BOX_WIDTH / 2 - 1.0f);
    boundaries.zMax = (BOX_WIDTH / 2 - 1.0f);
}

Vector3 CollisionBox::collisionDir(const Particle& particle) const
{
    Vector3 particleDisplacement = particle.getDisplacement();
    
    Vector3 ret(
        particleDisplacement.x() - std::clamp(particleDisplacement.x(), boundaries.xMin, boundaries.xMax),
        particleDisplacement.y() - std::clamp(particleDisplacement.y(), boundaries.yMin, boundaries.yMax),
        particleDisplacement.z() - std::clamp(particleDisplacement.z(), boundaries.zMin, boundaries.zMax)
    );

    if(ret.squareMagnitude() != 0)
        ret.normalise();

    return -1.0f * ret;
}

float CollisionBox::collisionOverlap(const Particle& particle) const
{
    Vector3 particleDisplacement = particle.getDisplacement();
    
    Vector3 ret(
        particleDisplacement.x() - std::clamp(particleDisplacement.x(), boundaries.xMin, boundaries.xMax),
        particleDisplacement.y() - std::clamp(particleDisplacement.y(), boundaries.yMin, boundaries.yMax),
        particleDisplacement.z() - std::clamp(particleDisplacement.z(), boundaries.zMin, boundaries.zMax)
    );

    return ret.magnitude();
}