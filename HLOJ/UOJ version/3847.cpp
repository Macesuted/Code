/**
 * @file light.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 4S  Memory Limit: 1G
 *
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
T read(void) {
    char c = getchar();
    T f = +1, x = 0;
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar(x ^ 48), void();
    if (x > 9) write(x / 10);
    return putchar((x % 10) ^ 48), void();
}

bool mem1;

#define maxn 5000005

typedef pair<int, int> pii;

long long a[maxn];
vector<long long> r[maxn], f[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>(), r[i].push_back(0);
    r[1].push_back(a[2] - a[1]), r[n].push_back(a[n] - a[n - 1]);
    for (int i = 2; i < n; i++) r[i].push_back(min(a[i] - a[i - 1], a[i + 1] - a[i]));
    for (int i = 2, k = 1; i < n; i++) {
        if (a[i] - a[i - 1] <= a[i + 1] - a[i]) continue;
        for (int j = i - 1, last = a[i + 1] - a[i]; j >= k; j--) {
            last = a[j + 1] - a[j] - last;
            if (last > a[j] - a[j - 1]) break;
            r[j].push_back(last);
        }
        k = i;
    }
    for (int i = n - 1, k = n; i > 1; i--) {
        if (a[i] - a[i - 1] >= a[i + 1] - a[i]) continue;
        for (int j = i + 1, last = a[i] - a[i - 1]; j <= k; j++) {
            last = a[j] - a[j - 1] - last;
            if (last > a[j + 1] - a[j]) break;
            r[j].push_back(last);
        }
        k = i;
    }
    f[1].resize(r[1].size());
    for (int i = 0; i < (int)r[1].size(); i++) f[1][i] = r[1][i] * r[1][i];
    for (int i = 2; i <= n; i++) {
        f[i].resize(r[i].size());
        assert(r[i].size() <= 10);
        for (int j = 0; j < (int)r[i].size(); j++) {
            for (int k = 0; k < (int)r[i - 1].size(); k++)
                if (a[i] - r[i][j] >= a[i - 1] + r[i - 1][k]) f[i][j] = max(f[i][j], f[i - 1][k]);
            f[i][j] += r[i][j] * r[i][j];
        }
    }
    long long ans = 0;
    for (auto i : f[n]) ans = max(ans, i);
    write(2 * ans), putchar('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("light.in", "r", stdin), freopen("light.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}