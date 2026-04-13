#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include "../Domain/BakeService.h"

struct UIComponents {
    std::filesystem::path selectedFolder;
    std::vector<std::string> imageFiles;
    bool hasFolderSelected = false;
    std::map<std::string, BakeResult> bakedCache;
    int selectedFileIndex = -1; 
    char analysisResult[128] = "Color Analysis Not Available";
};

