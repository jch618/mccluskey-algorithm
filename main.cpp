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
int main()
{
    vector<int> input = { 3, 6, 0, 1, 2, 5, 6, 7 };
    vector<int> input2 = { 3, 4, 0, 1, 2, 3 };
    vector<int> input3 = { 3, 8, 0, 1, 2, 3, 4, 5, 6, 7};
    vector<int> input4 = { 1, 2, 1, 0 };
    vector<int> input5 = { 0, 0 };
    vector<int> input6 = { 6, 29, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    vector<int> input7 = { 4, 8, 0, 4, 8, 10, 12, 11, 13, 15 };

    // callSolve(input);
    // callSolve(input2);
    // callSolve(input3);
    // callSolve(input4);
    // callSolve(input5);
    callSolve(input6);
    // callSolve(input7);
}