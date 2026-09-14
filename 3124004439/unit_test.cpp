#include <iostream>
#include <cassert>
#include "simhash.h"

void Test1_SameText()
{
    std::string s1 = "今天是星期天，天气晴，今天晚上我要去看电影。";
    std::string s2 = "今天是星期天，天气晴，今天晚上我要去看电影。";
    uint64_t h1 = CalcSimHash(s1);
    uint64_t h2 = CalcSimHash(s2);
    double r = CalcSimilarity(h1,h2);
    assert(r > 0.99);
    std::cout << "Test1 Pass" << std::endl;
}

void Test2_SimilarText()
{
    std::string s1 = "今天是星期天，天气晴，今天晚上我要去看电影。";
    std::string s2 = "今天是周天，天气晴朗，我晚上要去看电影。";
    uint64_t h1 = CalcSimHash(s1);
    uint64_t h2 = CalcSimHash(s2);
    double r = CalcSimilarity(h1,h2);
    assert(r > 0.5);
    std::cout << "Test2 Pass" << std::endl;
}

void Test3_EmptyOrig()
{
    std::string s1 = "";
    std::string s2 = "测试文本";
    uint64_t h1 = CalcSimHash(s1);
    uint64_t h2 = CalcSimHash(s2);
    double r = CalcSimilarity(h1,h2);
    std::cout << "Test3 Pass" << std::endl;
}

void Test4_AllDifferent()
{
    std::string s1 = "人工智能";
    std::string s2 = "篮球足球羽毛球";
    uint64_t h1 = CalcSimHash(s1);
    uint64_t h2 = CalcSimHash(s2);
    double r = CalcSimilarity(h1,h2);
    assert(r < 0.3);
    std::cout << "Test4 Pass" << std::endl;
}

void Test5_FileRead()
{
    std::string tmp;
    bool ok = ReadFileContent("not_exist.txt", tmp);
    assert(ok == false);
    std::cout << "Test5 Pass" << std::endl;
}

int main()
{
    Test1_SameText();
    Test2_SimilarText();
    Test3_EmptyOrig();
    Test4_AllDifferent();
    Test5_FileRead();
    std::cout << "All unit test finished!" << std::endl;
    return 0;
}
