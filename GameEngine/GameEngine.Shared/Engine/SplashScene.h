//
//  SplashScene.h
//  TouchCone
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#pragma once

#include <iostream>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <Engine/GameScene.h>
#include <Engine/IRenderingEngine.h>
#include <Engine/Quaternion.h>
#include <Engine/Square.h>
#include <Engine/Animation.h>
#include <Engine/Camera.h>

class SplashScene : public GameScene {
    
public:
    virtual void Initialize(int width, int height);
    virtual void Render() const;
    virtual void UpdateAnimation(float timeStep);
    virtual void OnRotate(DeviceOrientation newOrientation);
    virtual void OnFingerUp(ivec2 location);
    virtual void OnFingerDown(ivec2 location);
    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
    SplashScene();
    virtual ~SplashScene();
    
private:
    GLuint BuildShader(const char* source, GLenum shaderType) const;
    GLuint BuildProgram(const char* vShader, const char* fShader) const;
    
    Animation m_animation;
    
    GLfloat m_depthDegree;
    GLfloat m_rotationAngle;
    GLfloat m_scale;
    GLfloat m_device;
    
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    
    float m_height;
    float m_width;
    
    float m_coolness;
    ivec2 m_orientation;
    Square * m_square;
    
    Camera * m_camera;
    
    mat4 VerticalFieldOfView(float degrees, float aspectRatio, float near, float far);
    void DrawSquare(vec3 transform, vec4 color) const;
    vec4 GetColorForIndex(int index) const;
};
