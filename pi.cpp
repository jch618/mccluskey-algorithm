#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
void compress(int size, vector<Bin> bins, vector<Bin>& pi)
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
    compress(size, ret, pi);
}
void print(vector<Bin>& bins)
{
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
vector<string> solution(vector<int> minterm) {
    int size = minterm[0];
    int N = minterm[1];
    vector<Bin> bins;
    for (int i = 0; i < N; i++)
        bins.emplace_back(size, minterm[i+2]); //empalce_back: 생성자 호출 가능
    // print(bins);
    vector<Bin> ret;
    compress(size, bins, ret);
    sort(ret.begin(), ret.end(), binCompare);
    // print(ret);
    vector<string> pi = toStringVec(ret);
    return pi;
}
int main()
{
    vector<int> input = { 6, 32, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    // vector<int> input = { 4, 16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    // vector<int> input = { 5, 32, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

    vector<string> ret = solution(input);
    printStringVec(ret);
}