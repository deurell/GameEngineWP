/*!
 * \file Camera.h
 *
 * \author deurell
 * \date March 2015
 *
 * Simple camera implementation
 */
#pragma once

#include <iostream>
#include "Engine/Vector.h"
#include "Engine/Matrix.h"

class Camera {

public:
    Vector3<float> getPosition();
    void setPosition(Vector3<float> position);
    Vector3<float> getRotation();
    void setRotation(Vector3<float> rotation);
    Camera();
    Matrix4<float> toMatrix();
    
private:
    Vector3<float> m_position;
    Vector3<float> m_rotation;
};

