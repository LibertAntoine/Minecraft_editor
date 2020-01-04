#include "FrameBuffer.h"
#include "GLerror.h"

FrameBuffer::FrameBuffer()
{
  GLCall(glGenFramebuffers(1, &m_FrameBufferId));

}

FrameBuffer::~FrameBuffer()
{
  GLCall(glDeleteFramebuffers(1, &m_FrameBufferId));
}

void FrameBuffer::Bind() const
{
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId));
}

void FrameBuffer::Unbind() const
{
  GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GLuint FrameBuffer::GetFrameBufferId() const
{
  return m_FrameBufferId;
}

void FrameBuffer::getDataAtPosition4ui(int x, int y, GLuint *data, GLenum attachment) const
{
	GLCall(glReadBuffer(attachment));
	GLCall( glReadPixels(x, y, 1, 1, GL_RGBA_INTEGER, GL_UNSIGNED_INT, data) );
}

void FrameBuffer::getDataAtPosition4i(int x, int y, GLint *data, GLenum attachment) const
{
	GLCall(glReadBuffer(attachment));
	GLCall( glReadPixels(x, y, 1, 1, GL_RGBA_INTEGER, GL_INT, data) );
}
