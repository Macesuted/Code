/**
 * @file 1305F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int n;
int64_t a[maxn], ans = INT_MAX;

void check(int64_t v) {
    int64_t tot = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] < v)
            tot += v - a[i];
        else
            tot += min(a[i] % v, v - a[i] % v);
    return ans = min(ans, tot), void();
}
void solve(int64_t v) {
    if (!v) return;
    for (int64_t i = 2; i * i <= v; i++) {
        if (v % i) continue;
        check(i);
        while (v % i == 0) v /= i;
    }
    if (v > 1) check(v);
    return;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    mt19937 rnd(114514);
    for (int i = 1; i <= 30; i++) {
        int p = rnd() % n + 1;
        solve(a[p] - 1), solve(a[p]), solve(a[p] + 1);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}