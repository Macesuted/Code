/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 305

int a[maxn];

int t[maxn];

map<int, vector<int> > S;

void work(void) {
    int n, m;
    cin >> n >> m;
    S.clear();
    for (register int i = 1; i <= m; i++) cin >> a[i], S[a[i]].push_back(i), t[i] = 0;
    int answer = 0;
    for (auto i = S.rbegin(); i != S.rend(); i++) {
        for (auto j : i->second)
            for (register int x = j + 1; x <= m; x++) answer += t[x];
        for (auto j : i->second) t[j] = true;
    }
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}