/**
 * @file 868F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
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

#define maxn 100005

int a[maxn], cnt[maxn], L = 1, R = 0;
int64_t ans = 0, f[maxn], g[maxn];

int64_t query(int l, int r) {
    while (L > l) ans += cnt[a[--L]]++;
    while (R < r) ans += cnt[a[++R]]++;
    while (L < l) ans -= --cnt[a[L++]];
    while (R > r) ans -= --cnt[a[R--]];
    return ans;
}

void solve(int l, int r, int ql, int qr) {
    if (l > r) return;
    int mid = (l + r) >> 1, qmid = 0;
    for (int i = ql; i <= min(qr, mid); i++)
        if (f[i - 1] + query(i, mid) < g[mid]) g[mid] = f[(qmid = i) - 1] + ans;
    return solve(l, mid - 1, ql, qmid), solve(mid + 1, r, qmid, qr);
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, 0x3f, sizeof(f)), f[0] = 0;
    while (k--) memset(g, 0x3f, sizeof(g)), solve(1, n, 1, n), memcpy(f, g, sizeof(f));
    cout << f[n] << endl;
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