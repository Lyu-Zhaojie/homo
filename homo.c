#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char raw[7][96] = {
    "(11/(45-1)*4)",                                                                    // 2^0=1
    "(-11+4-5+14)",                                                                     // 2^1=2
    "(-11-4+5+14)",                                                                     // 2^2=4
    "(11-4-5+14)",                                                                      // 2^4=16
    "((114-51)*4+(-11-4+5+14))",                                                        // 2^8=256
    "(114*514+(11*45*14+(-11/4+51/4)))",                                                // 2^16=65536
    "(114514*(114*51*4+(11451+4+(114*(5+1)*4+(114-51-4))))+(11*(451+4)+(-1+1*4*51+4)))" // 2^32=4294967296
};
void homoBinary(uint64_t exp)
{
    if (exp == 0)
        printf(raw[0]);
    uint64_t tmp = 0;
    int s = 0;
    while (exp)
    {
        __asm__ volatile("tzcnt %1, %0;"
                         : "=r"(tmp)
                         : "r"(exp));
        if (s)
            printf("*");
        s = 1;
        printf(raw[tmp + 1]);
        exp ^= 1ULL << tmp;
    }
}
void homoUint64(uint64_t num)
{
    printf("%ulld", num);
    if (num == 0)
        printf("(1-1)*4514");
    uint64_t tmp = 0;
    int s = 0;
    while (num)
    {
        __asm__ volatile("tzcnt %1, %0;"
                         : "=r"(tmp)
                         : "r"(num));
        if (s)
            printf("+");
        s = 1;
        homoBinary(tmp);
        num ^= 1ULL << tmp;
    }
    printf("\n");
}
int main(void)
{
    uint64_t num = 0;
    printf("Please enter a integer between 0 and 2^64 - 1: ");
    scanf("%ulld", &num);
    homoUint64(num);
    system("pause");
    return 0;
}
