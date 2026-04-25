/**
 * @file 909F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

int p[maxn];

void solve(void) {
    int n;
    cin >> n;

    if (n & 1)
        cout << "NO" << endl;
    else {
        cout << "YES" << endl;

        int r = n;
        while (r) {
            int hb = 0;
            while ((1 << hb) <= r) hb++;
            int mask = (1 << hb) - 1;

            for (int x = r ^ mask, y = r; x < y; x++, y--) p[x] = y, p[y] = x;

            r = (r ^ mask) - 1;
        }

        for (int i = 1; i <= n; i++) cout << p[i] << ' ';
        cout << endl;

        for (int i = 1; i <= n; i++) assert((i ^ p[i]) && !(i & p[i]));
    }

    auto solve = [&](int n, int hb) {
        int x = 1 << hb;
        p[x] = x + 2;
        p[x + 1] = 1, p[1] = x + 1;
        for (int i = x + 2; i < n; i++) p[i] = i + 1;
        p[n] = x;

        vector<int> rec[30];
        for (int i = 1; i <= n; i++) {
            if (i == 1 || i >= x) continue;

            int x = 0;
            while ((1 << x) <= i) x++;
            rec[x].push_back(i);
        }

        for (int i = 1; i < 30; i++)
            for (int l = 0, r = (int)rec[i].size() - 1; l < r; l++, r--) p[rec[i][l]] = rec[i][r], p[rec[i][r]] = rec[i][l];

        return;
    };

    int hb = 0;
    while ((1 << hb) <= n) hb++;
    hb--;

    if (n == 3 || n == 5)
        cout << "NO" << endl;
    else if (n == (1 << hb))
        cout << "NO" << endl;
    else {
        if (n == (1 << hb) + 1)
            solve(n - 2, hb - 1), p[n - 1] = n, p[n] = n - 1;
        else
            solve(n, hb);

        cout << "YES" << endl;

        for (int i = 1; i <= n; i++) cout << p[i] << ' ';
        cout << endl;

        for (int i = 1; i <= n; i++) assert((i ^ p[i]) && (i & p[i]));
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
