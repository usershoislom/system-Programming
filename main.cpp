#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

// Функция для вычисления процента сходства двух строк
double CalculateSimilarity(const std::string& str1, const std::string& str2) {
    int len1 = str1.size();
    int len2 = str2.size();
    int maxLen = std::max(len1, len2);

    if (maxLen == 0) {
        return 100.0;  // Файлы пусты, считаем их идентичными
    }

    int commonLen = 0;
    for (int i = 0; i < len1; ++i) {
        if (i < len2 && str1[i] == str2[i]) {
            commonLen++;
        }
    }

    return static_cast<double>(commonLen) / maxLen * 100.0;
}

// Функция для сравнения файлов в двух директориях
void CompareDirectories(const std::string& dir1, const std::string& dir2, double similarityThreshold) {
    std::set<std::string> uniqueDir1;
    std::set<std::string> uniqueDir2;

    for (const auto& entry1 : std::filesystem::directory_iterator(dir1)) {
        if (entry1.is_regular_file()) {
            bool foundMatch = false; // Флаг для отслеживания наличия совпадений
            for (const auto& entry2 : std::filesystem::directory_iterator(dir2)) {
                if (entry2.is_regular_file()) {
                    std::ifstream file1(entry1.path());
                    std::ifstream file2(entry2.path());

                    std::string content1((std::istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());
                    std::string content2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());

                    double similarity = CalculateSimilarity(content1, content2);

                    if (similarity == 100.0) {
                        std::cout << entry1.path().string() << " - " << entry2.path().string() << std::endl;
                        foundMatch = true;
                    } else if (similarity >= similarityThreshold) {
                        std::cout << entry1.path().string() << " - " << entry2.path().string() << " - " << similarity << "%" << std::endl;
                        foundMatch = true;
                    }
                }
            }
            // Если совпадения не найдены, добавьте файл в соответствующий набор
            if (!foundMatch) {
                uniqueDir1.insert(entry1.path().string());
            }
        }
    }
    for (const auto& file : uniqueDir1) {
        std::cout << file << " ";
    }
    std::cout << uniqueDir1.size() <<" unique files in " << dir1 << std::endl;
    for (const auto& file : uniqueDir2) {
        std::cout << file << " ";
    }
    std::cout << uniqueDir2.size() <<" unique files in " << dir2 << std::endl;
}

int main(int argc, char** argv) {
    std::string directory1 = argv[1];
    std::string directory2 = argv[2];
    double similarityThreshold = std::stoul(argv[3]);

    CompareDirectories(directory1, directory2, similarityThreshold);

    return 0;
}