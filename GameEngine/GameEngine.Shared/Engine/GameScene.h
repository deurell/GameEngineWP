/*!
 * \file GameScene.h
 *
 * \author deurell
 * \date March 2015
 *
 * Provides id and scene loading behavior
 */
#pragma once
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "Engine/IRenderingEngine.h"
#include "Engine/SceneRequest.h"

class GameScene : public IRenderingEngine {
    
public:
    GameScene();
    int getSceneIdentifier();
    void setGlParams(GLuint program, GLuint frameBuffer, GLuint colorBuffer, GLuint depthBuffer);
    SceneRequest getSceneRequest();

protected:
    GLuint simpleProgram;
    GLuint framebuffer;
    GLuint colorRenderbuffer;
    GLuint depthRenderbuffer;
    void requestScene(SceneRequest scene);
    
private:
    int m_sceneIdentifier;
    SceneRequest m_sceneRequest;
};
