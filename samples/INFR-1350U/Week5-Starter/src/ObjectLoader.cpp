#include "ObjectLoader.h"


VertexArrayObject::sptr ObjectLoader::LoadObjectFile(const std::string& filename)
{
	std::ifstream in_file(filename);

	std::vector<glm::fvec3> positionVerts;
	std::vector<glm::fvec2> textureVerts;
	std::vector<glm::fvec3> normalVerts;

	//Face vectors
	std::vector<GLint> position_indicies;
	std::vector<GLint> texture_indicies;
	std::vector<GLint> normal_indicies;

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	
	glm::vec2 temp_vec2;
	glm::vec3 temp_vec3;
	
	GLint temp_glint = 0;

	if (!in_file.is_open())
	{
		throw "Error::ObjectLoader::Could not open file.";
	}

	MeshBuilder<VertexPosNormTex> mesh;

	// Read every line in obj file
	while (std::getline(in_file, line))
	{
		//Get line prefix
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "v") // vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			positionVerts.push_back(temp_vec3);
		}
		else if (prefix == "vt") // Texture
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			textureVerts.push_back(temp_vec2);
		}
		else if (prefix == "vn") // Normals
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			normalVerts.push_back(temp_vec3);
		}
		else if (prefix == "f") // Faces
		{
			int markType = 0;

			while (ss >> temp_glint)
			{
				//Push indices
				if (markType == 0)
					position_indicies.push_back(temp_glint);
				else if (markType == 1)
					texture_indicies.push_back(temp_glint);
				else if (markType == 2)
					normal_indicies.push_back(temp_glint);

				//Check if next is special character or space. Ignore if it is. 
				if (ss.peek() == '/')
				{
					++markType;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++markType;
					ss.ignore(1, ' ');
				}

				//Reset counterr
				if (markType > 2)
					markType = 0;
			}
		}

		//Vertices to mesh
		for (size_t i = 0; i < position_indicies.size(); ++i)
		{
			VertexPosNormTex v = VertexPosNormTex(positionVerts[position_indicies[i] - 1], normalVerts[normal_indicies[i] - 1],
															    textureVerts[texture_indicies[i] - 1]);

			mesh.AddIndex(mesh.AddVertex(v));
		}

	}

	return mesh.Bake();
}

