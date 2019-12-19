#pragma once

#include <GL/glew.h>
#include "Renderer.h" // NOTE: necessary for GLCall Macro

class DepthBuffer {
  private:
    unsigned int m_DepthBufferId;
  public:
    DepthBuffer();
    ~DepthBuffer();
    void Bind() const;
    void Unbind() const;

    const unsigned int getDepthBufferId() const;
};
