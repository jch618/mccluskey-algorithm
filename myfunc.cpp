#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "bin.h"
#include "myfunc.h"
using namespace std;

bool areCompressible(const Bin& b1, const Bin& b2)
{
    int cnt = 0;
    for (int i = 0; i < b1._size; i++) {
        if (b1._binary[i] != b2._binary[i]) {
            if ((b1._binary[i] == '2') || (b2._binary[i] == '2')) {
                return false;
            }
            cnt++;
        }
    }
    return (cnt == 1);
}

bool binCompareByString(const Bin& b1, const Bin& b2)
{
    return b1._binary < b2._binary;
}

vector<vector<Bin>> makeMatrix(int size, const vector<Bin>& input)
{
    vector<vector<Bin>> ret(size+1);
    for (auto& b : input) {
        ret[b.one()].push_back(b);
    }
    return ret;
}

void findPI(int size, vector<Bin> bins, vector<Bin>& pi) // circle 뭉치기
{
    // cout << "start!" << endl;
    if (bins.empty()) return;
    auto vec = makeMatrix(size, bins);
    vector<Bin> ret;
    // print(bins);
    for (int i = 0; i+1 < vec.size(); i++) {
        for (auto& b1 : vec[i]) {
            for (auto& b2 : vec[i+1]) {
                if (areCompressible(b1, b2)) {
                    bool ok = true;
                    Bin bin = b1 + b2;
                    for (const auto& b : ret) { // 중복일 경우 추가하지 않음
                        if (b == bin) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        ret.push_back(bin);
                    }
                    b1.checked = b2.checked = true;
                }
            }
        }  
    }
    for (const auto& v : vec) {
        for (const auto& b : v) {
            if (!b.checked) {
                pi.push_back(b);
            }
        }
    }
    findPI(size, ret, pi);
}

