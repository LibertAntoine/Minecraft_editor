#include "FrameBuffer.h"

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

const GLuint FrameBuffer::GetFrameBufferId() const
{
  return m_FrameBufferId;
}
