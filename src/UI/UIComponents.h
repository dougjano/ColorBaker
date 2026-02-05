#pragma once
#include <filesystem>

struct UIComponents {
    std::filesystem::path selectedFolder;
    std::vector<std::string> imageFiles;
    bool hasFolderSelected = false;
};

