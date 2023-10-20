//#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

// Функция для вывода оригинальных файлов из каждой директории
void PrintUniqueFiles(const std::string&, const std::string&, std::set<std::string>);

// Функция для вычисления процента сходства двух строк
double CalculateSimilarity(const std::string&, const std::string&);

// Функция для сравнения файлов в двух директориях и их вывода
void CompareDirectories(const std::string&, const std::string&, double);