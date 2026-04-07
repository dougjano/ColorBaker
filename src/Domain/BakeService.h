#pragma once
#include <string>
#include <vector>

struct BakeResult
{
    float red;
    float green;
    float blue;
};

class BakeService {
    public:
        static BakeResult AnalyzeImage(const std::string& filePath);
};