vector<Bin> findEPI(const vector<Bin>& pi, const vector<int>& minterms)
{
    vector<Bin> ret;
    for (const auto& n : minterms) { // input == [ size, minterm, m1(int), m2, ... ]
        // cout << "num: " << input[i] << endl;
        int cnt = 0;
        Bin bin;
        for (const auto& b : pi) { // 해당 minterm이 pi 원소들 중 하나에만 속하는 수인지 확인한다.
            for (const auto& num : b.getNums()) {
                if (num == n) { 
                    bin = b;
                    cnt++;
                    break; // 그 다음 bin으로
                }
            }
        }
        if (cnt == 1) { // input[i]를 포함하고 있던 bin이 하나일 경우:
            bool ok = true;
            // 아래 for문을 checked 이용해서 바꿀 수 있을 것 같다.
            for (const auto& b : ret) { // epi가 중복일 경우 추가 안함 ex) 7도 8도 혼자 갖고 있으면 두 번 조건 만족.
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

// epi에 속하지 않는 pi들을 return
vector<Bin> findNEPI(const vector<Bin>& pi, const vector<Bin>& epi)
{
    vector<Bin> nepi;
    for (const auto& p : pi) { 
        bool ok = true;
        for (const auto& e : epi) {
            if (p == e) {
                ok = false;
            }
        }
        if (ok) {
            nepi.push_back(p);
        }
    }
    return nepi;
}

vector<string> toStringVec(const vector<Bin>& bins)
{
    vector<string> vec;
    for (const auto& b : bins) {
        vec.push_back(b.getBinary());
    }
    return vec;
}

// except에 속하지 않는 minterm들을 가지는 벡터 리턴
void refineMinterms(const vector<Bin>& except, vector<int>& minterms) //epi에 속한 minterm들을 삭제한다.
{
    for (const auto& b : except) {
        for (const auto& n : b._nums) {
            auto delPos = find(minterms.begin(), minterms.end(), n);
            if (delPos != minterms.end()) {
                minterms.erase(delPos);
            }
        }
    }
}

inline void setBoolTrue(vector<Bin>& bins)
{
    for (auto& b : bins)
        b.checked = true;
}

bool isRowDominance(const Bin& b1, const Bin& b2, const vector<int>& minterms)
{
    vector<int> v1(minterms.size()), v2(minterms.size());
    auto it = set_intersection(b1._nums.begin(), b1._nums.end(), minterms.begin(), minterms.end(), v1.begin()); // 교집합 연산
    v1.erase(it, v1.end());
    it = set_intersection(b2._nums.begin(), b2._nums.end(), minterms.begin(), minterms.end(), v2.begin()); // 교집합 연산
    v2.erase(it, v2.end());
    
    // cout << "minterms:"; print(minterms);
    // cout << "v1:"; print(v1);
    // cout << "v2:"; print(v2);
    if (includes(v1.begin(), v1.end(), v2.begin(), v2.end())) {
        if (v1.size() == v2.size()) {
            return b1.getCircleSize() >= b2.getCircleSize(); // 더 비용이 낮은 것을 고르기 위해서
        }
        return true;
    }
    return false;
}
// RowDominance에서 포함되는 쪽은 checked가 false가 되며 pi 후보에서 제외된다.
// 즉, RowDominance에 포함이 안되는 원소들을 리턴한다.
void findRowDominance(vector<Bin>& bins, const vector<int>& minterms) 
{
    setBoolTrue(bins);
    for (int i = 0; i < bins.size(); i++) {
        if (!bins[i].checked) {
            continue;
        }
        for (int j = 0; j < bins.size(); j++) { // 부분집합일 경우 bins[j] 제외
            if (!bins[j].checked || (i == j)) {
                continue;
            }
            // 오류: circleSize가 작아도 포함할 수 있다. -> isRowDominance로 해결
            // 현재 남은 minterms를 기준으로 사이즈를 비교해야 한다.
            if (bins[j].checked && isRowDominance(bins[i], bins[j], minterms)) {
                cout << bins[i] << ">=" << bins[j] << '\n';
                bins[j].checked = false;
            }
        }
    }
    auto it = bins.begin();
    while (it != bins.end()) {
        if (!it->checked) {
            it = bins.erase(it);
        }
        else {
            it++;
        }
    }
}

void refineMinterms(const vector<int>& except, vector<int>& minterms) //epi에 속한 minterm들을 삭제한다.
{
    for (const auto& n : except) {
        auto delPos = find(minterms.begin(), minterms.end(), n);
        if (delPos != minterms.end()) {
            minterms.erase(delPos);
        }
    }
}

// Column dominance에서 포함하는(지배하는) minterm들을 제거한 뒤 리턴한다.
void findColumnDominance(vector<Bin>& bins, vector<int>& minterms)
{
    setBoolTrue(bins);
    map<int, set<string>> table;
    vector<int> except;
    for (const auto& m : minterms) {
        // table.insert(pair<int, set<string>>(m, set<string>()));
        table[m] = set<string>();
    }
    for (const auto& b : bins) {
        for (const auto& n : b._nums) {
            if (find(minterms.begin(), minterms.end(), n) != minterms.end()) { // minterms에 속한 원소만 추가해야 한다.
                table[n].insert(b._binary); // binary로 bin객체 구분. 
            }
        }
    }
    /* */
    printTable(table, bins);
    auto it1 = table.begin();
    while (it1 != table.end()) {
        bool ok = true;
        for (auto it2 = table.begin(); it2 != table.end(); it2++) {
            if (it1 == it2) {
                continue;
            }
            // cout << "it1==" << it1->first << ':'; for (const auto& n : it1->second) cout << n << ' ';
            // cout << '\n';
            // cout << "it2==" << it2->first << ':'; for (const auto& n : it2->second) cout << n << ' ';
            // cout << '\n';
            auto& a = it1->second;
            auto& b = it2->second;
            if (includes(a.begin(), a.end(), b.begin(), b.end())) {
                ok = false;
                except.push_back(it1->first);
                cout << it1->first << ">=" << it2->first << '\n';
                it1 = table.erase(it1); // 포함하는 원소를 삭제
                break; // 그 뒤는 확인할 필요 없다.
            }
        }
        if (ok) {
            it1++;
        }
    }
    refineMinterms(except, minterms);
}


