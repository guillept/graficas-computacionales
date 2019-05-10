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
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	_resolution = resolution;
	glGenTextures(1, &_dephtmap);
	bindDepthMap();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _dephtmap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	unbind();

}

void depth_buffer::bind()
{
	glViewport(0, 0, _resolution, _resolution);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
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