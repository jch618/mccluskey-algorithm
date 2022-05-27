#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "bin.h"
using namespace std;

void Bin::setBinary(int n)
{
    string s(_size, '0');
    for (int i = _size-1; i >= 0; i--) {
        s[i] = n % 2 + '0';
        if (n % 2) 
            _one++;
        n /= 2;
    }
    _binary = s;
    _binarys.push_back(s);
}
Bin& Bin::operator+=(const Bin& b)
{
    for (int i = 0; i < _size; i++)
        if (_binary[i] != b._binary[i]) {
            _binary[i] = '2';
        }
    // vector 이어 붙이기
    _binarys.insert(_binarys.end(), b._binarys.begin(), b._binarys.end());
    // _nums.insert(_nums.end(), b._nums.begin(), b._nums.end());
    for (const auto& n : b._nums)
        _nums.insert(n);
    return *this;
}
string Bin::getBinary() const
{
    string s(_binary);
    replace(s.begin(), s.end(), '2', '-');
    return s;
}
Bin operator+(Bin b1, const Bin& b2)
{
    b1 += b2;
    return b1;
}
bool operator==(const Bin& b1, const Bin& b2)
{
    return b1._binary == b2._binary;
}
bool operator!=(const Bin& b1, const Bin& b2)
{
    return !(b1 == b2);
}
std::ostream& operator<<(std::ostream& os, const Bin& bin)
{
    os << bin.getBinary();
    return os;
}

