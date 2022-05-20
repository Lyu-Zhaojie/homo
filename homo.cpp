#include <cstdint>
#include <iostream>
#include <string>

using namespace std;
constexpr char raw[7][96]{
    "(11/(45-1)*4)",                                                                    // 2^0=1
    "(-11+4-5+14)",                                                                     // 2^1=2
    "(-11-4+5+14)",                                                                     // 2^2=4
    "(11-4-5+14)",                                                                      // 2^4=16
    "((114-51)*4+(-11-4+5+14))",                                                        // 2^8=256
    "(114*514+(11*45*14+(-11/4+51/4)))",                                                // 2^16=65536
    "(114514*(114*51*4+(11451+4+(114*(5+1)*4+(114-51-4))))+(11*(451+4)+(-1+1*4*51+4)))" // 2^32=4294967296
};
string homoBinary(uint64_t exp)
{
    if (exp == 0)
        return string(raw[0]);
    uint64_t tmp{0};
    string ans;
    bool s{false};
    while (exp)
    {
        __asm__ volatile("tzcnt %1, %0;"
                         : "=r"(tmp)
                         : "r"(exp));
        if (s)
            ans += '*';
        s = true;
        ans += raw[tmp + 1];
        exp ^= 1ULL << tmp;
    }
    return ans;
}
string homoUint64(uint64_t num)
{
    if (num == 0)
        return "(1-1)*4514";
    uint64_t tmp{0};
    string ans;
    bool s{false};
    while (num)
    {
        __asm__ volatile("tzcnt %1, %0;"
                         : "=r"(tmp)
                         : "r"(num));
        if (s)
            ans += '+';
        s = true;
        ans += homoBinary(tmp);
        num ^= 1ULL << tmp;
    }
    return ans;
}
int main()
{
    uint64_t num{0};
    cout << "Please enter a integer between 0 and 2^64 - 1: " << endl;
    cin >> num;
    cout << '=' << homoUint64(num) << endl;
    system("pause");
    return 0;
}
