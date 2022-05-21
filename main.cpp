#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Bin.h"
using namespace std;
vector<string> solution(vector<int> minterm) {
    int size = minterm[0];
    int N = minterm[1];
    vector<Bin> bins;
    for (int i = 0; i < N; i++)
        bins.emplace_back(size, minterm[i+2]); //empalce_back: 생성자 호출 가능
    // print(bins);
    vector<Bin> ret;
    findPI(size, bins, ret);
    sort(ret.begin(), ret.end(), binCompare);
    vector<string> pi = toStringVec(ret);
    // print(ret);

    vector<Bin> ret2 = findEPI(ret, minterm);
    vector<string> epi = toStringVec(ret2);
    // print(ret2);
    pi.push_back("EPI");
    pi.insert(pi.end(), epi.begin(), epi.end());
    return pi;
}
int main()
{
    vector<int> input = { 3, 6, 0, 1, 2, 5, 6, 7 };
    vector<int> input2 = { 3, 4, 0, 1, 2, 3 };
    vector<int> input3 = { 3, 8, 0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> input4 = { 1, 2, 1, 0 };
    vector<int> input5 = { 0, 0 };
    vector<string> ret = solution(input);
    vector<string> ret2 = solution(input2);
    vector<string> ret3 = solution(input3);
    vector<string> ret4 = solution(input4);
    vector<string> ret5 = solution(input5);
    printStringVec(ret);
    printStringVec(ret2);
    printStringVec(ret3);
    printStringVec(ret4);
    printStringVec(ret5);
}