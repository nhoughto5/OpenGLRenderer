#include "pch.h"
#include "Model.h"
#include <tiny_obj_loader.h>

Model::Model() {
}

Model::Model(std::string name) :
    m_Name(name) {
}

void Model::SetMesh(std::string meshPath) {
    meshPath = (ASSET_FOLDER + meshPath);
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file((meshPath + "\manifest.xml").c_str());
    OGLR_ASSERT(result.status == 0, "Failed to read manifest file {0}", meshPath);

    auto meshNode = doc.child("mesh");

    OGLR_CORE_INFO("============================");
    OGLR_CORE_INFO("Loading Model: {0}", meshNode.attribute("meshname").value());
    OGLR_CORE_INFO("============================");
    for (pugi::xml_node child : meshNode.children()) {
        std::string n = child.name();
        if (n.compare("shape") == 0) {
            std::string shapeName = child.attribute("name").value();
            std::shared_ptr<Shape> shape = std::make_shared<Shape>();

            std::ifstream vertexData((meshPath + shapeName + ".mv"), std::ios::binary);
            std::ifstream indexData((meshPath + shapeName + ".mi"), std::ios::binary);

            if (vertexData.fail() || indexData.fail())
            {
                OGLR_CORE_ERROR("Failed to open data files for shape: {0}", (meshPath + shapeName));
            }

            vertexData.seekg(0, std::ios::end);
            indexData.seekg(0, std::ios::end);
            int vertexFileSize = vertexData.tellg();
            int indexFileSize = indexData.tellg();
            vertexData.seekg(0, std::ios::beg);
            indexData.seekg(0, std::ios::beg);

            float vertexSize = sizeof(Vertex);
            float vertCount = vertexFileSize / sizeof(Vertex);
            float indexCount = indexFileSize / sizeof(uint32_t);
            std::vector<Vertex> verts(vertexFileSize / sizeof(Vertex));
            vertexData.read(reinterpret_cast<char*>(verts.data()), vertexFileSize);

            std::vector<uint32_t> indices(indexFileSize / sizeof(uint32_t));
            indexData.read(reinterpret_cast<char*>(indices.data()), indexFileSize);

            shape->SetData(verts, indices, "default.glsl");
            shape->SetMaterial(readMaterial(child));

            m_Shapes.push_back(shape);
        }
    }
}

void Model::AddTransform(std::shared_ptr<Transform> t) {
    m_Transforms.push_back(t);
    auto transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, t->Position);
    transformMatrix = glm::scale(transformMatrix * t->GetRotationMatrix(), t->Scale);
    m_TransformMatrices.push_back(transformMatrix);

    for (const auto shape : m_Shapes) {
        shape->AddInstance(transformMatrix);
    }
}

void Model::RenderShadows(glm::mat4 cameraView, glm::mat4 cameraProj) {
    for (auto& shape : m_Shapes) {
        shape->DrawShadow(GL_TRIANGLES, cameraView, cameraProj);
    }
}
void Model::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    for (auto& shape : m_Shapes) {
        shape->Draw(GL_TRIANGLES, cameraView, cameraProj);
    }
}

std::shared_ptr<MaterialData> Model::readMaterial(pugi::xml_node node)
{
    std::shared_ptr<MaterialData> ret = std::make_shared<MaterialData>();
    ret->ambient_texname = node.child("ambient_texname").attribute("src").value();
    ret->diffuse_texname = node.child("diffuse_texname").attribute("src").value();
    ret->specular_texname = node.child("specular_texname").attribute("src").value();
    ret->specular_highlight_texname = node.child("specular_highlight_texname").attribute("src").value();
    ret->bump_texname = node.child("bump_texname").attribute("src").value();

    ret->ambient = readVec3(node.child("ambient"));
    ret->diffuse = readVec3(node.child("diffuse"));
    ret->specular = readVec3(node.child("specular"));
    ret->transmittance = readVec3(node.child("transmittance"));
    ret->emission = readVec3(node.child("emission"));

    ret->shininess = node.child("shininess").attribute("value").as_float();
    ret->ior = node.child("ior").attribute("value").as_float();
    ret->dissolve = node.child("dissolve").attribute("value").as_float();
    ret->illum = node.child("illum").attribute("value").as_float();
    return ret;
}

glm::vec3 Model::readVec3(pugi::xml_node node)
{
    glm::vec3 ret;
    ret.x = node.attribute("x").as_float();
    ret.y = node.attribute("y").as_float();
    ret.z = node.attribute("z").as_float();
    return ret;
}

glm::vec3 Model::float3ToGLM(float* realt) {
    return glm::vec3(realt[0], realt[1], realt[2]);
}