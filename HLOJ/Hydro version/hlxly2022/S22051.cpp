/**
 * @file S22051.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxm 1000005
#define maxq 100005

int a[maxq], cnt[maxm];
int64_t f[maxm];

void solve(void) {
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> a[i], cnt[a[i] + 1]++;
    memset(f, 0x3f, sizeof(f));
    int64_t minLcm = INT64_MAX;
    for (int i = 1; i < maxm; i++) {
        int64_t minv = i;
        while (minv < maxm && !cnt[minv]) minv += i;
        if (minv >= maxm) continue;
        for (int j = i; j < maxm; j += i) {
            f[j] = min(f[j], minv * j / i);
            if (cnt[j] > (j == minv)) minLcm = min(minLcm, minv * j / i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m, m++;
        int v = n - n % m;
        cout << ((n % m == 0 || (v != 0 && min(minLcm, f[m]) <= v)) ? "Bob" : "Alice") << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("nim.in", "r", stdin), freopen("nim.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}