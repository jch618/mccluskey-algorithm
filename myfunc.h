#ifndef MYFUNC_H
#define MYFUNC_H
#include <vector>
#include <set>
#include <map>
#include "testfunc.h"
class Bin;
bool areCompressible(const Bin& b1, const Bin& b2);
bool binCompareByString(const Bin& b1, const Bin& b2);
/* */
void findPI(int size, std::vector<Bin> bins, std::vector<Bin>& pi);
std::vector<Bin> findEPI(const std::vector<Bin>& pi, const std::vector<int>& input);
std::vector<Bin> findNEPI(const std::vector<Bin>& pi, const std::vector<Bin>& epi);

std::vector<std::string> toStringVec(const std::vector<Bin>& bins);
//
void refineMinterms(const std::vector<Bin>& except, std::vector<int>& minterms);
bool isRowDominance(const Bin& b1, const Bin& b2, const std::vector<int>& minterms);
void findRowDominance(std::vector<Bin>& bins, const std::vector<int>& minterms);
void findColumnDominance(std::vector<Bin>& bins, std::vector<int>& minterms);
#endif