#include "system_prog.hpp"

void PrintUniqueFiles(const std::string& dir1, const std::string& dir2, std::set<std::string> common) {
    for (const auto& entry : std::filesystem::directory_iterator(dir1)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().string();
            if (common.find(filename) == common.end()) {
                std::cout << filename << " ";
            }
        }
    }
    for (const auto& entry : std::filesystem::directory_iterator(dir2)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().string();
            if (common.find(filename) == common.end()) {
                std::cout << filename << " ";
            }
        }
    }
}

double CalculateSimilarity(const std::string& str1, const std::string& str2) {
    size_t len1 = str1.size();
    size_t len2 = str2.size();
    size_t maxLen = std::max(len1, len2);

    if (maxLen == 0) {
        return 100.0;  // Файлы пусты, считаем их идентичными
    }

    size_t commonLen = 0;
    for (size_t i = 0; i < len1; ++i) {
        if (i < len2 && str1[i] == str2[i]) {
            ++commonLen;
        }
    }

    return static_cast<double>(commonLen) / maxLen * 100.0;
}

void CompareDirectories(const std::string& dir1, const std::string& dir2, double similarityThreshold) {
    std::set<std::string> uniqueDir1;
    std::set<std::string> uniqueDir2;
    std::set<std::string> common;

    for (const auto& entry1 : std::filesystem::directory_iterator(dir1)) {
        if (entry1.is_regular_file()) {
            for (const auto& entry2 : std::filesystem::directory_iterator(dir2)) {
                if (entry2.is_regular_file()) {
                    std::ifstream file1(entry1.path());
                    std::ifstream file2(entry2.path());

                    std::string content1((std::istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());
                    std::string content2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());

                    double similarity = CalculateSimilarity(content1, content2);

                    if (similarity == 100.0) {
                        std::cout << entry1.path().string() << " - " << entry2.path().string() << std::endl;
                        common.insert(entry1.path().string());
                        common.insert(entry2.path().string());
                    } else if (similarity >= similarityThreshold) {
                        std::cout << entry1.path().string() << " - " << entry2.path().string() << " - " << similarity
                                  << "%" << std::endl;
                        common.insert(entry1.path().string());
                        common.insert(entry2.path().string());
                    }
                }
            }
        }
    }
    PrintUniqueFiles(dir1, dir2, common);
}
