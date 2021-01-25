#include "pch.h"

void main() {
    std::string path("assets\\");
    std::string ext(".obj");

    std::vector<std::filesystem::path> objFiles;
    for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext) {
            std::cout << p.path() << '\n';
            objFiles.push_back(p.path());
        }
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < objFiles.size(); ++i) {
        threads.push_back(std::thread([] {

        }));
    }

    for (auto it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }
}