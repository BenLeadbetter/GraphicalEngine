#include "Drawer.hpp"
#include <algorithm>
#include <cmath>

#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void ViewData::rotateEyePanLeft(const float& dtime)
{
    float dAngle = -1.0f * CAMERA_SPEEED * dtime;
    Matrix3 rotationAboutUp(
        std::cos(dAngle), -1.0f * std::sin(dAngle), 0.0f,
        std::sin(dAngle), std::cos(dAngle),         0.0f,
        0.0f,             0.0f,                     1.0f
    );

    Eye = rotationAboutUp * Eye;
}

void ViewData::rotateEyePanRight(const float& dtime)
{
    float dAngle = CAMERA_SPEEED * dtime;
    Matrix3 rotationAboutUp(
        std::cos(dAngle), -1.0f * std::sin(dAngle), 0.0f,
        std::sin(dAngle), std::cos(dAngle),         0.0f,
        0.0f,             0.0f,                     1.0f
    );

    Eye = rotationAboutUp * Eye;
}

void ViewData::rotateEyePitchUp(const float& dtime)
{
    float dAngle = CAMERA_SPEEED * dtime;
    Vector3 rotationAxis = cross(Eye - At, Up).unitVector();
    Matrix3 rotationAboutAxis(
        (float)(std::cos(dAngle) + std::pow(rotationAxis.x(), 2) * (1.0f - std::cos(dAngle))),
        rotationAxis.x() * rotationAxis.y() * (1.0f - std::cos(dAngle)) - rotationAxis.z() * std::sin(dAngle),
        rotationAxis.x() * rotationAxis.z() * (1.0f - std::cos(dAngle)) + rotationAxis.y() * std::sin(dAngle),
        rotationAxis.y() * rotationAxis.x() * (1.0f - std::cos(dAngle)) + rotationAxis.z() * std::sin(dAngle),
        (float)(std::cos(dAngle) + std::pow(rotationAxis.y(), 2) * (1.0f - std::cos(dAngle))),
        rotationAxis.y() * rotationAxis.z() * (1.0f - std::cos(dAngle)) - rotationAxis.x() * std::sin(dAngle),
        rotationAxis.z() * rotationAxis.x() * (1.0f - std::cos(dAngle)) - rotationAxis.y() * std::sin(dAngle),
        rotationAxis.z() * rotationAxis.y() * (1.0f - std::cos(dAngle)) + rotationAxis.x() * std::sin(dAngle),
        (float)(std::cos(dAngle) + std::pow(rotationAxis.z(), 2) * (1.0f - std::cos(dAngle)))
    );

    Eye = rotationAboutAxis * Eye;
}

void ViewData::rotateEyePitchDown(const float& dtime)
{
    float dAngle = -1.0f * CAMERA_SPEEED * dtime;
    Vector3 rotationAxis = cross(Eye - At, Up).unitVector();
    Matrix3 rotationAboutAxis(
        (float)(std::cos(dAngle) + std::pow(rotationAxis.x(), 2) * (1.0f - std::cos(dAngle))),
        rotationAxis.x() * rotationAxis.y() * (1.0f - std::cos(dAngle)) - rotationAxis.z() * std::sin(dAngle),
        rotationAxis.x() * rotationAxis.z() * (1.0f - std::cos(dAngle)) + rotationAxis.y() * std::sin(dAngle),
        rotationAxis.y() * rotationAxis.x() * (1.0f - std::cos(dAngle)) + rotationAxis.z() * std::sin(dAngle),
        (float)(std::cos(dAngle) + std::pow(rotationAxis.y(), 2) * (1.0f - std::cos(dAngle))),
        rotationAxis.y() * rotationAxis.z() * (1.0f - std::cos(dAngle)) - rotationAxis.x() * std::sin(dAngle),
        rotationAxis.z() * rotationAxis.x() * (1.0f - std::cos(dAngle)) - rotationAxis.y() * std::sin(dAngle),
        rotationAxis.z() * rotationAxis.y() * (1.0f - std::cos(dAngle)) + rotationAxis.x() * std::sin(dAngle),
        (float)(std::cos(dAngle) + std::pow(rotationAxis.z(), 2) * (1.0f - std::cos(dAngle)))
    );

    Eye = rotationAboutAxis * Eye;
}

void ProjectionData::zoomOut(const float& dt)
{
    Dist -= CAMERA_SPEEED * dt * 4.0f;
    if(Dist < 0)
        Dist = 0;
}

