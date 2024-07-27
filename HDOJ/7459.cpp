/**
 * @file 7459.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

typedef pair<int, int> pii;

int tl, tr;
bool flag;

map<int, int> S;

void check(pii a, pii b) {
    if (((a.first + a.second) & 1) ^ ((b.first + b.second) & 1)) tl = max(tl, a.first + 1);
    if (a.second == 1 && b.second > 1) tr = min(tr, b.first - b.second + 1);
    if (abs(a.second - b.second) > b.first - a.first) flag = false;
    return;
}

void insert(int tim, int pos) {
    if (S.count(tim) && S[tim] != pos) return flag = false, void();
    S[tim] = pos;
    auto p = S.find(tim);
    if (p != S.begin()) check(*--p, {tim, pos});
    p = S.find(tim);
    if (++p != S.end()) check({tim, pos}, *p);
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    tl = 0, tr = 1 << 30, flag = true;
    S.clear(), insert(0, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 0) {
            int p, q;
            cin >> p >> q;
            if (tl > tr || !flag) continue;
            insert(q, p);
        } else if (op == 1) {
            if (tl > tr || !flag)
                cout << "bad" << endl;
            else
                cout << tl << endl;
        } else {
            if (tl > tr || !flag)
                cout << "bad" << endl;
            else if (tr == (1 << 30))
                cout << "inf" << endl;
            else
                cout << tr << endl;
        }
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}