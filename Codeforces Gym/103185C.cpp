/**
 * @file 103185C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int a[maxn], b[maxn], fa[maxn];
int n;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

int64_t calc(void) {
    int64_t tot = 0, v = 0;
    for (int i = 1; i <= n; i++) b[i] = a[i], v += b[i];
    v /= n;
    for (int i = 1; i <= n; i++) fa[i] = (b[i] >= v ? i % n + 1 : i);
    for (int i = 1; i <= n; i++) {
        if (b[i] <= v) continue;
        int p = getfa(i), rest = b[i] - v;
        b[i] = v;
        while (rest && b[p] + rest >= v)
            rest -= v - b[p], tot += int64_t(v - b[p]) * ((p - i + n) % n), b[p] = v, p = fa[p] = getfa(p % n + 1);
        if (rest) b[p] += rest, tot += rest * ((p - i + n) % n);
    }
    return tot;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = calc();
    reverse(a + 1, a + n + 1);
    cout << min(ans, calc()) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}