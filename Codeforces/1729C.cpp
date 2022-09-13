/**
 * @file 1729C.cpp
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

pii a[maxn];

void solve(void) {
    string s;
    cin >> s, s = " " + s;
    int n = s.size() - 1, m = 0;
    for (int i = 2; i < n; i++)
        if (abs(s[i] - s[1]) + abs(s[i] - s[n]) == abs(s[1] - s[n])) a[++m] = {s[i], i};
    sort(a + 1, a + m + 1);
    if (s[1] > s[n]) reverse(a + 1, a + m + 1);
    cout << abs(s[1] - s[n]) << ' ' << m + 2 << endl;
    cout << 1 << ' ';
    for (int i = 1; i <= m; i++) cout << a[i].second << ' ';
    cout << n << endl;
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