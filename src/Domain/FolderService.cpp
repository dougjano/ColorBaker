#include "FolderService.h"

std::vector<std::string> FolderService::ScanForImages(const std::filesystem::path& folderPath){
    std::vector<std::string> names;

    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        return names;
    }

    for (const auto& entity : std::filesystem::directory_iterator(folderPath)) {
        if (entity.is_regular_file()) {
            std::string ext = entity.path().extension().string();

            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg") {
                names.push_back(entity.path().filename().string());
            }
        }
    }

    return names;
}