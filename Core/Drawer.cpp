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
viewChangeMatrix(glm::mat4(1.0f)),
projectionMatirx(glm::mat4(1.0f)),
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
    shader.setVec3("eyePos", DefaultViewData().Eye);
    
    setLightData(
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    glCheckError();
}

void Drawer::setView(const ViewData& data)
{
    // create new view-basis
    glm::vec3 n = glm::normalize(data.Eye - data.At);
    glm::vec3 u = glm::normalize(glm::cross(data.Up, n));
    glm::vec3 v = glm::cross(n, u);

    // assemble the matrix
    viewChangeMatrix = glm::mat4(
        u.x, v.x, n.x, 0.0f,
        u.y, v.y, n.y, 0.0f,
        u.z, v.z, n.z, 0.0f,
        -glm::dot(data.Eye, u), -glm::dot(data.Eye, v), -glm::dot(data.Eye,n), 1.0f
    );

    shader.use();
    shader.setVec3(
        "eyePos", 
        data.Eye.x,
        data.Eye.y,
        data.Eye.z
        );
}

void Drawer::setProjection(const ProjectionData& data)
{
    projectionMatirx = glm::mat4(
        data.Dist / data.Aspect,      
        0.0f,       
        0.0f,                           
        0.0f,
        0.0f,               
        data.Dist,       
        0.0f,                          
        0.0f,
        0.0f,               
        0.0f,       
        -(data.Far + data.Near) / (data.Far - data.Near),  
        -2 * data.Near * data.Far / (data.Far - data.Near),
        0.0f,               
        0.0f,       
        -1.0f,                          
        0.0f
    );
}

void Drawer::setLightData(
    glm::vec3 diffuse, 
    glm::vec3 specular, 
    glm::vec3 ambient
    )
{
    shader.use();
    shader.setVec3("srcSpec", diffuse.x, diffuse.y, diffuse.z);
    shader.setVec3("srcAmb", specular.x, specular.y, specular.z);
    shader.setVec3("srcEmit", ambient.x, ambient.y, ambient.z);   
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

    // set up for fill drawing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.use();
    glDrawElements(
        GL_TRIANGLES, 
        drawable.getDrawData().NumberOfIndices, 
        GL_UNSIGNED_INT, 
        0
    );

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
    glDrawElements(
        GL_TRIANGLES, 
        drawable.getDrawData().NumberOfIndices, 
        GL_UNSIGNED_INT, 
        0
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

    shader.setVec4("matDiff", drawable.getColorData().diffuse);
}