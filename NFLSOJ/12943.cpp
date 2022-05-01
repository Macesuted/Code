/**
 * @file 12943.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

bitset<maxn> pos[26], full;

void solve(void) {
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) pos[s[i] - 'a'].set(i);
    full.set();
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int p;
            char c;
            cin >> p >> c;
            p--;
            pos[s[p] - 'a'].reset(p), pos[(s[p] = c) - 'a'].set(p);
        } else {
            int k, len = 0;
            cin >> k;
            bitset<maxn> S = full;
            while (k--) {
                string x;
                cin >> x;
                bool check = true;
                for (auto i : x) check &= ('0' <= i && i <= '9');
                if (check) {
                    int p;
                    stringstream ssin(x);
                    ssin >> p;
                    len += p;
                } else
                    for (int i = 0; i < (int)x.size(); i++, len++) S &= pos[x[i] - 'a'] >> len;
            }
            int l, r;
            cin >> l >> r;
            l--, r--, r = r - len + 1;
            cout << (S >> l << (maxn - r + l - 1)).count() << endl;
        }
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("name.in", "r", stdin), freopen("name.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
