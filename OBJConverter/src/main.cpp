#include "pch.h"
#include "Loader.h"

void main() {
    std::string path;
    std::string ext(".obj");

    Log::Init();

    std::ifstream config("config.ini");
    getline(config, path);

    const std::filesystem::path pathObj = path;
    
    if (!std::filesystem::exists(path)) {
        OBJC_CORE_ERROR("DIRECTORY {0} does not exist", path);
        exit(-1);
    }

    std::vector<std::filesystem::path> objFiles;
    for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext) {
            std::cout << p.path() << '\n';
            objFiles.push_back(p.path());
        }
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < objFiles.size(); ++i) {
        threads.push_back(std::thread([&, i] {
            Loader l;
            l.LoadMesh(objFiles[i]);
        }));
    }

    for (auto it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }
}