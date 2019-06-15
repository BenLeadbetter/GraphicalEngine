#ifndef GUARD_SCENE_HPP
#define GUARD_SCENE_HPP

#include <vector>
#include <memory>
#include "Drawable.hpp"
#include "Drawer.hpp"

class Scene
{
    protected:
        using vecSize = std::vector<std::unique_ptr<Drawable>>::size_type;

    public:
        Scene() {};
        void draw(Drawer&) const;
        void addDrawable(std::unique_ptr<Drawable>&& drawable);

    private:
        std::vector<std::unique_ptr<Drawable>> drawables;
};

#endif