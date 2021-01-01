#include "pch.h"
#include "Application.h"
#include "Scene.h"

Scene::Scene(std::string scenePath) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(scenePath.c_str());
    OGLR_ASSERT(result.status == 0, "FAILED TO READ SCENE");
    m_LightService = LightService::GetInstance();
    for (pugi::xml_node scene : doc.children("scene")) {
        OGLR_CORE_INFO("============================");
        OGLR_CORE_INFO("LOADING SCENE: {0}", scene.attribute(SCENE_NAME.c_str()).value());
        OGLR_CORE_INFO("============================");
        for (pugi::xml_node child = scene.first_child(); child; child = child.next_sibling()) {
            std::string name = child.name();

            if (name.compare(MODEL_ATTRIBUTE_NAME) == 0) {
                loadModel(child);
            }
            else if (name.compare(GRID_NAME) == 0) {
                loadGrid(child);
            }
            else if (name.compare(LIGHT) == 0) {
                loadLight(child);
            }
        }
    }

    Application::Get().Subscribe(&m_Camera);
    m_Loaded = true;
}

void Scene::loadGrid(pugi::xml_node node) {
    for (auto attr = node.attributes_begin(); attr != node.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(ATTR_SIZE) == 0) {
            AddModel(std::make_shared<Grid>(std::stoi(attr->value())));
        }
    }
}

void Scene::loadModel(pugi::xml_node modelNode) {
    std::shared_ptr<Model> m(new Model(modelNode.name()));
    bool hasMTLFile = false;
    std::string meshPath = "";
    for (auto attr = modelNode.attributes_begin(); attr != modelNode.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(MESH_ATTRIBUTE_NAME) == 0) {
            meshPath = attr->value();
        }
        else if (name.compare(MATERIAL_ATTRIBUTE_NAME) == 0) {
            hasMTLFile = true;
        }
    }

    m->SetMesh(meshPath, hasMTLFile);

    for (const auto& child : modelNode.children()) {
        std::string childName = child.name();
        if (childName.compare(TRANSFORM) == 0) {
            m->SetTransform(ReadTransform(child));
        }
    }

    AddModel(m);
}

void Scene::loadLight(pugi::xml_node node) {
    for (const auto& child : node.children()) {
        std::string childName = child.name();
        if (childName.compare(AMBIENT) == 0) {
            m_LightService->SetAmbientLight(ReadVector(child), std::stof(ReadAttributeByName(child, "strength")));
        }
    }
}

std::shared_ptr<Transform> Scene::ReadTransform(pugi::xml_node transData) {
    std::shared_ptr<Transform> transform(new Transform());
    for (const auto& child : transData.children()) {
        std::string childName = child.name();
        if (childName.compare(TRANSFORM_POS) == 0) {
            transform->Position = ReadVector(child);
        }
        else if (childName.compare(TRANSFORM_ROT) == 0) {
            transform->Rotation = ReadVector(child);
        }
        else if (childName.compare(TRANSFORM_SCALE) == 0) {
            transform->Scale = ReadVector(child);
        }
    }
    return transform;
}

glm::vec3 Scene::ReadVector(pugi::xml_node matData) {
    glm::vec3 ret;

    for (auto attr = matData.attributes_begin(); attr != matData.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(VECTOR_X) == 0 || name.compare(VECTOR_R) == 0) {
            ret.x = std::stof(attr->value());
        }
        else if (name.compare(VECTOR_Y) == 0 || name.compare(VECTOR_G) == 0) {
            ret.y = std::stof(attr->value());
        }
        else if (name.compare(VECTOR_Z) == 0 || name.compare(VECTOR_B) == 0) {
            ret.z = std::stof(attr->value());
        }
    }
    return ret;
}

std::string Scene::ReadAttributeByName(pugi::xml_node node, std::string attrName) {
    for (auto attr = node.attributes_begin(); attr != node.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(attrName) == 0) {
            return attr->value();
        }
    }

    return "";
}

void Scene::AddModel(std::shared_ptr<Model> m) {
    m_Models.push_back(m);
}

void Scene::Activate() {
    m_Active = true;
}

void Scene::Deactivate() {
    m_Active = false;
}

bool Scene::IsActive() {
    return m_Active;
}

void Scene::Update() {
    if (!m_Loaded) return;
    for (std::shared_ptr<Model> model : m_Models) {
        model->Render(m_Camera.GetViewMatrix(), m_Camera.GetProjectionMatrix());
    }
}


