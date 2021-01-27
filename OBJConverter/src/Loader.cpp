#include "pch.h"
#include "Loader.h"
#include <tiny_obj_loader.h>

glm::vec3 float3ToGLM(float* realt) {
    return glm::vec3(realt[0], realt[1], realt[2]);
}

void Loader::LoadMesh(std::filesystem::path path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    std::string meshPath{ path.u8string() };

    std::string directory{ path.parent_path().u8string() };

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, meshPath.c_str(), directory.c_str())) {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes) {
        std::vector<Vertex> verts;
        std::vector<uint32_t> indices;
        std::unordered_map<Vertex, uint32_t> uniqueVertices = {};
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex = {};
            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            if (index.normal_index > 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }

            if (attrib.texcoords.size() > 0 && index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1],
                };
            }

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(verts.size());
                verts.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }

        if (materials.size() > 0) {
            tinyobj::material_t mat = materials[shape.mesh.material_ids[0]];
            std::shared_ptr<MaterialData> matData(new MaterialData());
            matData->ambient_texname = mat.ambient_texname;
            matData->diffuse_texname = mat.diffuse_texname;
            matData->specular_texname = mat.specular_texname;
            matData->specular_highlight_texname = mat.specular_highlight_texname;
            matData->bump_texname = mat.bump_texname;
            matData->displacement_texname = mat.displacement_texname;
            matData->alpha_texname = mat.alpha_texname;
            matData->reflection_texname = mat.reflection_texname;

            matData->ambient = float3ToGLM(mat.ambient);
            matData->diffuse = float3ToGLM(mat.diffuse);
            matData->specular = float3ToGLM(mat.specular);
            matData->transmittance = float3ToGLM(mat.transmittance);
            matData->emission = float3ToGLM(mat.emission);

            matData->shininess = mat.shininess;
            matData->ior = mat.ior;
            matData->dissolve = mat.dissolve;
            matData->illum = mat.illum;

            WriteShape(verts, indices, shape.name, matData, directory);
        }
        else {
            WriteShape(verts, indices, shape.name, NULL, directory);
        }
    }

    OBJC_CORE_INFO("MADE IT");
}

void Loader::WriteShape(std::vector<Vertex> verts, std::vector<uint32_t> indices, std::string name, std::shared_ptr<MaterialData> matData, std::string directory) {
    std::ofstream vertexFile(directory + "/" + name + ".mv", std::ios::out | std::ios::binary);
    for (int i = 0; i < 3; i++)
        vertexFile.write((char*)&verts[i], sizeof(Vertex));

    std::ofstream indexFile(directory + "/" + name + ".mi", std::ios::out | std::ios::binary);
    for (int i = 0; i < 3; i++)
        indexFile.write((char*)&verts[i], sizeof(Vertex));
}
