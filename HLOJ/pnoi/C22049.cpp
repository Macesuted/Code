/**
 * @file C22049.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-07
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

#define maxn 305
#define base 1000000000

typedef tuple<double, int, int, int, int> tdiiii;

class Integer {
   private:
    int64_t num[2000];

   public:
    Integer(void) { num[0] = 1; }
    void multi(int v) {
        for (int i = 0; i < 2000; i++) num[i] *= v;
        for (int i = 0; i < 1999; i++) num[i + 1] += num[i] / base, num[i] %= base;
        return;
    }
    void print(void) {
        int p = 1999;
        while (!num[p]) p--;
        cout << num[p];
        for (int i = p - 1; ~i; i--) {
            stack<int> S;
            for (int j = 0, v = num[i]; j < 9; j++) S.push(v % 10), v /= 10;
            while (!S.empty()) cout << char('0' + S.top()), S.pop();
        }
        return;
    }
} val;

int a[maxn][maxn];
double b[maxn][maxn], sum[maxn][maxn];

double getSum(int xl, int xr, int yl, int yr) { return sum[xr][yr] - sum[xl - 1][yr] - sum[xr][yl - 1] + sum[xl - 1][yl - 1]; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    tdiiii ans = {0, 0, 0, 0, 0};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j], b[i][j] = log(a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) sum[i][j] = b[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            for (int r = 2, l = 1; r <= m; r++) {
                ans =
                    max(ans, {getSum(i, i, l, r) + getSum(j, j, l, r) + getSum(i + 1, j - 1, l, l) + getSum(i + 1, j - 1, r, r),
                              i, j, l, r});
                if (getSum(i + 1, j - 1, r, r) - getSum(i, i, 1, r - 1) - getSum(j, j, 1, r - 1) >
                    getSum(i + 1, j - 1, l, l) - getSum(i, i, 1, l - 1) - getSum(j, j, 1, l - 1))
                    l = r;
            }
    int xl = get<1>(ans), xr = get<2>(ans), yl = get<3>(ans), yr = get<4>(ans);
    for (int i = xl; i <= xr; i++) val.multi(a[i][yl]), val.multi(a[i][yr]);
    for (int i = yl + 1; i < yr; i++) val.multi(a[xl][i]), val.multi(a[xr][i]);
    val.print(), cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("frame.in", "r", stdin), freopen("frame.out", "w", stdout);
#endif
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