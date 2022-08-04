/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 200005

typedef pair<int, int> pii;

map<pii, int> record;
map<int, int> A, B;
pii a[maxn];

void work(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        record[{x, y}]++, A[x]++, B[y]++;
    }
    long long answer = 1LL * n * (n - 1) * (n - 2) / 6;
    for (auto i : record) {
        if (i.second >= 2) answer -= 1LL * i.second * (i.second - 1) / 2 * (n - i.second);
        answer -= 1LL * (A[i.first.first] - 1) * (B[i.first.second] - 1);
    }
    cout << answer << endl;
    record.clear(), A.clear(), B.clear();
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = read<int>();
    while (_--) work();
    return 0;
}