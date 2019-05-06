#include "depth_buffer.h"
#include <GL/glew.h>

depth_buffer::depth_buffer()
{
	_framebuffer = 0;
	_dephtmap = 0;
	_resolution = 0;
}

depth_buffer::~depth_buffer()
{
	glDeleteFramebuffers(1, &_framebuffer);
	glDeleteTextures(1, &_dephtmap);
}

void depth_buffer::create(int resolution)
{
	glGenFramebuffers(1, &_framebuffer);
	glGenTextures(1, &_dephtmap);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	bindDepthMap();
	_resolution = resolution;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _dephtmap, 0);
	unbind();

}

void depth_buffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0, 0, _resolution, _resolution);
}

void depth_buffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void depth_buffer::bindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, _dephtmap);
}

void depth_buffer::unbindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}