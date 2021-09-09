/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define eps 1e-7

double ans;
void work(double c, double m, double p, double v, double a, int step = 1) {
    // cerr << "#" << c << ' ' << m << ' ' << p << ' ' << v << ' ' << a << ' ' << step << endl;
    ans += step * p * a;
    if (fabs(c) <= eps && fabs(m) <= eps) return;
    if (fabs(c) <= eps) return work(c, m - min(m, v), p + min(m, v), v, a * m, step + 1);
    if (fabs(m) <= eps) return work(c - min(c, v), m, p + min(c, v), v, a * c, step + 1);
    double t = min(m, v);
    work(c + 0.5 * t, m - t, p + 0.5 * t, v, a * m, step + 1);
    t = min(c, v);
    work(c - t, m + 0.5 * t, p + 0.5 * t, v, a * c, step + 1);
    return;
}

void solve(void) {
    double c, m, p, v;
    cin >> c >> m >> p >> v;
    ans = 0;
    work(c, m, p, v, 1);
    cout << ans << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) solve();
    return 0;
}