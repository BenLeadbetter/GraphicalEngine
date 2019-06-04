#ifndef GUARD_DRAWER_HPP
#define GUARD_DRAWER_HPP

/**
 * 
 *  Header file for the Drawer class
 * 
 *  This class will be responsible for Drawing Drawables
 *  and for managing the shader and camera positions etc.
 * 
 * 
*/

#include "../GL/Shader.h"
#include "../Maths/Vector3.hpp"
#include "Drawable.hpp"
#include <glm/glm.hpp>

struct ViewData
{
    ViewData(const Vector3& EyeIn, const Vector3& AtIn, const Vector3& UpIn):
    Eye(EyeIn),
    At(AtIn),
    Up(UpIn)
    {};

    Vector3 Eye;
    Vector3 At;
    Vector3 Up;
};

struct ProjectionData
{
    ProjectionData(float DistIn, float AspectIn, float NearIn, float FarIn):
    Dist(DistIn),
    Aspect(AspectIn),
    Near(NearIn),
    Far(FarIn)
    {};

    float Dist;
    float Aspect;
    float Near;
    float Far;
};

class Drawer
{
    public:

        //
        Drawer();

        //
        void setView(const ViewData&);
        void setProjection(const ProjectionData&);
        //TODO void moveAt(vector);
        //TODO void rotateEye();
        void updateShader();
        void setLightData(glm::vec3, glm::vec3, glm::vec3);

        //
        void draw(Drawable&);

    private:
        
        //
        void loadShader();
        void drawSolidPolygon(const Drawable&);
        void drawWireFramePolygon(const Drawable&);
        void setObjectColorData(const Drawable&);

        //
        glm::mat4   viewChangeMatrix;
        glm::mat4   projectionMatirx;
        
        //
        Shader      shader;

        //
        // float cameraSpeed;
};

#endif