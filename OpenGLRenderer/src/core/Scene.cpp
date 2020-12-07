#include "pch.h"
#include "Scene.h"

Scene::Scene(std::string scenePath)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(scenePath.c_str());
    OGLR_ASSERT(result.status == 0, "FAILED TO READ SCENE");

    for (pugi::xml_node scene : doc.children("scene"))
    {
        OGLR_CORE_INFO("============================");
        OGLR_CORE_INFO("LOADING SCENE: {0}", scene.attribute(SCENE_NAME.c_str()).value());
        OGLR_CORE_INFO("============================");
        for (pugi::xml_node child = scene.first_child(); child; child = child.next_sibling())
        {
            std::string name = child.name();

            // Add a new model
            if (name.compare(MODEL_ATTRIBUTE_NAME) == 0)
            {
                loadModel(child);
            }
        }
    }
}

void Scene::loadModel(pugi::xml_node modelNode)
{
    std::shared_ptr<Model> m(new Model(modelNode.name()));

    auto matData = modelNode.child("material");
    for (pugi::xml_node child1 = modelNode.first_child(); child1; child1 = child1.next_sibling())
    {
        std::string child1Name = child1.name();
        if (child1Name.compare(MATERIAL_ATTRIBUTE_NAME) == 0)
        {
            std::shared_ptr<Material> mat(new Material());

            for (pugi::xml_node child2 = child1.first_child(); child2; child2 = child2.next_sibling())
            {
                std::string child2Name = child2.name();
                if (child2Name.compare(SHADER_NAME) == 0)
                {
                    mat->SetShader(child2.first_child().value());
                }
                else if (child2Name.compare(TEXTURE_NAME) == 0)
                {
                    mat->AddTexture(child2.first_child().value());
                }
            }

            m->SetMaterial(mat);
        }
    }

    AddModel(m);
}

void Scene::AddModel(std::shared_ptr<Model> m)
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
    for (std::shared_ptr<Model> model : m_Models)
    {
        model->Update(m_Camera.GetViewMatrix(), m_Camera.GetProjectionMatrix());
    }
}


