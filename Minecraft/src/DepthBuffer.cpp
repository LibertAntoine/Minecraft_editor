#include "DepthBuffer.h"

DepthBuffer::DepthBuffer()
{
  GLCall(glGenRenderbuffers(1, &m_DepthBufferId));
}

// TODO: write this with the proper syntax
DepthBuffer::~DepthBuffer()
{
  //GLCall(glDeleteDepthbuffers(1, &m_DepthBufferId));
}

void DepthBuffer::Bind() const
{
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferId));
}

void DepthBuffer::Unbind() const
{
  GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

const unsigned int DepthBuffer::getDepthBufferId() const
{
  return m_DepthBufferId;
}
