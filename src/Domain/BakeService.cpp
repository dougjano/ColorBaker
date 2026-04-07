#include "BakeService.h"

BakeResult BakeService::AnalyzeImage(const std::string& filePath) {

    int width, height, channels;
    unsigned char* pixels = nullptr;

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

    return {redCount / total, greenCount / total, blueCount / total};

};