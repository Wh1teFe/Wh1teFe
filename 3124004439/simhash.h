#ifndef SIMHASH_H
#define SIMHASH_H
#include <string>
#include <vector>
#include <cstdint>

std::vector<std::string> SplitNgram(const std::string& text, int n = 3);
uint64_t CalcSimHash(const std::string& text);
int HammingDistance(uint64_t hash1, uint64_t hash2);
double CalcSimilarity(uint64_t hash1, uint64_t hash2);
bool ReadFileContent(const std::string& filePath, std::string& outContent);
bool WriteResult(const std::string& filePath, double rate);
#endif
