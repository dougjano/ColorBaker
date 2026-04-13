#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "BakeService.h"
#include <fstream>
#include <cstring>

BakeResult BakeService::AnalyzeImage(const std::string& filePath) {

    int width, height, channels;
    unsigned char* pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 3);

    long redCount = 0,  greenCount = 0, blueCount = 0;
    int stride = 10;

    for (int y = 0; y < height; y += stride) {
        int xOffset = (y / stride) % stride;

        for (int x = xOffset; x < width; x += stride) {
            int index = (y * width + x) * 3;
            int r = pixels[index];
            int g = pixels[index + 1];
            int b = pixels[index + 2];

            if (r >= g && r >= b) {
                redCount += 1;
            } else if (g >= b) {
                greenCount += 1;
            } else {
                blueCount += 1;
            }
        }
    }

    float total = (float)(redCount + greenCount + blueCount);

    stbi_image_free(pixels);

    return {redCount / total, greenCount / total, blueCount / total};

};

void BakeService::BakeFolder(const std::filesystem::path& folderPath, const std::vector<std::string>& files) {

    std::ofstream outFile(folderPath / "color_data.bin", std::ios::binary);

    if (!outFile) {
        return;
    }

    for (const auto& f : files) {
        BakeResult res = AnalyzeImage((folderPath / f).string());

        BakedEntry entry;
        std::strncpy(entry.fileName, f.c_str(), sizeof(entry.fileName));
        entry.r = res.red;
        entry.g = res.green;
        entry.b = res.blue;

        outFile.write(reinterpret_cast<const char*>(&entry), sizeof(BakedEntry));
    }
};

std::map<std::string, BakeResult> BakeService::LoadMetadata(const std::filesystem::path& folderPath) {
    
    std::map<std::string, BakeResult> cache;
    std::ifstream inFile(folderPath / "color_data.bin", std::ios::binary);

    if (!inFile) {
        return cache;
    }

    BakedEntry entry;

    while (inFile.read(reinterpret_cast<char*>(&entry), sizeof(BakedEntry))) {
        cache[std::string(entry.fileName)] = {entry.r, entry.g, entry.b};
    }

    return cache;
};