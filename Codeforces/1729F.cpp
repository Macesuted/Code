/**
 * @file 1729F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

typedef pair<int, int> pii;

int pw10[maxn], a[maxn];
vector<int> pos[9];

int getVal(int l, int r) { return (a[r] + 9 - a[l - 1] * pw10[r - l + 1] % 9) % 9; }

void solve(void) {
    string s;
    cin >> s, s = " " + s;
    int n = s.size() - 1, w, m;
    cin >> w >> m;
    a[0] = 0;
    for (int i = 1; i <= n; i++) a[i] = (a[i - 1] * 10 + (s[i] - '0')) % 9;
    for (int i = 0; i < 9; i++) pos[i].clear();
    cerr << "! ";
    for (int i = w; i <= n; i++) pos[getVal(i - w + 1, i)].push_back(i - w + 1), cerr << getVal(i - w + 1, i) << ' ';
    cerr << endl;
    while (m--) {
        int l, r, k;
        pii ret = {INT_MAX, INT_MAX};
        cin >> l >> r >> k;
        for (int i = 0; i < 9; i++) {
            if (pos[i].empty()) continue;
            int v = (k + 9 - i * getVal(l, r) % 9) % 9;
            if (pos[v].size() < 1 + (v == i)) continue;
            ret = min(ret, pii{pos[i].front(), pos[v][pos[v][0] == pos[i].front()]});
        }
        if (ret == pii{INT_MAX, INT_MAX}) ret = {-1, -1};
        cout << ret.first << ' ' << ret.second << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    pw10[0] = 1;
    for (int i = 1; i < maxn; i++) pw10[i] = pw10[i - 1] * 10 % 9;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}