#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "myfunc.h"
#include "bin.h"
#include "testfunc.h"
// #include "testfunc.h"
using namespace std;

vector<Bin> callSolve(const vector<int>& input)
{
    int size = input[0];
    vector<int> minterms(input.begin()+2, input.end());
    vector<Bin> bins, ret;
    for (const auto& m : minterms) {
        bins.emplace_back(size, m);
    }
    startSolve(size, bins, minterms, ret);
    return ret;
}
// 좋은 테스트 케이스의 조건:
// 1. 겹치는 원소가 많아야 됨: row dominance
// 2. pi가 많이 나와야 됨 (비교적 크기가 작은 circle)

int main()
{
    vector<int> input = { 4, 10, 0, 1, 4, 5, 13, 15, 10, 11 };
    // vector<int> input1 = { 4, 12, 0, 1, 2, 3, 4, 6, 8, 9, 10, 11, 12, 14 };
    // vector<int> input2 = { 4, 10, 0, 1, 3, 4, 5, 7, 8, 10, 12, 14};
    // vector<int> input3 = { 4, 9, 4, 5, 6, 8, 9, 10, 12, 13, 14 };
    // vector<int> input4 = { 4, 11, 0, 1, 3, 4, 5, 7, 8, 12, 13, 14, 15};
    // vector<int> input5 = { 5, 18, 0, 1, 3, 4, 5, 7, 8, 12, 13, 14, 15, 17, 22, 23, 25, 27, 31 };
    vector<int> input6 = { 5, 24, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 17, 20, 21, 22, 23, 25, 26, 27, 30, 31 };
    vector<int> input7 = { 5, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 30, 31 };


    callSolve(input);
    // callSolve(input1);
    // callSolve(input2);
    // callSolve(input3);
    // callSolve(input4);
    // callSolve(input5);
    callSolve(input6);
    callSolve(input7);
    // callSolve(input8);
}