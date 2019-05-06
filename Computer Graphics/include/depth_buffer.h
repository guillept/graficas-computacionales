#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

class depth_buffer {
public:
	depth_buffer();
	~depth_buffer();
	void create(int resolution);
	void bind();
	void unbind();
	void bindDepthMap();
	void unbindDepthMap();
private:
	GLuint _framebuffer = 0;
	GLuint _dephtmap = 0;
	GLsizei _resolution = 0;
};