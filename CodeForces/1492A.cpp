/**
 * @author Macesuted
 * @date 2021-02-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define bufferSiz (1 << 18)
char Buff[bufferSiz], *_S = Buff, *_T = Buff;
#define getchar() (_S == _T && (_T = (_S = Buff) + fread(Buff, 1, bufferSiz, stdin), _S == _T) ? EOF : *_S++)

template <typename T>
T read(void) {
    char c = getchar();
    T f = 1, num = 0;
    while (c < '0' || c > '9') {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        num = (num << 3) + (num << 1) + (c ^ 48);
        c = getchar();
    }
    return f * num;
}

int main() {
    int T = read<int>();
    while (T--) {
        long long p = read<long long>(), a = read<long long>(), b = read<long long>(), c = read<long long>();
        long long ta = p / a * a, tb = p / b * b, tc = p / c * c;
        if (ta < p) ta += a;
        if (tb < p) tb += b;
        if (tc < p) tc += c;
        printf("%lld\n", min(ta - p, min(tb - p, tc - p)));
    }
    return 0;
}