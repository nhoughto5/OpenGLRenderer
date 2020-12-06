#include "pch.h"
#include "Scene.h"

Scene::Scene(std::string scenePath)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(scenePath.c_str());
    OGLR_ASSERT(result, "FAILED TO READ SCENE");
}

void Scene::AddModel(Model* m)
{
    m_Models.push_back(m);
}

void Scene::Activate()
{
    m_Active = true;
}

void Scene::Deactivate()
{
    m_Active = true;
}

bool Scene::IsActive()
{
    return m_Active;
}

void Scene::Update()
{
    for (Model* model : m_Models)
    {
        model->Update();
    }
}
