/**
 * @file 14682.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 2000005

using pii = pair<int, int>;

int a[maxn], cnt[3][maxn];

void solve(void) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    n = s.size();
    s = ' ' + s + ' ';

    int xl = n, xr = 1;

    bool beau = true;
    for (int i = 1; i < n; i++)
        if (s[i] == s[i + 1]) xl = min(xl, i + 1), xr = max(xr, i), beau = false;
    if (beau) return cout << "Beautiful" << endl, void();

    for (int i = 1; i <= n; i++) a[i] = (s[i] == 'C' ? 0 : s[i] == 'P' ? 1 : 2);

    a[0] = a[n + 1] = 4;
    for (int i = 1; i <= n; i++) {
        for (int t = 0; t < 3; t++) cnt[t][i] = cnt[t][i - 1];
        cnt[a[i]][i]++;
    }

    auto getCnt = [&](int c, int l, int r) -> int { return cnt[c][r] - cnt[c][l - 1]; };
    auto check = [&](int l, int r) -> bool {
        int c[3] = {0, 1, 2};
        sort(c, c + 3, [&](int x, int y) -> int { return getCnt(x, l, r) > getCnt(y, l, r); });

        if (!getCnt(c[1], l, r)) return false;

        if (!getCnt(c[2], l, r)) {
            if (a[l - 1] == c[0]) swap(c[0], c[1]);
            if (a[r + 1] == c[(r - l) & 1]) swap(c[0], c[1]);
            if (a[l - 1] == c[0] || a[r + 1] == c[(r - l) & 1]) return false;
            if (getCnt(c[0], l, r) != (r - l + 2) / 2) return false;
            if (getCnt(c[1], l, r) != (r - l + 1) / 2) return false;
            return true;
        }

        int l0 = l;
        if (a[l - 1] == c[0]) l0++;
        int r0 = l0 + (getCnt(c[0], l, r) - 1) * 2;
        if (r0 > r || (r0 == r && a[r + 1] == c[0])) return false;

        int r1 = r;
        if (a[r + 1] == c[1]) r1--;
        if (r0 == r1) r1--;

        int l1 = r1 - (getCnt(c[1], l, r) - 1) * 2;
        if (l1 <= r0 && abs(r0 - r1) % 2 == 0) l1--;
        if (l1 < l) return false;

        return true;
    };

    pii ans = {0, n + 1};

    for (int l = 1, r = xr; l <= xl; l++) {
        r = max(l, r);
        while (r <= n && !check(l, r)) r++;
        if (r > n) break;
        if (r - l + 1 < ans.second - ans.first + 1) ans = {l, r};
    }

    if (ans.first == 0) return cout << "Impossible" << endl, void();

    auto [l, r] = ans;

    int c[3] = {0, 1, 2};
    sort(c, c + 3, [&](int x, int y) -> int { return getCnt(x, l, r) > getCnt(y, l, r); });

    for (int i = l; i <= r; i++) a[i] = c[2];

    if (!getCnt(c[2], l, r)) {
        if (a[l - 1] == c[0]) swap(c[0], c[1]);
        if (a[r + 1] == c[(r - l) & 1]) swap(c[0], c[1]);
    }

    int l0 = l;
    if (a[l - 1] == c[0]) l0++;
    int r0 = l0 + (getCnt(c[0], l, r) - 1) * 2;
    for (int i = l0; i <= r0; i += 2) a[i] = c[0];

    int r1 = r;
    if (a[r + 1] == c[1]) r1--;
    if (r0 == r1) r1--;

    int l1 = r1 - (getCnt(c[1], l, r) - 1) * 2;
    if (l1 <= r0 && abs(r0 - r1) % 2 == 0) l1--;
    for (int i = r1; i >= l1; i -= 2) {
        if (i <= r0 && abs(i - r0) % 2 == 0) i--;
        a[i] = c[1];
    }

    cout << "Possible" << endl;
    cout << l << ' ' << r << endl;
    for (int i = 1; i <= n; i++) cout << "CPW "[a[i]];
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
