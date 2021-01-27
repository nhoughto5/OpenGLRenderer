#pragma once

class Loader {
public:
    void static LoadMesh(std::filesystem::path path);
private:
    void static WriteShape(std::vector<Vertex> verts, std::vector<uint32_t> indices, std::string name, std::shared_ptr<MaterialData> matData, std::string directory);
};

