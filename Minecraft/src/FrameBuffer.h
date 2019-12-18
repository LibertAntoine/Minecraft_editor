#pragma once

#include <GL/glew.h>
#include "Renderer.h"

class FrameBuffer {
  private:
    unsigned int m_FrameBufferId;
  public:
    FrameBuffer();
    ~FrameBuffer();
    void Bind() const;
    void Unbind() const;
};
