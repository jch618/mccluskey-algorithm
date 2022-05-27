#include "testfunc.h"
#include <iomanip>
#define WIDTH 4
using namespace std;

void solve(vector<Bin>& pi, vector<int>& minterms, vector<Bin>& ret)
{
    sort(pi.begin(), pi.end(), binCompareByString);
    if (minterms.empty()) {
        return;
    }
    cout << "------start------------------\n";
    // vector<int> minterms(input.begin()+2, input.end());
    int mintermSize = minterms.size();
    printPIAndMinterms(pi, minterms) ;
    
    cout << "-----------------------------\n";
    cout <<"findEPI:\n"; printTable(pi, minterms);
    auto epi = findEPI(pi, minterms); // vector<Bin> epi return
    cout << "epi: "; print(epi);
    refineMinterms(epi, minterms); // epi에 포함되는 nums를 minterms에서 제외
    cout << "after del epi minterms: "; print(minterms);
    auto nepi = findNEPI(pi, epi); // pi에서 epi를 제외한 원소들 리턴
    cout << "nepi:"; print(nepi);

    cout << "-----------------------------\n";
    cout << "coulmn dominance start:\n";
    printPIAndMinterms(nepi, minterms);
    findColumnDominance(nepi, minterms); // column dominance에서 다른 포함을 하는 쪽의 minterm을 제거
    cout << "after column dominance minterms: "; print(minterms);

    cout << "-----------------------------\n";
    cout << "row dominance:\n"; printTable(nepi, minterms);
    findRowDominance(nepi, minterms); // row dominance에서 포함 당하는 쪽의 pi를 후보에서 제거
    cout << "after row dominance nepi: "; print(nepi);
    if (minterms.size() == mintermSize) {
        return; // 더이상 최적화 될 수 없는 상태.
    }
    ret.insert(ret.end(), epi.begin(), epi.end());
    sort(ret.begin(), ret.end(), binCompareByString);
    solve(nepi, minterms, ret);
}

void startSolve(int size, vector<Bin>& bins, vector<int>& minterms, vector<Bin>& ret)
{
    vector<Bin> pi;
    findPI(size, bins, pi);
    // for (const auto& b : pi) {
    //     cout << b << ": "; print(b.getNums());
    // }
    cout << "{---start solve-------------\n";
    solve(pi, minterms, ret);
    cout << "ret: "; print(ret);
    cout << "------end solve------------}\n\n\n";
}

void print(const vector<Bin>& bins)
{
    if (bins.empty()) {
        cout << "empty.\n";
        return;
    }
    cout << '[';
    int i;
    for (i = 0; i < bins.size()-1; i++) {
        cout << '\'' << bins[i].getBinary() << "\', ";
    }
    cout << '\'' << bins[i].getBinary() << "\']\n";
}

void print(const vector<int>& minterms)
{
    for (const auto& n : minterms) {
        cout << n << ", ";
    }
    cout << '\n';
}

void print(const set<int>& s)
{
    for (const auto& n : s) {
        cout << n << ", ";
    }
    cout << '\n';
}

void printPIAndMinterms(const vector<Bin>& pi, const vector<int>& minterms)
{
    cout << "pi: "; print(pi);
    cout << "minterms: "; print(minterms);
}

void printStringVec(vector<string>& vec)
{
    for (const auto& s : vec)
        cout << s << ' ';
    cout << endl;
}

void printTable(const vector<Bin>& bins, const vector<int>& minterms)
{
    const int SIZE = (!bins.empty()) ? bins[0].getSize()+2 : 0;
    // cout << "SIZE: " << SIZE << '\n';
    cout << left << setw(SIZE) << "";
    for (const auto& m : minterms)
        cout << setw(WIDTH) << m;
    cout << '\n';
    for (const auto& b : bins) {
        cout << setw(SIZE) << b;
        for (const auto& n : minterms) {
            if (find(b._nums.begin(), b._nums.end(), n) != b._nums.end())
                cout << setw(WIDTH) << 'O';
            else
                cout << setw(WIDTH) << '-';
        }
        cout << '\n';
    }
    cout << '\n';
}

void printTable(const map<int, set<string>>& table, const vector<Bin>& bin)
{
    const int SIZE = (!bin.empty()) ? bin[0].getSize()+2 : 0;
    // cout << "SIZE: " << SIZE << '\n';
    cout << left << setw(WIDTH) << "";
    for (const auto& b : bin) {
        cout << setw(SIZE) << b;
    }
    cout << '\n';
    for (const auto& p : table) {
        cout << left << setw(WIDTH) << p.first;
        for (const auto& b : bin) {
            if (p.second.find(b._binary) != p.second.end())
                cout << setw(SIZE) << 'O';
            else
                cout << setw(SIZE) << '-';
        }
        cout << '\n';
    }
    cout << '\n';
}

// homework
vector<string> solution(vector<int> minterm) {
    int size = minterm[0];
    int N = minterm[1];
    vector<Bin> bins;
    for (int i = 0; i < N; i++)
        bins.emplace_back(size, minterm[i+2]); //empalce_back: 생성자 호출 가능
    // print(bins);
    vector<Bin> ret;
    findPI(size, bins, ret);
    sort(ret.begin(), ret.end(), binCompareByString);
    vector<string> pi = toStringVec(ret);
    print(ret);

    vector<Bin> ret2 = findEPI(ret, minterm);
    vector<string> epi = toStringVec(ret2);
    print(ret2);
    pi.push_back("EPI");
    pi.insert(pi.end(), epi.begin(), epi.end());
    return pi;
}