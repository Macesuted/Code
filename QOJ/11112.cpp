/**
 * @file 11112.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-13
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

string gets(string s) {
    string ans = s;
    for (int i = 1; i < (int)s.size(); i++) s = s.substr(1) + s[0], ans = min(ans, s);
    return ans;
}

unordered_set<string> S;

void find(string &s, int n, int rest, int p) {
    if (p == n) return S.insert(gets(s)), void();
    if (rest > 0) s.push_back('1'), find(s, n, rest - 1, p + 1), s.pop_back();
    if (n - p > rest) s.push_back('0'), find(s, n, rest, p + 1), s.pop_back();
    return;
}

void solve(void) {
    int n, k, m;
    cin >> n >> k >> m;

    string s;
    S.clear(), find(s, n, k, 0), S.erase(string(n - k, '0') + string(k, '1'));

    cout << (k * m + n - 1) / n << endl;

    vector<string> ans;
    while (m > n) {
        string o = *S.begin(), s = o;
        S.erase(o);
        do {
            ans.push_back(s), m--, s = s.substr(1) + s[0];
        } while (s != o);
    }

    vector<bool> used(n);
    int p = 0;
    while (m--) {
        while (used[p]) p = (p + 1) % n;
        used[p] = true;
        string s(n, '0');
        for (int t = 0; t < k; t++) s[p] = '1', p = (p + 1) % n;
        ans.push_back(s);
    }

    for (auto s : ans) cout << s << endl;

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