void ProjectionData::zoomIn(const float& dt)
{
    Dist += CAMERA_SPEEED * dt * 4.0f;
}

Drawer::Drawer():
    viewChangeMatrix(Matrix4(1.0f)),
    projectionMatirx(Matrix4(1.0f)),
    viewData(
        Vector3(3.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 1.0f)
    ),
    projectionData(3, 1, 1, 10),
    shader(
        "GL/Shaders/DefaultVertex.glsl", 
        "GL/Shaders/DefaultFrag.glsl"
        )
{
    updateShader(0.0f);

    glCheckError();
}

void Drawer::updateView()
{
    Vector3 n = (viewData.getEye() - viewData.getAt()).unitVector();
    Vector3 u = cross(viewData.getUp(), n).unitVector();
    Vector3 v = cross(n, u).unitVector();

    viewChangeMatrix = Matrix4(
        u.x(), u.y(), u.z(), -dot(viewData.getEye(), u),
        v.x(), v.y(), v.z(), -dot(viewData.getEye(), v),
        n.x(), n.y(), n.z(), -dot(viewData.getEye(), n),
        0.0f,  0.0f,  0.0f,  1.0f
    );

    shader.use();
    shader.setVec3("eyePos", viewData.getEye());
}

void Drawer::setView(const ViewData& data)
{
    viewData = data;

    updateView();
}

void Drawer::updateProjection()
{
    projectionMatirx = Matrix4(
        projectionData.getDist() / projectionData.getAspect(),
        0.0f,           
        0.0f,                                                                   
        0.0f,
        0.0f,                               
        projectionData.getDist(), 0.0f,                                                                   
        0.0f,
        0.0f,                               
        .0f,           
        -(projectionData.getFar() + projectionData.getNear()) / (projectionData.getFar() - projectionData.getNear()),   
        -1.0f,
        0.0f,                               
        0.0f,           
        -2 * projectionData.getNear() * projectionData.getFar() / (projectionData.getFar() - projectionData.getNear()), 
        0.0f
    );    
}

void Drawer::setProjection(const ProjectionData& data)
{
    projectionData = data;

    updateProjection();
}

LightData& Drawer::getLightData()
{
    return lightData;
}

ViewData& Drawer::getViewData()
{
    return viewData;
}

ProjectionData& Drawer::getProjectionData()
{
    return projectionData;
}

void Drawer::updateShader(const float&)
{
    updateLightData();
    updateView();
    updateProjection();

    shader.setMat4("view", viewChangeMatrix);
    shader.setMat4("proj", projectionMatirx);
}

void Drawer::draw(Drawable& drawable)
{
    Matrix4 worldTransform(drawable.getDrawData().WorldTransform);
    shader.setMat4("world", worldTransform);
    
    if(drawable.getDrawData().renderMode == RenderMode::FILL)
        drawSolidPolygon(drawable);
    
    else if(drawable.getDrawData().renderMode == RenderMode::LINE)
        drawWireFramePolygon(drawable);
}

void Drawer::drawSolidPolygon(const Drawable& drawable)
{
    glBindVertexArray(drawable.getDrawData().VertexArrayID);

    setObjectColorData(drawable);
    updateLightData();

    // set up for fill drawing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    shader.use();
    glDrawArrays(
        GL_TRIANGLES, 
        0, 
        drawable.getDrawData().NumberOfVertices
    );

    glDisable(GL_DEPTH_TEST);

    glCheckError();
}

void Drawer::drawWireFramePolygon(const Drawable& drawable)
{
    // Bind the appropriate Vertex Array
    glBindVertexArray(drawable.getDrawData().VertexArrayID);

    // antialiasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set colour to shader
    setObjectColorData(drawable);

    glCheckError();

    // Draw the wire frame
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5f);
    shader.use();
    glDrawArrays(
        GL_TRIANGLES, 
        0, 
        drawable.getDrawData().NumberOfVertices
    );

    glCheckError();

    // return the state of the GL interface
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    glCheckError();
}


void Drawer::setObjectColorData(const Drawable& drawable)
{
    shader.use();

    shader.setVec3("matDiff", drawable.getColorData().getDiffuse());
    shader.setVec3("matSpec", drawable.getColorData().getSpecular());
    shader.setVec3("matAmbi", drawable.getColorData().getAmbient());
    shader.setVec3("setEmis", drawable.getColorData().getEmissive());
    shader.setFloat("shininess", drawable.getColorData().getShininess());
    //TODO shader.setFloat("alpha", drawable.getColorData().getAlpha());
}

