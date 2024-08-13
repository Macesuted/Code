/**
 * @file 81604G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 1005

int a[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    cout << n + (n - 1) / k << endl;
    for (int i = 1; i <= n + 1; ++i) a[i] = i;
    for (int t = 1; t <= n + (n - 1) / k; t++) {
        vector<int> op;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = l;
            while (r <= n && a[r + 1] == a[r] + 1) r++;
            if (l == r) continue;
            int p = max(l, r - k);
            op.push_back(p);
            for (int i = p + 1; i <= r; i++) a[i]++;
        }
        cout << op.size() << ' ';
        for (auto i : op) cout << i << ' ';
        cout << endl;
    }
    cout << 2 * n - 1 << endl;
    for (int t = 1; t <= 2 * n - 1; t++) {
        vector<int> op;
        for (int i = 1; i <= n; i++)
            if (i == n || (a[i] + 2 == a[i + 1] && a[i + 1] + 1 == a[i + 2])) op.push_back(i), a[++i]--;
        cout << op.size() << ' ';
        for (auto i : op) cout << i << ' ';
        cout << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}