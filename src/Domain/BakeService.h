#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <map>

struct BakeResult {
    float red;
    float green;
    float blue;
};

struct BakedEntry {
    char fileName[260];
    float r, g, b;
};

class BakeService {
    public:
        static BakeResult AnalyzeImage(const std::string& filePath);
        static void BakeFolder(const std::filesystem::path& folderPath, const std::vector<std::string>& files);
        static std::map<std::string, BakeResult> LoadMetadata(const std::filesystem::path& folderPath);
};