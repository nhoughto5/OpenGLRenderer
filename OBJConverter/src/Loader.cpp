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
    std::string fileName{ path.filename().u8string() };

    m_Doc.append_child("mesh").append_attribute("meshname").set_value(fileName.c_str());

    m_Directory = std::string(path.parent_path().u8string());
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, meshPath.c_str(), m_Directory.c_str())) {
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

            WriteShape(verts, indices, shape.name, matData);
        }
        else {
            WriteShape(verts, indices, shape.name, NULL);
        }
    }

    m_Doc.save_file((m_Directory + "/manifest.xml").c_str());
    OBJC_CORE_INFO("Succesfully Converted " + fileName);
}

void Loader::WriteShape(std::vector<Vertex> verts, std::vector<uint32_t> indices, std::string name, std::shared_ptr<MaterialData> matData) {
    std::ofstream vertexFile(m_Directory + "/" + name + ".mv", std::ios::out | std::ios::binary);
    for (int i = 0; i < 3; i++)
        vertexFile.write((char*)&verts[i], sizeof(Vertex));

    std::ofstream indexFile(m_Directory + "/" + name + ".mi", std::ios::out | std::ios::binary);
    for (int i = 0; i < 3; i++)
        indexFile.write((char*)&verts[i], sizeof(Vertex));

    auto shape = m_Doc.child("mesh").append_child("shape");
    shape.append_attribute("name").set_value(name.c_str());
    shape.append_child("ambient_texname").append_attribute("src").set_value(matData->ambient_texname.c_str());
    shape.append_child("diffuse_texname").append_attribute("src").set_value(matData->diffuse_texname.c_str());
    shape.append_child("specular_texname").append_attribute("src").set_value(matData->specular_texname.c_str());
    shape.append_child("specular_highlight_texname").append_attribute("src").set_value(matData->specular_highlight_texname.c_str());
    shape.append_child("bump_texname").append_attribute("src").set_value(matData->bump_texname.c_str());
    shape.append_child("displacement_texname").append_attribute("src").set_value(matData->displacement_texname.c_str());
    shape.append_child("alpha_texname").append_attribute("src").set_value(matData->alpha_texname.c_str());
    shape.append_child("reflection_texname").append_attribute("src").set_value(matData->reflection_texname.c_str());
    
    WriteVec3(shape.append_child("ambient"), matData->ambient);
    WriteVec3(shape.append_child("diffuse"), matData->diffuse);
    WriteVec3(shape.append_child("specular"), matData->specular);
    WriteVec3(shape.append_child("transmittance"), matData->transmittance);
    WriteVec3(shape.append_child("emission"), matData->emission);

    shape.append_child("shininess").append_attribute("value").set_value(matData->shininess);
    shape.append_child("ior").append_attribute("value").set_value(matData->ior);
    shape.append_child("dissolve").append_attribute("value").set_value(matData->dissolve);
    shape.append_child("illum").append_attribute("value").set_value(matData->illum);
}

void Loader::WriteVec3(pugi::xml_node node, glm::vec3 vec) {
    node.append_attribute("x").set_value(vec.x);
    node.append_attribute("y").set_value(vec.y);
    node.append_attribute("z").set_value(vec.z);
}
