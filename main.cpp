#include "system_prog.hpp"

int main(int argc, char** argv) {
    std::string directory1 = argv[1];
    std::string directory2 = argv[2];
    double similarityThreshold = std::stoul(argv[3]);

    CompareDirectories(directory1, directory2, similarityThreshold);

    return 0;
}