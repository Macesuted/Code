/**
 * @file arc120_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
 *
 * @copyright Copyright (c) 2025
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
int a[maxn], tim[maxn], b[maxn], f[maxn];

bool check(int k) {
    for (int l = 1, r; l < n; l = r) {
        r = l + 1;
        while (r + 1 <= n && !((a[l] < a[l + 1]) ^ (a[r] < a[r + 1]))) r++;
        for (int i = l; i <= r; i++) b[i] = a[i];
        if (b[l] > b[r]) reverse(b + l, b + r + 1);
        f[l] = b[l] + k;
        for (int i = l + 1; i <= r; i++) {
            f[i] = INT_MIN;
            if (f[i - 1] != INT_MIN && f[i - 1] >= b[i] - k) f[i] = max(f[i], f[i - 1]);
            if (i - 2 >= l && f[i - 2] != INT_MIN && f[i - 2] >= b[i] - k) f[i] = max(f[i], b[i - 1] + k);
        }
        if (f[r] == INT_MIN) return false;
    }
    return true;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int l = 0, r = 1e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) ? r : l) = mid;
    }
    cout << r << endl;

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