#include "DepthBuffer.h"
#include "GLerror.h"

DepthBuffer::DepthBuffer()
{
  GLCall(glGenRenderbuffers(1, &m_DepthBufferId));
}

DepthBuffer::~DepthBuffer()
{
  GLCall(glDeleteRenderbuffers(1, &m_DepthBufferId));
}

void DepthBuffer::Bind() const
{
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferId));
}

void DepthBuffer::Unbind() const
{
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

unsigned int DepthBuffer::getDepthBufferId() const
{
  return m_DepthBufferId;
}
