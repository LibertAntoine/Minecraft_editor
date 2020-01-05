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

		/**
		 * \brief Extract pixel data from the current framebuffer
		 * \param attachment Specify on which attachment to pick the data from.
		 * \param[out] data Array that will contain the extracted data
		 */
		void getDataAtPosition4ui(int x, int y, GLuint* data, GLenum attachment) const;
		void getDataAtPosition4i(int x, int y, GLint* data, GLenum attachment) const;
};
