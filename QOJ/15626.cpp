/**
 * @file 15626.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1005

int n, m;
int rem[maxn];

bool dfs(vector<string> &a, int x, int y, char c) {
    char tar = "IP"[c == 'I'];

    for (int dx = -1; dx <= +1; dx++)
        for (int dy = -1; dy <= +1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int tx = x + dx, ty = y + dy;
            if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] == 'C') continue;
            if (a[tx][ty] == 'X' && !dfs(a, tx, ty, a[tx][ty] = tar)) return false;
            if (a[tx][ty] != tar) return false;
        }

    return true;
}

vector<string> calc(vector<string> a) {
    n = a.size() - 1, m = a[0].size() - 1;

    for (int i = 1; i <= n; i++) {
        rem[i] = -1;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '?') continue;
            int cur = (a[i][j] == 'C') ^ (j & 1);
            if (rem[i] == -1) rem[i] = cur;
            if (rem[i] != cur) return {};
        }
    }

    int lst = -1;
    for (int i = 1; i <= n && lst == -1; i++) lst = rem[i];
    if (lst == -1) lst = 0;
    for (int i = 1; i <= n; i++) {
        if (rem[i] != -1) lst = rem[i];
        for (int j = 1; j <= m; j++)
            if (a[i][j] == '?') a[i][j] = "XC"[(j & 1) ^ lst];
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if ((a[i][j] == 'I' || a[i][j] == 'P') && !dfs(a, i, j, a[i][j])) return {};

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == 'X' && !dfs(a, i, j, a[i][j] = 'I')) return {};

    return a;
}

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<string> a(n + 1);
    a[0] = string(m + 1, ' ');
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = ' ' + a[i];

    auto rev = [&](const vector<string> &a) -> vector<string> {
        if (a.empty()) return {};

        vector<string> ret(a[0].size(), string(a.size(), ' '));
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < a[0].size(); j++) ret[j][i] = a[i][j];

        return ret;
    };

    vector<string> ans = calc(a);
    if (ans.empty()) ans = rev(calc(rev(a)));
    if (ans.empty()) return cout << "no" << endl, void();

    cout << "yes" << endl;
    for (int i = 1; i <= n; i++) cout << ans[i].substr(1) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
