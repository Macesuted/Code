/**
 * @file D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using ticc = tuple<int, char, char>;

char oth(char a, char b) {
    string s = "RYB";
    for (char c : s)
        if (c != a && c != b) return c;
    assert(false);
}

void solve(int n, string& s, vector<ticc>& ans) {
    ans.clear();

    auto pre = [&](int p) -> int { return p == 0 ? n - 1 : p - 1; };
    auto nxt = [&](int p) -> int { return p == n - 1 ? 0 : p + 1; };

    auto upd = [&](int p, char c) -> void {
        assert(s[p] != c && s[pre(p)] != s[nxt(p)]);
        return ans.emplace_back(p, s[p], c), s[p] = c, void();
    };

    for (int i = 1; i < n - 1; i++) {
        if (s[i] == s[0]) continue;
        int j = i;
        while (j != 0 && s[pre(j)] == s[nxt(j)]) j = nxt(j);

        if (s[pre(j)] == s[nxt(j)]) return;

        char c = oth(s[i], s[pre(i)]), o = s[0];
        for (int x = j; x != i; x = pre(x)) upd(x, c);
        for (int x = i; s[pre(x)] != s[nxt(x)]; x = nxt(x)) upd(x, o);
        if (j == 0) upd(n - 1, oth(o, s[0])), upd(0, o);
    }

    if (s[n - 1] == s[0]) return;

    if (s[0] != 'B') {
        char tar = oth('B', s[0]);
        if (s[n - 1] != tar) upd(n - 2, oth(s[0], tar)), upd(n - 1, tar), upd(n - 2, s[0]);
        for (int i = 0; i < n - 1; i++) upd(i, 'B');
    }

    if (s[n - 1] != 'R') upd(n - 2, oth(s[0], 'R')), upd(n - 1, 'R'), upd(n - 2, s[0]);

    return;
}

void solve(void) {
    int n;
    cin >> n;

    string s, t;
    cin >> s >> t;
    vector<ticc> anss, anst;

    string S = s, T = t;

    solve(n, s, anss), solve(n, t, anst);

    if (s != t) return cout << -1 << endl, void();

    auto pre = [&](int p) -> int { return p == 0 ? n - 1 : p - 1; };
    auto nxt = [&](int p) -> int { return p == n - 1 ? 0 : p + 1; };

    auto upd = [&](int p, char c) -> void {
        assert(S[pre(p)] != S[nxt(p)]);
        return S[p] = c, void();
    };

    cout << anss.size() + anst.size() << endl;
    for (auto [p, a, b] : anss) cout << p + 1 << ' ' << b << endl, upd(p, b);
    reverse(anst.begin(), anst.end());
    for (auto [p, a, b] : anst) cout << p + 1 << ' ' << a << endl, upd(p, a);

    assert(S == T);

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}