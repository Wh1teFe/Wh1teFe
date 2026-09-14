#ifndef SIMHASH_H
#define SIMHASH_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

class SimHash {
public:
    // 分词，简单按标点符号切分
    static std::vector<std::string> SplitNgram(const std::string& text);
    // 计算simhash指纹 64bit
    static uint64_t CalcSimHash(const std::string& text);
    // 计算汉明距离
    static int HammingDistance(uint64_t hash1, uint64_t hash2);
    // 根据汉明距离得到相似度 0~1
    static double GetSimilarity(uint64_t hash1, uint64_t hash2);
    // 读取文件全部文本
    static std::string ReadFile(const std::string& filePath);
    // 写入结果文件
    static void WriteResult(const std::string& filePath, double sim);
};

#endif
