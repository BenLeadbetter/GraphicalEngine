#ifndef GUARD_RENDER_HPP
#define GUARD_RENDER_HPP

#include <memory>
#include "Drawer.hpp"

enum class RenderingMode {
    DEFAULT,
    RAINBOW
};

RenderingMode decideRenderingMode(int argc, char** argv);
std::unique_ptr<Drawer> getDrawer(RenderingMode&);

#endif