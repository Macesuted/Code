/**
 * @file 2076.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
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

#define maxn 15
#define maxm 1005

typedef pair<double, double> pdd;

mt19937 rnd(114514);
int X[maxn], Y[maxn], R[maxn], px[maxm], py[maxm];
int n, m, r, ans;
double x, y;

double sqr(double x) { return x * x; }
double dist(pdd x, pdd y) { return sqrt(sqr(x.first - y.first) + sqr(x.second - y.second)); }

int query(double x, double y) {
    double d = r;
    for (int i = 1; i <= n; i++) d = min(d, dist({x, y}, {X[i], Y[i]}) - R[i]);
    int cnt = 0;
    for (int i = 1; i <= m; i++) cnt += (dist({x, y}, {px[i], py[i]}) <= d);
    return cnt;
}

void solve(void) {
    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++) cin >> X[i] >> Y[i] >> R[i];
    for (int i = 1; i <= m; i++) cin >> px[i] >> py[i], x += px[i], y += py[i];
    x /= m, y /= m, ans = query(x, y);
    while (clock() * 1000. / CLOCKS_PER_SEC < 800)
        for (double temp = 100; temp > 1e-10; temp *= 0.998) {
            double nx = x + int(rnd()) * temp, ny = y + int(rnd()) * temp;
            int nans = query(nx, ny);
            if (nans > ans || exp((ans - nans) / temp) * UINT32_MAX < rand()) x = nx, y = ny, ans = nans;
        }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}