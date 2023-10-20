#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;


bool identical(const std::string& file1_path, const std::string& file2_path) {
    std::ifstream file1(file1_path, std::ios::binary);
    std::ifstream file2(file2_path, std::ios::binary);

    if (!file1.is_open() || !file2.is_open()) {
        return false;
    }
    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> end1;
    std::istreambuf_iterator<char> begin2(file2);
    std::istreambuf_iterator<char> end2;

    return equal(begin1, end1, begin2, end2);
}

std::string construct_full_path(const std::string& dir_path, const std::string& file_name) {
    return dir_path + file_name;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " dir1 dir2" << std::endl;
        return 1;
    }

    std::string dir1_path = argv[1];
    std::string dir2_path = argv[2];
    uint64_t similarity = std::stoull(argv[3]);

    std::vector<std::string> dir1_files;
    std::vector<std::string> dir2_files;

    // Получаем список файлов из первой директории
    for (const auto& entry : fs::directory_iterator(dir1_path)) {
        if (entry.is_regular_file()) {
            dir1_files.push_back(entry.path().filename().string());
            //std::cout << entry.path().filename().string() << "\n";
        }
    }

    // Получаем список файлов из второй директории
    for (const auto& entry : fs::directory_iterator(dir2_path)) {
        if (entry.is_regular_file()) {
            dir2_files.push_back(entry.path().filename().string());
            //std::cout<< "Test: " << entry.path().filename().string() << "\n";
        }
    }

    // Проходим по списку файлов из первой директории и ищем совпадения во второй директории
    for (const auto& file1 : dir1_files) {
        for (const auto& file2 : dir2_files) {
            if (identical(construct_full_path(dir1_path, file1), construct_full_path(dir2_path, file2))) {
                std::cout << construct_full_path(dir1_path, file1) << " - " << construct_full_path(dir2_path, file2) << std::endl;
            }
        }
    }

    // Find elements in vec1 that are not in vec2
    for (const auto& file : dir1_files) {
        if (std::find(dir2_files.begin(), dir2_files.end(), file) == dir2_files.end()) {
            std::cout << file << " ";
        }
    }
    std::cout << std::endl;

    // Find elements in vec2 that are not in vec1
    for (const auto& file : dir2_files) {
        if (std::find(dir1_files.begin(), dir1_files.end(), file) == dir1_files.end()) {
            std::cout << file << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}