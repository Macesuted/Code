/**
 * @file 2129C3.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

int a[maxn], d[20], dr[20];

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) a[i] = i;

    while (true) {
        shuffle(a + 1, a + n + 1, rnd);
        cout << "? " << n << ' ';
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << endl;
        int64_t ret;
        cin >> ret;
        if (ret) break;
    }

    string s(n, '(');

    int l = 1, r = n;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;

        cout << "? " << mid - l + 1 << ' ';
        for (int i = l; i <= mid; i++) cout << a[i] << ' ';
        cout << endl;
        int64_t ret;
        cin >> ret;

        (ret == 0 ? l : r) = mid;
    }

    int pL = a[l];

    int B = 13;
    for (int l = 1; l <= n; l += B) {
        vector<int> vec;
        for (int i = 0; i < min(B, n - l + 1); i++) {
            for (int t = 1; t < d[i]; t++) vec.push_back(pL), vec.push_back(l + i);
            for (int t = 0; t <= dr[i]; t++) vec.push_back(pL);
            for (int t = 0; t <= dr[i]; t++) vec.push_back(l + i);
            vec.push_back(pL);
        }
        cout << "? " << vec.size() << ' ';
        for (auto x : vec) cout << x << ' ';
        cout << endl;
        int64_t ret = 0;
        cin >> ret;
        for (int i = 0; i < B; i++)
            if (ret >> i & 1) s[l + i - 1] = ')';
    }

    cout << "! " << s << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < 13; i++) {
        int x = 1;
        while ((x + 1) * (x + 2) / 2 <= (1 << i)) x++;
        d[i] = x, dr[i] = (1 << i) - x * (x + 1) / 2;
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}