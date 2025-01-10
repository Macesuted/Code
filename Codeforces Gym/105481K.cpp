/**
 * @file 105481K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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

#define maxn 500005
#define mod 1'000'000'009

class SegmentTree {
   private:
    vector<int> op[maxn << 2];
    int n;

    void insert(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return op[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void solve(int p, int l, int r, bitset<maxn> S) {
        for (auto v : op[p]) S |= S << v;
        if (l == r) return cout << S.count() - 1 << endl, void();
        int mid = (l + r) >> 1;
        solve(p << 1, l, mid, S), solve(p << 1 | 1, mid + 1, r, S);
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, int v) { return insert(1, 1, n, l, r, v); }
    void solve(void) {
        bitset<maxn> S;
        S[0] = true;
        return solve(1, 1, n, S);
    }
} ST;

vector<int> pos[maxn];

void solve(void) {
    int n;
    cin >> n;

    ST.resize(n);
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1)
            pos[x].push_back(i);
        else
            ST.insert(pos[x].back(), i - 1, x), pos[x].pop_back();
    }
    for (int i = 1; i < maxn; i++)
        for (auto p : pos[i]) ST.insert(p, n, i);

    ST.solve();

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