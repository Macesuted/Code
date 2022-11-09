/**
 * @file 1061F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

mt19937 rnd(114514);

vector<int> a;

bool query(int x, int y, int z) {
    cout << "? " << x << ' ' << y << ' ' << z << endl;
    string s;
    cin >> s;
    return s == "Yes";
}

void solve(void) {
    int n, k, L1, L2, h = 1, d = 1, s = 1;
    cin >> n >> k;
    while (s != n) h++, d *= k, s += d;
    while (true) {
        L1 = rnd() % n + 1;
        int p = 1 + (L1 == 1);
        bool chk = true;
        for (int i = 1; i <= n && chk; i++)
            if (i != p && i != L1) chk &= !query(p, L1, i);
        if (chk) break;
    }
    while (true) {
        L2 = rnd() % n + 1;
        while (L2 == L1) L2 = rnd() % n + 1;
        bool chk = true;
        for (int i = 1; i <= n && chk; i++)
            if (i != L1 && i != L2) chk &= !query(L1, L2, i);
        if (!chk) continue;
        a.clear();
        for (int i = 1; i <= n; i++)
            if (i != L1 && i != L2 && query(L1, i, L2)) a.push_back(i);
        if ((int)a.size() == 2 * h - 3) break;
    }
    sort(a.begin(), a.end(), [&](int x, int y) { return query(L1, x, y); });
    for (auto i : a) cerr << i << ' ';
    cerr << endl;
    cout << "! " << a[a.size() >> 1] << endl;
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