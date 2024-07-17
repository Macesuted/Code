/**
 * @file 535265F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 105

typedef pair<int, double> pid;

int A[maxn], B[maxn], C[maxn], D[maxn], E[maxn], F[maxn], G[maxn], H[maxn], I[maxn], U[maxn], V[maxn], J[maxn], K[maxn],
    L[maxn], R[maxn], P[maxn][maxn];
bool able[maxn][maxn];
double f[maxn][maxn][maxn][2], sh[maxn << 1];

void solve(void) {
    int X, n, m;
    cin >> X >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i] >> E[i] >> F[i] >> G[i] >> H[i] >> I[i] >> U[i] >> V[i] >> J[i] >> K[i] >> L[i] >>
            R[i];
        for (int j = 1; j <= n; j++) cin >> P[i][j];
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = U[i]; k <= V[i] && !able[i][j]; k++)
                if (L[k] <= j && j <= R[k]) able[i][j] = true;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 1; k <= m; k++) f[i][j][k][0] = f[i][j][k][1] = -1e9;

    f[0][0][1][1] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++) {
            for (int k = 1; k <= m; k++) f[i + 1][j][k][1] = max({f[i + 1][j][k][1], f[i][j][k][0], f[i][j][k][1]});
            for (int k = 1; k <= m; k++) {
                if (i + 1 < L[k] || i + 1 > R[k]) continue;
                double sum = -114514, stock = 0;
                for (int lk = 1; lk <= m; lk++)
                    if (k != lk || i == 0) {
                        sum = max(sum, f[i][j][lk][1]);
                        if (k < U[lk] || k > V[lk]) sum = max(sum, f[i][j][lk][0]);
                    }
                if (sum < 0) continue;

                sum += A[k] * (X + j) + B[k];

                stack<pid> S;
                for (int t = 1; i + t <= R[k]; t++) sh[i + t] = 0;
                for (int t = 1; i + t <= R[k]; t++) {
                    double share = double(G[k] * (X + j + t - 1) + H[k]) / I[k];
                    sh[i + t + 1] += share, sh[i + t + I[k] + 1] -= share;
                }
                for (int t = 2; i + t <= R[k]; t++) sh[i + t] += sh[i + t - 1];
                for (int t = 1; i + t <= R[k]; t++) {
                    int Y = X + j + t - 1, Z = t - 1;
                    sum += C[k] * Y + D[k];
                    if (i + t == R[k])
                        sum += (Z + 2) * (C[k] * Y + D[k]) / 12.;
                    else
                        sum += E[k] * Z + F[k];
                    double share = sh[i + t];
                    while (!S.empty() && S.top().first <= P[k][i + t])
                        share += S.top().second, stock -= S.top().first * S.top().second, S.pop();
                    S.emplace(P[k][i + t], share), stock += P[k][i + t] * share;
                    if (i + t == R[k])
                        f[i + t][j + t][k][1] = max(f[i + t][j + t][k][1], sum + stock);
                    else if (able[k][i + t + 1])
                        f[i + t + 1][j + t][k][1] = max(f[i + t + 1][j + t][k][1], sum + stock + J[k] * t + K[k]);
                    f[i + t][j + t][k][0] = max(f[i + t][j + t][k][0], sum + stock);
                    if (i == j && i + t == 4) {
                        cerr << i << ' ' << j << ' ' << k << ' ' << t << ' ' << sum + stock << endl;
                    }
                }
            }
        }

    double ans = 0;
    for (int j = 1; j <= n; j++)
        for (int k = 1; k <= m; k++) ans = max(ans, f[n][j][k][1]);
    // for (int j = 1; j <= n; j++)
    //     for (int k = 1; k <= m; k++)
    //         if (f[n][j][k][1] == ans) cerr << j << ' ' << k << ' ' << endl;
    cout << fixed << setprecision(12) << ans << endl;
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