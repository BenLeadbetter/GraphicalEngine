#include "Scene.hpp"

void Scene::draw(Drawer& drawer) const
{
    vecSize nDrawables = drawables.size();

    for(vecSize i = 0; i != nDrawables; ++i)
        drawer.draw(*drawables[i]);
}

void Scene::addDrawable(std::unique_ptr<Drawable>&& pDrawable)
{
    drawables.push_back(std::move(pDrawable));
}