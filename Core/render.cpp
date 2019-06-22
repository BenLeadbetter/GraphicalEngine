#include "render.hpp"
#include <algorithm>

RenderingMode decideRenderingMode(int argc, char** argv)
{
    unsigned int nFlags = std::max(argc, 2);
    
    RenderingMode ret = RenderingMode::DEFAULT;

    for(unsigned int i = 2; i != nFlags; ++i)
    {
        std::string flag(argv[i]);
        if(flag == "-rainbow")
            ret = RenderingMode::RAINBOW;
        
        else if(flag == "-disco")
            ret = RenderingMode::DISCO;
    }

    return ret;
}

std::unique_ptr<Drawer> getDrawer(RenderingMode& mode)
{
    switch (mode)
    {
    case RenderingMode::RAINBOW:
        return std::make_unique<RainbowDrawer>();
        break;
    
    case RenderingMode::DISCO:
        return std::make_unique<DiscoDrawer>();
        break;

    default:
        return std::make_unique<Drawer>();
        break;
    }
}