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

void Model::SetOverrideDiffuse(std::string t) {
    m_OverrideDiffuse = t;
}

void Model::SetOverrideNormal(std::string t) {
    m_OverrideNormal = t;
}

void Model::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    for (auto& shape : m_Shapes) {
        shape->Draw(GL_TRIANGLES, cameraView, cameraProj);
    }
}

glm::vec3 Model::float3ToGLM(float* realt) {
    return glm::vec3(realt[0], realt[1], realt[2]);
}