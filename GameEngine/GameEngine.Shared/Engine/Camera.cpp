/*!
 * \file Camera.cpp
 *
 * \author deurell
 * \date March 2015
 *
 * Simple camera implementation
 */
#include "Engine/Camera.h"
#include "Engine/Quaternion.h"

#define M_PI        3.14159265358979323846264338327950288
#define DEGREES_TO_RADIANS(degrees) ((degrees) * (M_PI / 180))

Camera::Camera() : m_position(Vector3<float>(0,0,0)), m_rotation(Vector3<float>(0,0,0)) {
}

Vector3<float> Camera::getPosition() {
    return m_position;
}

void Camera::setPosition(Vector3<float> position) {
    m_position = position;
}

Vector3<float> Camera::getRotation() {
    return m_rotation;
}

void Camera::setRotation(Vector3<float> rotation) {
    m_rotation = rotation;
}

Matrix4<float> Camera::toMatrix() {
    float xw = DEGREES_TO_RADIANS(m_rotation.x);
    float yw = DEGREES_TO_RADIANS(m_rotation.y);
    float zw = DEGREES_TO_RADIANS(m_rotation.z);
    Quaternion zrq = Quaternion::CreateFromAxisAngle(vec3(0,0,1), -zw);
    Quaternion xrq = Quaternion::CreateFromAxisAngle(vec3(1,0,0), -xw);
    Quaternion yrq = Quaternion::CreateFromAxisAngle(vec3(0,1,0), -yw);
    mat4 rotatedCamera = zrq.Rotated(xrq).Rotated(yrq).ToMatrix();
    mat4 translatedCamera = mat4::Translate(-m_position.x, -m_position.y, -m_position.z);
    mat4 camera = translatedCamera * rotatedCamera;
    return camera;
}
