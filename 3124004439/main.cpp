#include <iostream>
#include "simhash.h"

int main(int argc, char* argv[])
{
    // 参数检查：程序 原文路径 抄袭路径 输出路径
    if(argc != 4)
    {
        std::cerr << "Usage: main.exe orig.txt copy.txt ans.txt" << std::endl;
        return -1;
    }
    std::string origPath = argv[1];
    std::string copyPath = argv[2];
    std::string outPath = argv[3];

    std::string origText, copyText;
    if(!ReadFileContent(origPath, origText))
    {
        std::cerr << "Error: cannot open original file" << std::endl;
        return -2;
    }
    if(!ReadFileContent(copyPath, copyText))
    {
        std::cerr << "Error: cannot open copy file" << std::endl;
        return -3;
    }

    uint64_t hashOrig = CalcSimHash(origText);
    uint64_t hashCopy = CalcSimHash(copyText);
    double simRate = CalcSimilarity(hashOrig, hashCopy);

    if(!WriteResult(outPath, simRate))
    {
        std::cerr << "Error: cannot write output file" << std::endl;
        return -4;
    }
    return 0;
}
