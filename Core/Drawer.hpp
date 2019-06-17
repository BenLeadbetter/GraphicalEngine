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

        void rotateEyePanLeft(const float&);
        void rotateEyePanRight(const float&);
        void rotateEyePitchUp(const float&);
        void rotateEyePitchDown(const float&);

    private:
        Vector3 Eye;
        Vector3 At;
        Vector3 Up;

        static constexpr float CAMERA_SPEEED = 0.6f;
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

        void zoomOut(const float&);
        void zoomIn(const float&);
        
    private:
        float Dist;
        float Aspect;
        float Near;
        float Far;

        static constexpr float CAMERA_SPEEED = 0.6f;
};

class LightData
{
    public:
        LightData() {};
        template<typename T>
        LightData(T&& vec1, T&& vec2, T&& vec3, T&& vec4):
        diffuse(std::forward<T>(vec1)),
        specular(std::forward<T>(vec2)),
        ambient(std::forward<T>(vec3)),
        lightDir(std::forward<T>(vec4))
        {};

        void setDiffuse(const Vector3& vec) { diffuse = vec; }
        void setSpecular(const Vector3& vec) { specular = vec; }
        void setAmbient(const Vector3& vec) { ambient = vec; }
        void setLightDir(const Vector3 vec) { lightDir = vec; }

        Vector3 getDiffuse() const { return diffuse; }
        Vector3 getSpecular() const { return specular; }
        Vector3 getAmbient() const { return ambient; }
        Vector3 getLightDir() const { return lightDir; }
        
    private:
        Vector3 diffuse = Vector3(1.0f, 1.0f, 1.0f);
        Vector3 specular = Vector3(1.0f, 1.0f, 1.0f);
        Vector3 ambient = Vector3(0.5f, 0.5f, 0.5f);
        Vector3 lightDir = Vector3(1.0f, 1.0f, 1.0f);

};

class Drawer
{
    public:
        Drawer();
        virtual ~Drawer() {};
        void setView(const ViewData&);
        void setProjection(const ProjectionData&);
        template<typename T> void setLightData(T&&, T&&, T&&, T&&);
        template<typename Sh> void setShader(Sh&&);
        
        LightData& getLightData();
        ViewData& getViewData();
        ProjectionData& getProjectionData();

        void updateShader();
        virtual void draw(Drawable&);

    protected:
        void drawSolidPolygon(const Drawable&);
        void drawWireFramePolygon(const Drawable&);

    private:
        void loadShader();
        void setObjectColorData(const Drawable&);
        void updateView();
        void updateProjection();
        void updateLightData();

        Matrix4   viewChangeMatrix;
        Matrix4   projectionMatirx;
        
        LightData lightData;
        ViewData viewData;
        ProjectionData projectionData;
    
    protected:
        Shader shader;
};

template<typename T>
void Drawer::setLightData(T&& diffIn, T&& specIn, T&& ambiIn, T&& dirIn)
{
    lightData = LightData(
        std::forward<T>(diffIn), 
        std::forward<T>(specIn),
        std::forward<T>(ambiIn), 
        std::forward<T>(dirIn)
    );

    updateLightData();
}

template<typename Sh> 
void Drawer::setShader(Sh&& s)
{
    shader = std::forward<Sh>(s);
    updateShader();
}

class RainbowDrawer : public Drawer
{
    public:
        RainbowDrawer();
        ~RainbowDrawer() {};

        void draw(Drawable&);
    
    private:
        float getWidthValue(const Drawable&) const;
        void setWidthToShader(const float&);
};

#endif