/**
 * @file 4001.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-12-24
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

#define maxn 3005

string s[maxn], l[maxn], r[maxn];
multiset<string> S;
queue<int> fnd[256];

void solve(void) {
    int n, m;
    cin >> n >> m;
    string M1, M2;
    M1 = M2 = string(1, 'z' + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i], l[i] = r[i] = s[i];

        sort(r[i].begin(), r[i].end(), greater<char>()), l[i] = r[i], reverse(l[i].begin(), l[i].end());
        if (M1 > r[i])
            M2 = M1, M1 = r[i];
        else if (M2 > r[i])
            M2 = r[i];
    }
    for (int i = 1; i <= n; i++) cout << (l[i] < (M1 == r[i] ? M2 : M1));
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("dict.in", "r", stdin), freopen("dict.out", "w", stdout);
#endif
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