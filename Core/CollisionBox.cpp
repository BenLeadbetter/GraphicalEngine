#include "CollisionBox.hpp"
#include "MeshManager.hpp"
#include <algorithm>

CollisionBox::CollisionBox(MeshManager& meshManager): 
    Drawable(meshManager.getMesh(MeshID::CUBE))
{
    setRenderMode(RenderMode::LINE);
    scale(BOX_WIDTH);

    boundaries.xMin = - BOX_WIDTH / 2;
    boundaries.xMax = BOX_WIDTH / 2;
    boundaries.yMin = - BOX_WIDTH / 2;
    boundaries.yMax = BOX_WIDTH / 2;
    boundaries.zMin = - BOX_WIDTH / 2;
    boundaries.zMax = BOX_WIDTH / 2;
}

Vector3 CollisionBox::collide(const Particle& particle) const
{
    Vector3 particleDisplacement = particle.getDisplacement();
    
    return Vector3(
        particleDisplacement.x() - std::clamp(particleDisplacement.x(), boundaries.xMin, boundaries.xMax),
        particleDisplacement.y() - std::clamp(particleDisplacement.y(), boundaries.yMin, boundaries.yMax),
        particleDisplacement.z() - std::clamp(particleDisplacement.z(), boundaries.zMin, boundaries.zMax)
    );
}