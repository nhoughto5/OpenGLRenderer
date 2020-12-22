#include "pch.h"
#include "Application.h"
#include "Scene.h"

Scene::Scene(std::string scenePath) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(scenePath.c_str());
    OGLR_ASSERT(result.status == 0, "FAILED TO READ SCENE");

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
            else if (name.compare(AMBIENT)) {
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

    for (auto attr = modelNode.attributes_begin(); attr != modelNode.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(MESH_ATTRIBUTE_NAME) == 0) {
            m->SetMesh(attr->value());
        }
    }

    for (const auto& child : modelNode.children()) {
        std::string childName = child.name();
        if (childName.compare(MATERIAL_ATTRIBUTE_NAME) == 0) {
            m->SetMaterial(ReadMaterial(child));
        }
        else if (childName.compare(TRANSFORM) == 0) {
            m->SetTransform(ReadTransform(child));
        }
    }

    AddModel(m);
}

void Scene::loadLight(pugi::xml_node node) {
    for (const auto& child : node.children()) {
        std::string childName = child.name();
        if (childName.compare(AMBIENT) == 0) {

        }
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

std::shared_ptr<Material> Scene::ReadMaterial(pugi::xml_node matData) {
    std::shared_ptr<Material> mat(new Material());
    for (const auto& child : matData.children()) {
        std::string child2Name = child.name();
        if (child2Name.compare(SHADER_NAME) == 0) {
            mat->SetShader(child.first_child().value());
        }
        else if (child2Name.compare(TEXTURE_NAME) == 0) {
            mat->AddTexture(child.first_child().value());
        }
    }

    return mat;
}

glm::vec3 Scene::ReadVector(pugi::xml_node matData) {
    glm::vec3 ret;

    for (auto attr = matData.attributes_begin(); attr != matData.attributes_end(); attr++) {
        std::string name = attr->name();
        if (name.compare(VECTOR_X) == 0) {
            ret.x = std::stof(attr->value());
        }
        else if (name.compare(VECTOR_Y) == 0) {
            ret.y = std::stof(attr->value());
        }
        else if (name.compare(VECTOR_Z) == 0) {
            ret.z = std::stof(attr->value());
        }
    }
    return ret;
}

void Scene::AddModel(std::shared_ptr<Model> m) {
    m_Models.push_back(m);
}

void Scene::Activate() {
    m_Active = true;
}

void Scene::Deactivate() {
    m_Active = true;
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


