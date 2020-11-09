#pragma once

#include <GLM/glm.hpp>
#include <gl/GL.h>
#include <Graphics/Texture2D.h>
class GameObject
{
public:

	glm::vec2 Position, Size, Velocity;
	glm::vec3 Colour;

	GLfloat alive;
	GLfloat destroyed; 


	
};

