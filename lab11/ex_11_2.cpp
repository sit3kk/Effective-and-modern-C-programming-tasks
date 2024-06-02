#include <iostream>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

void printDirectory(std::string_view path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        auto status = entry.status();
        auto file_type = status.type();
        char type_char = ' ';

        if (fs::is_directory(status)) {
            type_char = 'D';
        } else if (fs::is_regular_file(status)) {
            type_char = 'F';
        } else if (fs::is_symlink(status)) {
            type_char = 'L';
        }

        std::cout << "[" << type_char << "] " << entry.path().filename().string() 
                  << " " << fs::file_size(entry) << " bytes" << std::endl;
    }
}

void changeExtension(fs::path path, const std::string& fileNames, std::string_view newExtension) {
    std::regex pattern(fileNames);

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.status())) {
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, pattern)) {
                fs::path newFile = entry.path();
                newFile.replace_extension(newExtension);
                fs::copy(entry.path(), newFile);
            }
        }
    }
}

int main() {
    std::string directoryPath = "../test";
    

    if (!fs::exists(directoryPath)) {
        std::cerr << "Directory does not exist. Creating directory: " << directoryPath << std::endl;
        fs::create_directory(directoryPath);
    }

    std::cout << "Directory contents:" << std::endl;
    printDirectory(directoryPath);

    std::string regexPattern = R"(.*\.txt$)";
    std::string newExtension = ".bak";
    
    changeExtension(directoryPath, regexPattern, newExtension);

    std::cout << "\nDirectory contents after extension change:" << std::endl;
    printDirectory(directoryPath);

    return 0;
}