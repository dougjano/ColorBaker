#pragma once
#include <vector>
#include <string>
#include <filesystem>

class FolderService {
    public:
        static std::vector<std::string> ScanForImages(const std::filesystem::path& folderPath);
};