//
//  SplashScene.cpp
//  TouchCone
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#include "SplashScene.h"
#define DEGREES_TO_RADIANS(degrees) ((degrees) * (M_PI / 180))

static const int ColumnCount = 30;
static const int RowCount = 9;

static const int deurell_logo[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    0,1,1,0,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1
};

SplashScene::SplashScene() : m_rotationAngle(0), m_scale(1.2f) {
}

void SplashScene::Initialize(int width, int height) {
    m_depthDegree = 0;
    m_coolness = 1451.66f;
    m_height = height;
    m_width = width;

    m_square = new Square();
    m_camera = new Camera();
    m_camera->setPosition(Vector3<float>(0, 0, 20));
    m_camera->setRotation(Vector3<float>(0, 0, 0));
    
    vector<Vertex> cubeVertices;
    vector<GLubyte> cubeIndices;
    m_square->GenerateVertices(cubeVertices, cubeIndices, vec4(0,0,0,1));
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(cubeVertices[0]),
                 &cubeVertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(cubeIndices[0]),
                 &cubeIndices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void SplashScene::OnRotate(DeviceOrientation newOrientation) {
}

void SplashScene::OnFingerUp(ivec2 location) {
}

void SplashScene::OnFingerDown(ivec2 location) {
}

void SplashScene::OnFingerMove(ivec2 oldLocation, ivec2 newLocation) {
}

SplashScene::~SplashScene() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    delete m_square;
    delete m_camera;
}

mat4 SplashScene::VerticalFieldOfView(float degrees, float aspectRatio, float near, float far) {
    float top = near * std::tan(degrees * Pi / 360.0f);
    float bottom = -top;
    float left = bottom * aspectRatio;
    float right = top * aspectRatio;
    return mat4::Frustum(left, right, bottom, top, near, far);
}

void SplashScene::UpdateAnimation(float timeStep) {
    float degrees = timeStep * 180;
    m_depthDegree += degrees;
}

void SplashScene::Render() const {
    glClearColor(0.6f, 0.6f, 0.6f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int index = 0;
    float zpos = -30;
    float rad = m_depthDegree/180*Pi;
    vec4 color(1,1,1,1);
    float const column_offset = 4;
    float const row_offset = 4;
    for (int row=0; row<RowCount; row++) {
        for (int column=0; column<ColumnCount; column++) {
            color = this->GetColorForIndex(index);
            float c = (column - (ColumnCount - 1)/ 2.0f) * column_offset;
            float r = (row - RowCount / 2.0f) * row_offset;
            float degAdd = index * m_coolness * (Pi / 180);
            float amp = 8 * cos(rad + degAdd);
            DrawSquare(vec3(c,-r,zpos + amp), color);
            index++;
        }
    }
}

void SplashScene::DrawSquare(vec3 translate, vec4 color) const
{
    GLuint positionSlot = glGetAttribLocation(simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(simpleProgram, "SourceColor");
    
    GLuint deviceUniform = glGetUniformLocation(simpleProgram, "Device");
    mat4 deviceRotation = mat4::Rotate(m_device);
    glUniformMatrix4fv(deviceUniform, 1, 0, deviceRotation.Pointer());
    
    mat4 rotation = mat4::Rotate(m_rotationAngle);
    mat4 scale = mat4::Scale(m_scale);
    mat4 translation = mat4::Translate(translate.x, translate.y, translate.z);
    
    GLint modelviewUniform = glGetUniformLocation(simpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation * m_camera->toMatrix();
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    
    GLsizei stride = sizeof(Vertex);
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttrib4f(colorSlot, color.x, color.y, color.z, color.w);
    glEnableVertexAttribArray(positionSlot);
    glDrawElements(GL_TRIANGLES, m_square->getIndicesCount(), GL_UNSIGNED_BYTE, 0);
    glDisableVertexAttribArray(positionSlot);
}

vec4 SplashScene::GetColorForIndex(int index) const {
    int col = deurell_logo[index];
    switch (col) {
        case 0:
            return vec4(0,0,0,1);
        case 1:
            return vec4(1,1,1,1);
        case 2:
            return vec4(0.2f,0.2f,0.8f,1);
        case 3:
            return vec4(1,1,0,1);
    }
    return vec4(1,1,1,1);
}

