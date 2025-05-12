/**
 * @file 11112.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
mt19937_64 rnd(time(nullptr));
void solve(void) {
    int n, k, m;
    cin >> n >> k >> m;
    set<string> hap;
    string s;
    auto dfs = [&](auto self, int p, int num) -> void {
        if (p == n) {
            hap.insert(s);
            return;
        }
        if (num < k) {
            s += '1';
            self(self, p + 1, num + 1);
            s.pop_back();
        }
        if (num + (n - p - 1) >= k) {
            s += '0';
            self(self, p + 1, num);
            s.pop_back();
        }
    };
    dfs(dfs, 0, 0);
    set<string> hp1, hp2;
    auto check = [&](string s) -> bool {
        auto iz = s;
        sort(iz.begin(), iz.end());
        for (int i = 0; i < n; i++) {
            if (iz == s) return false;
            s = s.substr(1) + s[0];
        }
        return true;
    };
    for (auto it : hap) {
        if (check(it))
            hp1.insert(it);
        else
            hp2.insert(it);
    }
    cout << (m * k + n - 1) / n << '\n';
    vector<string> ans;
    while (m >= n && !hp1.empty()) {
        auto it = *hp1.begin();
        while (hp1.count(it)) {
            hp1.erase(it);
            ans.push_back(it);
            m--;
            it = it.substr(1) + it[0];
        }
    }
    int p = 0;
    vector<bool> vis(n, false);
    while (m--) {
        while (vis[p]) p++;
        vis[p] = true;
        string s(n, '0');
        for (int t = 0; t < k; t++) s[p] = '1', p = (p + 1) % n;
        ans.push_back(s);
    }
    for (auto &s : ans) cout << s << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}