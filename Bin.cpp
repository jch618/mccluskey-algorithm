#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Bin.h"
using namespace std;

void print(vector<Bin>& bins);
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
    _nums.insert(_nums.end(), b._nums.begin(), b._nums.end());
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
ostream& operator<<(ostream& os, const Bin& bin)
{
    os << bin._binary;
    return os;
}
bool areCompressible(const Bin& b1, const Bin& b2)
{
    int cnt = 0;
    for (int i = 0; i < b1._size; i++) {
        if (b1._binary[i] != b2._binary[i]) {
            if ((b1._binary[i] == '2') && (b2._binary[i] == '2'))
                return false;
            cnt++;
        }
    }
    return (cnt == 1);
}
bool binCompare(const Bin& b1, const Bin& b2)
{
    return b1._binary < b2._binary;
}
vector<vector<pair<Bin, bool>>> makeMatrix(int size, vector<Bin> input)
{
    vector<vector<pair<Bin, bool>>> ret(size+1);
    for (auto& b : input) {
        ret[b.one()].push_back({b, false});
    }
    return ret;
}
void findPI(int size, vector<Bin> bins, vector<Bin>& pi)
{
    // cout << "start!" << endl;
    if (bins.empty()) return;
    auto vec = makeMatrix(size, bins);
    vector<Bin> ret;
    // print(bins);
    for (int i = 0; i+1 < vec.size(); i++) {
        for (auto& p1 : vec[i]) {
            for (auto& p2 : vec[i+1]) {
                if (areCompressible(p1.first, p2.first)) {
                    bool ok = true;
                    Bin bin = p1.first + p2.first;
                    for (const auto& b : ret) { //중복처리: hashmap이 나을듯??
                        if (b == bin) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        ret.push_back(p1.first + p2.first);
                        // cout << p1.first << '+' << p2.first << ':' << ret.back() << endl;
                    }
                    p1.second = p2.second = true;
                }
            }
        }  
    }
    for (const auto& pvec : vec) {
        for (const auto& p : pvec) {
            // cout << p.first << ':' << p.second << '\n';
            if (p.second == false) {
                pi.push_back(p.first);
            }
        }
    }
    findPI(size, ret, pi);
}
vector<Bin> findEPI(const vector<Bin>& pi, const vector<int>& input)
{
    vector<Bin> ret;
    for (int i = 2; i < input.size(); i++) {
        // cout << "num: " << input[i] << endl;
        int cnt = 0;
        int n = input[i];
        Bin bin;
        for (const auto& b : pi) {
            for (const auto& num : b.getNums()) {
                bool ok = false;
                if (num == n) {
                    bin = b;
                    cnt++;
                    break;
                }
            }
        }
        if (cnt == 1) {
            bool ok = true;
            for (const auto& b : ret) {
                if (bin == b)
                    ok = false;
            }
            // cout << "push_back:" << bin << endl;
            if (ok)
                ret.push_back(bin);
        }
    }
    return ret;
}
void print(vector<Bin>& bins)
{
    if (bins.empty()) {
        cout << "bins is empty.\n";
        return;
    }
    cout << '[';
    int i;
    for (i = 0; i < bins.size()-1; i++) {
        cout << '\"' << bins[i].getBinary() << "\", ";
    }
    cout << '\"' << bins[i].getBinary() << "\"]\n";
}
void printStringVec(vector<string>& vec)
{
    for (const auto& s : vec)
        cout << s << ' ';
    cout << endl;
}
vector<string> toStringVec(vector<Bin> bins)
{
    vector<string> vec;
    for (const auto& b : bins) {
        vec.push_back(b.getBinary());
    }
    return vec;
}