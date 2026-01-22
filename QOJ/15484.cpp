/**
 * @file 15484.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

// a * x + b * y = gcd(a, b)
int64_t exgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b) {
        int64_t d = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
    x = 1, y = 0;
    return a;
}

#define maxn 1005

using pll = pair<int64_t, int64_t>;

int64_t a[maxn][maxn], sr[maxn], sc[maxn];
pll fr[maxn], fc[maxn];
int64_t gr[maxn], gc[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    int64_t sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j], sum += a[i][j], sr[i] += a[i][j], sc[j] += a[i][j];

    if (sum % n || sum % m) return cout << -1 << endl, void();

    int64_t sR = sum / n, sC = sum / m;

    fr[1] = fc[1] = {1, 0};
    fr[2] = {1, sr[1] - sR}, fc[2] = {1, sc[1] - sC};
    for (int i = 2; i < n; i++)
        fr[i + 1] = {-fr[i - 1].first + 2 * fr[i].first, -fr[i - 1].second + 2 * fr[i].second + sr[i] - sR};
    for (int i = 2; i < m; i++)
        fc[i + 1] = {-fc[i - 1].first + 2 * fc[i].first, -fc[i - 1].second + 2 * fc[i].second + sc[i] - sC};

    pll sumr, sumc;
    for (int i = 1; i <= n; i++) sumr.first += fr[i].first, sumr.second += fr[i].second;
    for (int i = 1; i <= m; i++) sumc.first += fc[i].first, sumc.second += fc[i].second;

    int64_t A = sumr.first, B = sumc.first, C = sumc.second - sumr.second, X, Y;
    if (C % gcd(A, B)) return cout << -1 << endl, void();
    typedef long long LL;
    LL g = exgcd(A, B, X, Y);
    X *= C / gcd(A, B), Y *= -C / gcd(A, B);
    LL k = X / (B / g);
    X -= k * (B / g);
    Y -= k * (A / g);

    for (int i = 1; i <= n; i++) gr[i] = fr[i].first * X + fr[i].second;
    for (int i = 1; i <= m; i++) gc[i] = fc[i].first * Y + fc[i].second;

    int64_t sumf = gr[1];
    for (int i = 2; i <= m; i++) sumf -= gc[i];

    vector<tuple<int, int, int64_t>> ans;
    if (sumf) ans.emplace_back(1, 1, sumf);
    for (int i = 2; i <= n; i++)
        if (gr[i]) ans.emplace_back(i, 1, gr[i]);
    for (int i = 2; i <= m; i++)
        if (gc[i]) ans.emplace_back(1, i, gc[i]);

    cout << ans.size() << endl;
    for (auto [x, y, v] : ans) cout << x << ' ' << y << ' ' << v << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
