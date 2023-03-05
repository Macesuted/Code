/**
 * @file 4.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 300005

int a[maxn], cnt[maxn];

void solve(void) {
    int n;
    cin >> n;
    if (n == 1) return cout << -1 << endl, void();
    for (int i = 1; i <= n; i++) cnt[i] = 2;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]--;
    int p = 0;
    for (int i = 1; i <= n; i++)
        if (cnt[i] == 2) p = i;
    if (p) {
        cout << n << endl;
        cout << p << ' ';
        vector<int> S;
        for (int i = 1; i <= n; i++)
            if (cnt[i] == 2 && i != p) S.push_back(i);
        for (int i = 1; i < n; i++)
            if (cnt[a[i]])
                cout << a[i] << ' ';
            else {
                int r = i;
                while (!cnt[a[r]]) cnt[a[r++]]++;
                for (int j = i + 1, x = 0; j < r; j++, x++) cout << S[x] << ' ';
                cout << p << ' ';
                if (r < n) cout << p << ' ';
                i = r;
            }
        cout << endl;
    } else {
        cout << n + 2 << endl;
        int x = 1 + (a[1] == 1), p = 1, y = 0;
        cout << x << ' ';
        while (a[p] != x) cout << a[p] << ' ', y = a[p++];
        cout << y << ' ', p++;
        while (p <= n) cout << a[p++] << ' ';
        cout << y << endl;
    }
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
