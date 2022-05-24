#ifndef BIN_H
#define BIN_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bin {
friend Bin operator+(Bin b1, const Bin& b2);
friend ostream& operator<<(ostream& os, const Bin& b);
friend bool operator==(const Bin& b1, const Bin& b2);
friend bool operator!=(const Bin& b1, const Bin& b2);
friend bool areCompressible(const Bin& b1, const Bin& b2);
friend bool binCompare(const Bin& b1, const Bin& b2);
    int _size;
    string _binary;
    vector<string> _binarys;
    vector<int> _nums;
    int _one;
public:
    Bin(int s=0, int n=0): _size(s), _one(0) { _nums.push_back(n); setBinary(n); }
    Bin(const Bin& b): _size(b._size), _binary(b._binary), _binarys(b._binarys), _nums(b._nums), _one(b._one) {}
    void setBinary(int n);
    string getBinary() const;
    vector<string> getBinarys() const { return _binarys; }
    vector<int> getNums() const { return _nums; }
    int getSize() const { return _size; }
    int getCircleSize() const { return _binarys.size(); }
    int one() const { return _one; }
    Bin& operator+=(const Bin& b);
    char operator[](int index) const { return _binary[index]; }
};

Bin operator+(Bin b1, const Bin& b2);
bool operator==(const Bin& b1, const Bin& b2);
bool operator!=(const Bin& b1, const Bin& b2);
ostream& operator<<(ostream& os, const Bin& bin);
bool areCompressible(const Bin& b1, const Bin& b2);
bool binCompare(const Bin& b1, const Bin& b2);
vector<vector<pair<Bin, bool>>> makeMatrix(int size, vector<Bin> input);
void findPI(int size, vector<Bin> bins, vector<Bin>& pi);
vector<Bin> findEPI(const vector<Bin>& pi, const vector<int>& input);
void print(vector<Bin>& bins);
void printStringVec(vector<string>& vec);
vector<string> toStringVec(vector<Bin> bins);
vector<string> solution(vector<int> minterm);
#endif