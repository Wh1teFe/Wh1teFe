#include "simhash.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>

// 滑动窗口n-gram分词
std::vector<std::string> SplitNgram(const std::string& text, int n)
{
    std::vector<std::string> res;
    if (text.size() < (size_t)n)
    {
        res.push_back(text);
        return res;
    }
    for (size_t i = 0; i <= text.size() - n; ++i)
    {
        res.push_back(text.substr(i, n));
    }
    return res;
}

// 简单哈希，转为64bit
static uint64_t HashStr(const std::string& s)
{
    std::hash<std::string> hasher;
    return hasher(s);
}

uint64_t CalcSimHash(const std::string& text)
{
    std::vector<std::string> tokens = SplitNgram(text,3);
    std::vector<int> weight(64,0);

    for(auto& token : tokens)
    {
        uint64_t h = HashStr(token);
        for(int i=0;i<64;i++)
        {
            if(h & (1ULL << i))
                weight[i]++;
            else
                weight[i]--;
        }
    }
    uint64_t fingerprint = 0;
    for(int i=0;i<64;i++)
    {
        if(weight[i]>0)
            fingerprint |= (1ULL << i);
    }
    return fingerprint;
}

int HammingDistance(uint64_t hash1, uint64_t hash2)
{
    uint64_t xorVal = hash1 ^ hash2;
    return __builtin_popcountll(xorVal);
}

double CalcSimilarity(uint64_t hash1, uint64_t hash2)
{
    int dist = HammingDistance(hash1, hash2);
    return 1.0 - dist / 64.0;
}

bool ReadFileContent(const std::string& filePath, std::string& outContent)
{
    std::ifstream fin(filePath);
    if(!fin.is_open())
        return false;
    std::stringstream buffer;
    buffer << fin.rdbuf();
    outContent = buffer.str();
    fin.close();
    return true;
}

bool WriteResult(const std::string& filePath, double rate)
{
    std::ofstream fout(filePath);
    if(!fout.is_open())
        return false;
    fout.precision(2);
    fout << std::fixed << rate << std::endl;
    fout.close();
    return true;
}
