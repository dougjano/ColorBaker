#pragma once
#include <filesystem>

struct UIComponents {
    std::filesystem::path selectedFolder;
    std::vector<std::string> imageFiles;
    bool hasFolderSelected = false;
    int selectedFileIndex = -1; 
    char analysisResult[128] = "No analysis performed";
};

