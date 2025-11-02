/**
 * @file 9327.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn], p[maxn], sum[maxn], cnt[maxn];
map<int, int> S;

void solve(void) {
    int n, q;
    cin >> n >> q;
    int B = sqrt(n);

    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;

    auto add = [&](int x, int y, int delt) -> void {
        int64_t v = abs(x - y) * abs(a[x] - a[y]);
        if (v > maxn) return;
        sum[v / B] += delt, cnt[v] += delt;
        return;
    };
    auto getAns = [&](void) -> int {
        int ans = 0;
        while (!sum[ans / B]) ans += B;
        while (!cnt[ans]) ans++;
        return ans;
    };

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= min(n, i + B); j++) add(i, j, +1), add(p[i], p[j], +1);

    cout << getAns() << endl;
    while (q--) {
        int x, y;
        cin >> x >> y;

        auto calc = [&](int delt) -> void {
            for (int i = max(1, x - B); i <= min(n, x + B); i++)
                if (i != x) add(x, i, delt);
            for (int i = max(1, y - B); i <= min(n, y + B); i++)
                if (i != x && i != y) add(y, i, delt);
            for (int i = max(1, a[x] - B); i <= min(n, a[x] + B); i++)
                if (i != a[x]) add(x, p[i], delt);
            for (int i = max(1, a[y] - B); i <= min(n, a[y] + B); i++)
                if (i != a[x] && i != a[y]) add(y, p[i], delt);
            return;
        };

        calc(-1);
        swap(a[x], a[y]);
        swap(p[a[x]], p[a[y]]);
        calc(+1);

        cout << getAns() << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
