#include "pch.h"
#include "Model.h"
#include <tiny_obj_loader.h>

Model::Model() :
    m_TransformMatrix(1.0) {
    m_Transform = std::make_shared<Transform>();
}

Model::Model(std::string name) :
    m_Name(name),
    m_TransformMatrix(1.0) {
    m_Transform = std::make_shared<Transform>();
}

void Model::SetMesh(std::string meshPath, bool hasMTLFile = false) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    meshPath = (ASSET_FOLDER + meshPath);

    std::string directory;
    const size_t last_slash_idx = meshPath.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        directory = meshPath.substr(0, last_slash_idx) + "/";
    }

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
            //m_Shapes.push_back(std::make_shared<Shape>());
        }

        //if (shape.mesh.material_ids.size() > 0)
        //{
        //    m_Shapes.push_back(std::make_shared<Shape>(shape, attrib, &materials[shape.mesh.material_ids[0]]));
        //}
        //else
        //{
        //    m_Shapes.push_back(std::make_shared<Shape>(shape, attrib, nullptr));
        //}
        std::shared_ptr<Shape> s(new Shape(verts, indices, "triangle.glsl"));
        m_Shapes.push_back(s);
    }
}

void Model::SetTransform(std::shared_ptr<Transform> t) {
    m_Transform = t;
}

void Model::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    for (auto& shape : m_Shapes)
    {
        shape->Draw(GL_TRIANGLES, m_TransformMatrix, cameraView, cameraProj);
    }
}

void Model::UpdateTransform() {
    m_TransformMatrix = glm::mat4(1.0);
    //m_TransformMatrix = glm::translate(m_TransformMatrix, m_Transform->Position);
    //m_TransformMatrix = glm::scale(m_TransformMatrix * m_Transform->GetRotationMatrix(), m_Transform->Scale);
}
