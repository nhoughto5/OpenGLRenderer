#include "pch.h"
#include "Scene.h"

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
