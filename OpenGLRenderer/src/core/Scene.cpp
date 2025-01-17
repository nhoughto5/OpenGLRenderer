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
            else if (name.compare(LIGHTS) == 0) {
                loadLight(child);
            }
            else if (name.compare(SKYBOX_NAME) == 0) {
                m_Skybox = std::make_shared<Skybox>(ReadAttributeByName(child, SRC_FOLDER));
                m_Skybox->SetTransform(ReadTransform(child.child(TRANSFORM.c_str())));
            }
        }
    }

    Application::Get().Subscribe(&m_Camera);
    m_LightService->CreateShadowmaps();
    m_Loaded = true;

    d_Shader.SetShaderFileName("debug.glsl");
    setupDebugTexture();
}

void Scene::loadGrid(pugi::xml_node node) {
    auto gridName = node.attribute(ATTR_SIZE.c_str()).value();
    AddModel(gridName, std::make_shared<Grid>(std::stoi(gridName)));
}

void Scene::loadModel(pugi::xml_node modelNode) {
    std::shared_ptr<Model> m(new Model(modelNode.name()));
    std::string meshPath = modelNode.attribute(MESH_ATTRIBUTE_NAME.c_str()).value();

    auto fromMap = m_Models.find(meshPath);
    if (fromMap != m_Models.end()) {
        fromMap->second->AddTransform(ReadTransform(modelNode.child(TRANSFORM.c_str())));
    }
    else {
        m->SetMesh(meshPath);

        m->AddTransform(ReadTransform(modelNode.child(TRANSFORM.c_str())));

        AddModel(meshPath, m);
    }
}

void Scene::loadLight(pugi::xml_node node) {
    for (const auto& child : node.children()) {
        std::string childName = child.name();
        if (childName.compare(AMBIENT) == 0) {
            m_LightService->SetAmbientLight(ReadVector(child), std::stof(ReadAttributeByName(child, "strength")));
        }
        else if (childName.compare(LIGHT) == 0) {
            std::shared_ptr<Light> light(new Light());
            bool dirSet = false, posSet = false, cutoffSet = false;
            for (const auto& child2 : child.children()) {
                std::string childName2 = child2.name();
                if (childName2.compare(TRANSFORM_POS) == 0) {
                    light->position = ReadVector(child2);
                    posSet = true;
                }
                else if (childName2.compare(ATTENUATION) == 0) {
                    light->attenuation = ReadVector(child2);
                }
                else if (childName2.compare(DIRECTION) == 0) {
                    light->direction = ReadVector(child2);
                    dirSet = true;
                }
                else if (childName2.compare(CUTOFF) == 0) {
                    light->innerAngle = child2.attribute(INNERANGLE.c_str()).as_float();
                    light->outerAngle = child2.attribute(OUTERANGLE.c_str()).as_float();
                    cutoffSet = true;
                }
                else if (childName2.compare(SHADOWS) == 0) {
                    light->generatesShadows = true;
                }
                else if (childName2.compare(COLOR) == 0) {
                    light->color = ReadVector(child2);
                    light->strength = std::stof(ReadAttributeByName(child2, STRENGTH));
                }
            }

            if (cutoffSet && posSet && dirSet) {
                light->isSpotLight = true;
                light->isPointLight = true;
            }
            else if (posSet && !dirSet) {
                light->isSpotLight = false;
                light->isPointLight = true;
            }
            else {
                light->isSpotLight = false;
                light->isPointLight = false;
            }

            m_LightService->AddLight(light);

            if (light->isPointLight) {
                std::shared_ptr<Model> m(new Model("PointLight"));
                m->SetMesh("light/");
                std::shared_ptr<Transform> transform(new Transform());
                transform->Position = light->position;
                transform->Scale = glm::vec3(0.05, 0.05, 0.05);
                transform->Rotation = glm::vec3(180, 0, 0);
                m->AddTransform(transform);
                AddModel("light/light.obj", m);
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
    return node.attribute(attrName.c_str()).value();
}

void Scene::AddModel(std::string modelName, std::shared_ptr<Model> m) {
    m_Models[modelName] = m;
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

    if (m_Skybox != nullptr) {
        m_Skybox->Render(m_Camera.GetViewMatrix(), m_Camera.GetProjectionMatrix());
    }

    m_LightService->StartShadowRender();
    for (const auto& light : m_LightService->GetLights())
    {
        if (light->generatesShadows)
        {
            for (const auto& item : m_Models) {
                for (const auto& instance : item.second->GetModelMatrices())
                {
                    m_LightService->SetShadowModelMatrix(instance);
                    m_LightService->SetShadowLightTransport(light->GetViewMatrix() * light->GetProjectionMatrix());
                    item.second->RenderShadows();
                }
            }
        }
    }
    m_LightService->EndShadowRender();


    //auto l = m_LightService->GetLights();
    //for (const auto item : m_Models) {
    //    //item.second->Render(l[0]->GetViewMatrix(), m_Camera.GetProjectionMatrix());
    //    //item.second->Render(l[0]->GetViewMatrix(), l[0]->GetProjectionMatrix());
    //    item.second->Render(m_Camera.GetViewMatrix(), m_Camera.GetProjectionMatrix());
    //}

    renderDebugTexture();
}

void Scene::setupDebugTexture() {
    glGenVertexArrays(1, &d_VAO);
    glBindVertexArray(d_VAO);

    static const GLfloat g_quad_vertex_buffer_data[] = {
    -0.5f, -0.5f, 0.0, 0.0,
     0.5f, -0.5f, 1.0, 0.0,
     0.5f,  0.5f, 1.0, 1.0,

     -0.5f, -0.5f, 0.0, 0.0,
     0.5f,  0.5f, 1.0, 1.0,
     -0.5f, 0.5, 0.0, 1.0
    };

    glGenBuffers(1, &d_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, d_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    d_Shader.Bind();
    d_Texture = std::make_shared<Texture>("skull/skull.jpg", d_Shader.ShaderId(), "debugTexture", 0);
}

void Scene::renderDebugTexture() {
    d_Shader.Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, d_Texture->Id());
    glBindVertexArray(d_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}