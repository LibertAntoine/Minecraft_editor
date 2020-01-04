#pragma once

#include <GL/glew.h>

class DepthBuffer {
  private:
    unsigned int m_DepthBufferId;
  public:
    DepthBuffer();
    ~DepthBuffer();
    void Bind() const;
    void Unbind() const;

    unsigned int getDepthBufferId() const;
};
