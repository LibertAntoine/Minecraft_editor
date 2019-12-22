#pragma once

#include <GL/glew.h>
#include "Renderer.h"

class FrameBuffer {
  private:
    GLuint m_FrameBufferId;
  public:
    FrameBuffer();
    ~FrameBuffer();
    void Bind() const;
    void Unbind() const;
    const GLuint GetFrameBufferId() const;
};
