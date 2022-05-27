#ifndef BIN_H
#define BIN_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "myfunc.h"
// #include "testfunc.h"

class Bin { // std 빼먹지 말기
friend Bin operator+(Bin b1, const Bin& b2);
friend std::ostream& operator<<(std::ostream& os, const Bin& b);
friend bool operator==(const Bin& b1, const Bin& b2);
friend bool operator!=(const Bin& b1, const Bin& b2);
friend bool areCompressible(const Bin& b1, const Bin& b2);
friend bool binCompareByString(const Bin& b1, const Bin& b2);
// friend bool isIncluded(const Bin& b1, const Bin& b2);
friend void refineMinterms(const std::vector<Bin>& except, std::vector<int>& minterms);
friend void printTable(const std::vector<Bin>& bins, const std::vector<int>& minterms);
friend void printTable(const std::map<int, std::set<std::string>>& table, const std::vector<Bin>& bin);
friend void findRowDominance(std::vector<Bin>& bins, std::vector<Bin>& epi);
friend void findColumnDominance(std::vector<Bin>& bins, std::vector<int>& minterms);
    int _size;
    std::string _binary;
    std::vector<std::string> _binarys;
    //std::vector<int> _nums;
    std::set<int> _nums;
    int _one;
public:
    bool checked = false;
    Bin(int s=0, int n=0): _size(s), _one(0) { _nums.insert(n); setBinary(n); }
    Bin(const Bin& b): _size(b._size), _binary(b._binary), _binarys(b._binarys), _nums(b._nums), _one(b._one) {}
    void setBinary(int n);
    std::string getBinary() const;
    std::vector<std::string> getBinarys() const { return _binarys; }
    // std::vector<int> getNums() const { return _nums; }
    std::set<int> getNums() const { return _nums; }
    int getSize() const { return _size; }
    int getCircleSize() const { return _binarys.size(); }
    int one() const { return _one; }
    Bin& operator+=(const Bin& b);
    char operator[](int index) const { return _binary[index]; }
    void setTrue() { checked = true; }
};

Bin operator+(Bin b1, const Bin& b2);
bool operator==(const Bin& b1, const Bin& b2);
bool operator!=(const Bin& b1, const Bin& b2);
std::ostream& operator<<(std::ostream& os, const Bin& bin);
bool areCompressible(const Bin& b1, const Bin& b2);

// std::vector<std::vector<pair<Bin, bool>>> makeMatrix(int size, std::vector<Bin> input);
std::vector<std::vector<Bin>> makeMatrix(int size, const std::vector<Bin>& input);
// bool isIncluded(const Bin& b1, const Bin& b2);
#endif