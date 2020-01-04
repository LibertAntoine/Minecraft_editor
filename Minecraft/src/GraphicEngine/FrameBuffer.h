#pragma once

#include <GL/glew.h>

class FrameBuffer {
  private:
    GLuint m_FrameBufferId;
  public:
    FrameBuffer();
    ~FrameBuffer();
    void Bind() const;
    void Unbind() const;
    GLuint GetFrameBufferId() const;

		void getDataAtPosition4ui(int x, int y, GLuint* data, GLenum attachment) const;
		void getDataAtPosition4i(int x, int y, GLint* data, GLenum attachment) const;
};