void Drawer::updateLightData()
{
    shader.use();
    shader.setVec3("srcDiff", getLightData().getDiffuse());
    shader.setVec3("srcSpec", getLightData().getSpecular());
    shader.setVec3("srcAmbi", getLightData().getAmbient());
    shader.setVec3("lightDir", getLightData().getLightDir());
}

RainbowDrawer::RainbowDrawer()
{
    setShader(Shader("GL/Shaders/RainbowVertex.glsl", "GL/Shaders/RainbowFrag.glsl"));
    updateShader(0.0);
}

float RainbowDrawer::getWidthValue(const Drawable& drawable) const
{
    ObjectData data = drawable.getMeshData();
    auto nVerts = data.vertices.size();
    float maxX = -10000.0;
    float minX = 10000.0;

    for(unsigned int i = 0; i != nVerts; ++i)
    {
        maxX = std::max(maxX, data.vertices[i][0]);
        minX = std::min(minX, data.vertices[i][0]);
    }

    return maxX - minX;
}

void RainbowDrawer::setWidthToShader(const float& width)
{
    shader.setFloat("modelWidth", width);
}

void RainbowDrawer::draw(Drawable& drawable)
{
    Matrix4 worldTransform(drawable.getDrawData().WorldTransform);
    shader.setMat4("world", worldTransform);
    setWidthToShader(getWidthValue(drawable));
    
    if(drawable.getDrawData().renderMode == RenderMode::FILL)
        drawSolidPolygon(drawable);
    
    else if(drawable.getDrawData().renderMode == RenderMode::LINE)
        drawWireFramePolygon(drawable);
}

DiscoDrawer::DiscoDrawer()
{
    setShader(Shader("GL/Shaders/DiscoVertex.glsl", "GL/Shaders/DiscoFrag.glsl"));
    setLightData(
        Vector3(0.3f, 0.0f, 0.3f),
        Vector3(0.5f, 0.5f, 0.5f),
        Vector3(0.2f, 0.0f, 0.5f),
        Vector3(1.0f, -0.8f, 0.7f)
    );
}

void DiscoDrawer::draw(Drawable& drawable)
{
    Matrix4 worldTransform(drawable.getDrawData().WorldTransform);
    shader.setMat4("world", worldTransform);
    
    if(drawable.getDrawData().renderMode == RenderMode::FILL)
        drawSolidPolygon(drawable);
    
    else if(drawable.getDrawData().renderMode == RenderMode::LINE)
        drawWireFramePolygon(drawable);
}

void DiscoDrawer::setSpotlight1Data(const Vector3& tar, const Vector3& col)
{
    shader.setVec3("spotlight1Target", tar);
    shader.setVec3("spotlight1Color", col);
}

void DiscoDrawer::setSpotlight2Data(const Vector3& tar, const Vector3& col)
{
    shader.setVec3("spotlight2Target", tar);
    shader.setVec3("spotlight2Color", col);
}

void DiscoDrawer::setSpotlight3Data(const Vector3& tar, const Vector3& col)
{
    shader.setVec3("spotlight3Target", tar);
    shader.setVec3("spotlight3Color", col);
}

void DiscoDrawer::updateShader(const float& dt)
{
    updateLightData();
    updateView();
    updateProjection();
    updateSpotlights(dt);

    shader.setMat4("view", viewChangeMatrix);
    shader.setMat4("proj", projectionMatirx);
}

void DiscoDrawer::updateSpotlights(const float& dt)
{
    spotlight1CurrentAngle += SPOT_SPEED * 0.8f * dt;
    spotlight2CurrentAngle += SPOT_SPEED * 0.6f * dt;
    spotlight3CurrentAngle += SPOT_SPEED * 0.5f * dt;

    setSpotlight1Data(
        Vector3(2.5f * std::cos(spotlight1CurrentAngle) + 1.0f, 0.0f, 1.5f *std::sin(spotlight1CurrentAngle)),
        Vector3(1.0f, 0.0f, 0.0f)
    );
    setSpotlight2Data(
        Vector3(0.5f * std::cos(spotlight2CurrentAngle) - 1.0f, 0.0f, 3.5f *std::sin(spotlight2CurrentAngle)),
        Vector3(1.0f, 0.0f, 1.0f)
    );
    setSpotlight3Data(
        Vector3(4.0f * std::cos(spotlight2CurrentAngle), 0.0f, 1.0f * std::sin(spotlight2CurrentAngle) + 0.5f),
        Vector3(0.2f, 0.0f, 1.0f)
    );


}