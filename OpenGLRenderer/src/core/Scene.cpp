#include "pch.h"
#include "Scene.h"

Scene::Scene(std::string scenePath)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(scenePath.c_str());
    OGLR_ASSERT(result.status == 0, "FAILED TO READ SCENE");
    for (pugi::xml_node scene : doc.children("scene"))
    {
        for (pugi::xml_node child = scene.first_child(); child; child = child.next_sibling())
        {
            std::string name = child.name();
            std::cout << name << std::endl;

            if (name.compare(MODEL_ATTRIBUTE_NAME) == 0)
            {
                std::cout << "Model name is: " << child.attribute(MODEL_NAME.c_str()).value() << std::endl;
            }
        }
    }
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
