#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <iostream>
#include "Engine/IRenderingEngine.h"
#include "Engine/SplashScene.h"
#include "Engine/SceneRequest.h"

#define STRINGIFY(A)  #A
#include "./Simple.vert"
#include "./Simple.frag"

using namespace std;

class RenderingEngine : public IRenderingEngine {
public:
    RenderingEngine();
    ~RenderingEngine();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
    void OnFingerUp(ivec2 location);
    void OnFingerDown(ivec2 location);
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
    
    bool SceneAvailable() const;

private:
    GameScene *m_gameScene;
    
    GLuint BuildShader(const char* source, GLenum shaderType) const;
    GLuint BuildProgram(const char* vShader, const char* fShader) const;
        
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_colorRenderbuffer;
    GLuint m_depthRenderbuffer;
    
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    
    float m_height;
    float m_width;
    ivec2 m_orientation;
    
    SceneRequest m_currentScene;
    
    void SetupNextScene(SceneRequest sceneRequest);
};

IRenderingEngine* CreateRenderer() {
    return new RenderingEngine();
}

void RenderingEngine::UpdateAnimation(float timeStep) {
    if(!SceneAvailable()) return;
    m_gameScene->UpdateAnimation(timeStep);
    SceneRequest request = m_gameScene->getSceneRequest();
    if(request.Scene != 0) {
        SetupNextScene(request);
    }
}

void RenderingEngine::SetupNextScene(SceneRequest request) {
    if(m_gameScene != NULL) {
        delete m_gameScene;
        m_gameScene = NULL;
    }
    GameScene *scene = new SplashScene();
    scene->setGlParams(m_simpleProgram, m_framebuffer, m_colorRenderbuffer, m_depthRenderbuffer);
    scene->Initialize(m_width, m_height);
    m_gameScene = scene;
}

RenderingEngine::RenderingEngine() : m_currentScene(SceneRequest(0)) {
    m_gameScene = new SplashScene();
    glGenRenderbuffers(1, &m_colorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
}

RenderingEngine::~RenderingEngine() {
    delete m_gameScene;
}

void RenderingEngine::Initialize(int width, int height) {
    m_height = height;
    m_width = width;   
    m_simpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
    glUseProgram(m_simpleProgram);
    
    // Set the projection matrix.
    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    mat4 projectionMatrix = mat4::Frustum(-1.6f, 1.6, -2.4, 2.4, 1, 100);
    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.Pointer());

    m_gameScene->setGlParams(m_simpleProgram, m_framebuffer, m_colorRenderbuffer, m_depthRenderbuffer);
    m_gameScene->Initialize(width, height);    
}

void RenderingEngine::Render() const {
    if(!SceneAvailable()) return;
    m_gameScene->Render();
}

void RenderingEngine::OnRotate(DeviceOrientation newOrientation) {
    if(!SceneAvailable()) {
        return;
    }
    m_gameScene->OnRotate(newOrientation);
}

void RenderingEngine::OnFingerUp(ivec2 location) {
    if(!SceneAvailable()) return;
    m_gameScene->OnFingerUp(location);
}

void RenderingEngine::OnFingerDown(ivec2 location) {
    if(!SceneAvailable()) return;
    m_gameScene->OnFingerUp(location);
}

void RenderingEngine::OnFingerMove(ivec2 previous, ivec2 location) {
    if(!SceneAvailable()) return;
}

GLuint RenderingEngine::BuildShader(const char* source, GLenum shaderType) const {
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return shaderHandle;
}

GLuint RenderingEngine::BuildProgram(const char* vertexShaderSource,
                                      const char* fragmentShaderSource) const {
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return programHandle;
}

bool RenderingEngine::SceneAvailable() const {
    if (m_gameScene == nullptr) {
        return false;
    }
    else {
        return true;
    }
}
