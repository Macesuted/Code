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

#define maxn 100005

typedef pair<int, int> pii;

int a[maxn], tail;
pii record[maxn];

int main() {
    int T = read<int>();
    while (T--) {
        int n = tail = read<int>();
        for (register int i = 1; i <= n; i++) record[i] = (pii){a[i] = read<int>(), i};
        sort(record + 1, record + n + 1);
        for (register int i = n; i && tail > 0; i--) {
            if (record[i].second > tail) continue;
            for (register int j = record[i].second; j <= tail; j++) printf("%d ", a[j]);
            tail = record[i].second - 1;
        }
        puts("");
    }
    return 0;
}