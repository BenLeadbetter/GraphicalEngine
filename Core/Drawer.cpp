/* 
 *  Source file for the Drawer class header 
*/

#include "Drawer.hpp"


#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)


static ViewData DefaultViewData()
{
    return ViewData(
        Vector3(3.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 1.0f)
    );
}


static ProjectionData DefaultProjectionData()
{
    return ProjectionData(3, 1, 1, 10);
}

Drawer::Drawer():
viewChangeMatrix(Matrix4(1.0f)),
projectionMatirx(Matrix4(1.0f)),
shader(
    "GL/Shaders/VertexShaderSource.glsl", 
    "GL/Shaders/FragmentShaderSource.glsl"
    )
{
    // set the transformation matrices
    setView(DefaultViewData());
    setProjection(DefaultProjectionData());
    
    // load uniforms to shader
    shader.use();
    shader.setMat4("view", viewChangeMatrix);
    shader.setMat4("proj", projectionMatirx);
    shader.setVec3("eyePos", DefaultViewData().getEye());

    glCheckError();
}

void Drawer::setView(const ViewData& data)
{
    // create new view-basis
    Vector3 n = (data.getEye() - data.getAt()).unitVector();
    Vector3 u = cross(data.getUp(), n).unitVector();
    Vector3 v = cross(n, u).unitVector();

    // assemble the matrix
    viewChangeMatrix = Matrix4(
        u.x(), u.y(), u.z(), -dot(data.getEye(), u),
        v.x(), v.y(), v.z(), -dot(data.getEye(), v),
        n.x(), n.y(), n.z(), -dot(data.getEye(), n),
        0.0f,  0.0f,  0.0f,  1.0f
    );

    shader.use();
    shader.setVec3("eyePos", data.getEye());
}

void Drawer::setProjection(const ProjectionData& data)
{
    projectionMatirx = Matrix4(
        data.getDist() / data.getAspect(),
        0.0f,           
        0.0f,                                                                   
        0.0f,
        0.0f,                               
        data.getDist(), 0.0f,                                                                   
        0.0f,
        0.0f,                               
        .0f,           
        -(data.getFar() + data.getNear()) / (data.getFar() - data.getNear()),   
        -1.0f,
        0.0f,                               
        0.0f,           
        -2 * data.getNear() * data.getFar() / (data.getFar() - data.getNear()), 
        0.0f
    );
}

LightData Drawer::getLightData()
{
    return lightData;
}

void Drawer::updateShader()
{

    // load uniforms to shader
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
        32
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