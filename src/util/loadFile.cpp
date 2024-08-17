#include "loadFile.h"
#include "../ui/etc/fileBar.h"
#include "../ui/css/cssLoader.h"
#include "../ui/editor/textEditor.h"
#include "util.h"
#include <filesystem>
#include <string>

void loadFileIntoDisk() {
    save_text_to_file(gBuffer, config_path + ".edit-" + std::filesystem::path(currentPath).filename().string());
}

std::string getFileFromDisk(std::string path) {
    std::string p = config_path + ".edit-" + path;
    if (std::filesystem::exists(p)) {
        return read_file_contents(p);
    } else {
        return "";
    }
}