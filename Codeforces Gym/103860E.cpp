/**
 * @file 103860E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef tuple<char, int, int> tcii;

void solve(void) {
    int n, m;
    cin >> m >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i], a[i] = ' ' + a[i];
    reverse(a.begin(), a.end());

    {
        auto chk = [&](const string& s) -> bool {
            for (auto c : s)
                if (c == '#') return false;
            return true;
        };
        while (n && chk(a.back())) a.pop_back(), n--;
        reverse(a.begin(), a.end());
    }

    int x = 2;
    if (n)
        for (int j = 1; j <= m; j++)
            if (a[0][j] == '#') x = max(2, j - 1);

    vector<tcii> answer;

    answer.emplace_back('T', 2, x - 1);

    if (x & 1) {
        for (int i = x - 3; i >= 2; i -= 2) answer.emplace_back('S', 0, i);
        answer.emplace_back('T', 3, 1);
        for (int i = 1; i <= x - 2; i += 2) answer.emplace_back('Z', 0, i);
    } else {
        for (int i = x - 3; i >= 1; i -= 2) answer.emplace_back('S', 0, i);
        answer.emplace_back('T', 3, 1);
        for (int i = 2; i <= x - 2; i += 2) answer.emplace_back('Z', 0, i);
    }

    if (x == m - 1)
        answer.emplace_back('L', 2, m - 1);
    else if ((m - x) & 1) {
        for (int i = x + 1; i <= m - 2; i += 2) answer.emplace_back('Z', 0, i);
        answer.emplace_back('T', 1, m - 1);
        for (int i = m - 3; i >= x + 2; i -= 2) answer.emplace_back('S', 0, i);
        answer.emplace_back('T', 0, x);
    } else {
        for (int i = x + 1; i <= m - 3; i += 2) answer.emplace_back('Z', 0, i);
        answer.emplace_back('T', 1, m - 1);
        for (int i = m - 2; i >= x + 2; i -= 2) answer.emplace_back('S', 0, i);
        answer.emplace_back('T', 0, x);
    }

    cout << answer.size() << endl;
    for (auto [ch, a, x] : answer) cout << ch << ' ' << a << ' ' << x << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}