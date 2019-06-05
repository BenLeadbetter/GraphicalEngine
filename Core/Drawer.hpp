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

class ViewData
{
    public:
        ViewData(const Vector3& EyeIn, const Vector3& AtIn, const Vector3& UpIn):
        Eye(EyeIn),
        At(AtIn),
        Up(UpIn)
        {};

        void setEye(const Vector3& vec) { Eye = vec; }
        void setAt(const Vector3& vec) { At = vec; }
        void setUp(const Vector3& vec) { Up = vec; }

        Vector3 getEye() const { return Eye; }
        Vector3 getAt() const { return At; }
        Vector3 getUp() const { return Up; }


    private:
        Vector3 Eye;
        Vector3 At;
        Vector3 Up;
};

class ProjectionData
{
    public:
        ProjectionData(float DistIn, float AspectIn, float NearIn, float FarIn):
        Dist(DistIn),
        Aspect(AspectIn),
        Near(NearIn),
        Far(FarIn)
        {};

        void setDist(const float& val) { Dist = val; }
        void setAspect(const float& val) { Aspect = val; }
        void setNear(const float& val) { Near = val; }
        void setFar(const float& val) { Far = val; }

        float getDist() const { return Dist; }
        float getAspect() const { return Aspect; }
        float getNear() const { return Near; }
        float getFar() const { return Far; }
        
    private:
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
        void setLightData(Vector3, Vector3, Vector3);

        //
        void draw(Drawable&);

    private:
        
        //
        void loadShader();
        void drawSolidPolygon(const Drawable&);
        void drawWireFramePolygon(const Drawable&);
        void setObjectColorData(const Drawable&);

        //
        Matrix4   viewChangeMatrix;
        Matrix4   projectionMatirx;
        
        //
        Shader      shader;

        //
        // float cameraSpeed;
};

#endif