#pragma once

#include "MeshBuilder.h"
#include "MeshFactory.h"
#include <fstream>
#include <sstream>
#include <iostream>

class ObjectLoader
{
public:
	static VertexArrayObject::sptr LoadObjectFile(const std::string& filename);

protected:
	ObjectLoader() = default;
	~ObjectLoader() = default;
};

