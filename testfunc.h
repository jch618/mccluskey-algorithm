#ifndef TESTFUNC_H
#define TESTFUNC_H
#include <iostream>
#include <algorithm>
#include "bin.h"
class Bin;

void testAreCompressible();
void testBinCompare();
void testIsIncluded();
void testSetMinterms();
void testFindColumnDominance();

void solve(std::vector<Bin>& pi, std::vector<int>& minterms, std::vector<Bin>& ret);
void startSolve(int size, std::vector<Bin>& bins, std::vector<int>& minterms, std::vector<Bin>& ret);

void print(const std::vector<Bin>& bins);
void print(const std::vector<int>& minterms);
void printStringVec(std::vector<std::string>& vec);
void printPIAndMinterms(const std::vector<Bin>& pi, const std::vector<int>& minterms);
void printTable(const std::vector<Bin>& bins, const std::vector<int>& minterms);
void printTable(const std::map<int, std::set<std::string>>& table, const std::vector<Bin>& bin);
#endif