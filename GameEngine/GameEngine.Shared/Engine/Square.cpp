/*!
 * \file Square.cpp
 *
 * \author deurell
 * \date March 2015
 *
 * Provides a simple 3D square model.
 */
#include "Engine/Square.h"
#include "Engine/Vector.h"
#include <vector>

const Vertex Vertices[] = {
    vec3(-1,1,-1),vec4(1,1,1,0.5f),
    vec3(1,1,-1),vec4(1,1,1,0.5f),
    vec3(-1,-1,-1),vec4(1,1,1,0.5f),
    vec3(1,-1,-1),vec4(1,1,1,0.5f),
    vec3(-1,1,1),vec4(1,1,1,0.5f),
    vec3(1,1,1),vec4(1,1,1,0.5f),
    vec3(-1,-1,1),vec4(1,1,1,0.5f),
    vec3(1,-1,1),vec4(1,1,1,0.5f)
};

const GLubyte Indices[] = {
    0,1,2,
    1,2,3,
    4,5,6,
    5,6,7,
    0,4,6,
    0,2,6,
    0,1,4,
    1,4,5,
    1,3,5,
    3,5,7,
    2,6,3,
    3,6,7
};

void Square::setOffset(vec3 offset) {
    m_offset = offset;
}

void Square::setScale(vec3 scale) {
    m_scale = scale;
}

int Square::getVerticesCount() const {
    return sizeof(Vertices) / sizeof(Vertex);
}

int Square::getIndicesCount() const {
    return sizeof(Indices) / sizeof(GLubyte);
}

Square::Square() {
    m_scale = vec3(1,1,1);
    m_offset = vec3(0,0,0);
}

void Square::GenerateVertices(vector<Vertex>& vertices, vector<GLubyte>& indices, vec4 color) {
    for (int currentVertice = 0; currentVertice < this->getVerticesCount(); currentVertice++)
    {
        Vertex current = Vertices[currentVertice];
        current.Position.x = current.Position.x * m_scale.x;
        current.Position.y = current.Position.y * m_scale.y;
        current.Position.z = current.Position.z * m_scale.z;
        current.Position += m_offset;
        current.Color = color;
        vertices.push_back(current);
    }

    for (int currentIndex=0; currentIndex < this->getIndicesCount(); currentIndex++) {
        indices.push_back(Indices[currentIndex]);
    }
}