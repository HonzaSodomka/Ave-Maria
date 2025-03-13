#pragma once
#include "Loader.h"
#include "Mesh.h"

/*
	Loader pro formát modelù .obj
*/
class OBJLoader : public Loader
{
public:
	OBJLoader(const std::filesystem::path& filename);
	Mesh getMesh();
};

