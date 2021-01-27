#pragma once

class Loader {
public:
    void LoadMesh(std::filesystem::path path);
private:
    void WriteShape(std::vector<Vertex> verts, std::vector<uint32_t> indices, std::string name, std::shared_ptr<MaterialData> matData);
    void WriteVec3(pugi::xml_node node, glm::vec3 vec);

    std::string m_Directory;
    pugi::xml_document m_Doc;

};

