#pragma once
#include <unordered_map>
#include "Mesh.h"
#include "Material.h"

/*
	Loader pro formát modelù .obj
    Currently uses only last mentioned material, that is TODO
*/
class OBJLoader
{
public:
    OBJLoader(const std::filesystem::path& filename);
	Mesh getMesh();

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    std::vector<Mesh> submeshes;

    class Parse {
    public:
        // OBJ file
        static void vertex(std::vector<std::string> input, std::vector<glm::vec3>& output);
        static void uv(std::vector<std::string> input, std::vector<glm::vec2>& output);
        static void normal(std::vector<std::string> input, std::vector<glm::vec3>& output);
        static void face(std::vector<std::string> input, std::vector<unsigned int>& vertices_i, std::vector<unsigned int>& uvs_i, std::vector<unsigned int>& normals_i);

        // MTL file
        static void MTL(std::vector<std::string> input, std::string modelFilename, std::unordered_map<std::string, Material>& materials);
        static void ambient(std::vector<std::string> input, Material& output);
        static void diffuse(std::vector<std::string> input, Material& output);
        static void specular(std::vector<std::string> input, Material& output);
    };

private:
    std::unordered_map<std::string, Material> materials;
    Material usedMaterial;
};

