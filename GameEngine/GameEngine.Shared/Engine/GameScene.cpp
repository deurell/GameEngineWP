/*!
 * \file GameScene.cpp
 *
 * \author deurell
 * \date March 2015
 *
 * Game scene provides id for scene and also a way to request a new scene load sequence
 */
#include "Engine/GameScene.h"

GameScene::GameScene() : m_sceneRequest(SceneRequest(0)) {
}

int GameScene::getSceneIdentifier() {
    return m_sceneIdentifier;
}


void GameScene::requestScene(SceneRequest scene) {
    m_sceneRequest = scene;
}

void GameScene::setGlParams(GLuint program, GLuint frameBuffer, GLuint colorBuffer, GLuint depthBuffer) {
    simpleProgram = program;
    framebuffer = frameBuffer;
    colorRenderbuffer = colorBuffer;
    depthRenderbuffer = depthBuffer;
}

SceneRequest GameScene::getSceneRequest() {
    return m_sceneRequest;
}