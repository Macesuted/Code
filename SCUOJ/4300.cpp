/**
 * @file 4300.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

#define maxn 155

typedef tuple<int, int, int> tiii;

short cnt[maxn][maxn][maxn];
long long f[maxn][maxn][maxn];
long long A[maxn], B[maxn], C[maxn];
tiii a[maxn];

bool mem1;

void solve(int n) {
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]);
    for (int i = 1; i <= n; i++) cin >> get<1>(a[i]);
    for (int i = 1; i <= n; i++) cin >> get<2>(a[i]);
    long long sum = 0;
    for (int i = 1; i <= n; i++) A[i] = get<0>(a[i]), B[i] = get<1>(a[i]), C[i] = get<2>(a[i]), sum += A[i] + B[i] + C[i];
    sort(A + 1, A + n + 1), sort(B + 1, B + n + 1), sort(C + 1, C + n + 1);
    for (int i = 1; i <= n; i++)
        get<0>(a[i]) = lower_bound(A + 1, A + n + 1, get<0>(a[i])) - A,
        get<1>(a[i]) = lower_bound(B + 1, B + n + 1, get<1>(a[i])) - B,
        get<2>(a[i]) = lower_bound(C + 1, C + n + 1, get<2>(a[i])) - C;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) cnt[get<0>(a[i])][get<1>(a[i])][get<2>(a[i])]++;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) cnt[i][j][k] += cnt[i - 1][j][k];
    for (int j = 2; j <= n; j++)
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= n; k++) cnt[i][j][k] += cnt[i][j - 1][k];
    for (int k = 2; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) cnt[i][j][k] += cnt[i][j][k - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                long long c = A[i] + B[j] + C[k];
                f[i][j][k] = min({f[i - 1][j][k] + c * (cnt[i][j][k] - cnt[i - 1][j][k]),
                                  f[i][j - 1][k] + c * (cnt[i][j][k] - cnt[i][j - 1][k]),
                                  f[i][j][k - 1] + c * (cnt[i][j][k] - cnt[i][j][k - 1])});
            }
    cout << f[n][n][n] - sum << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int n;
    while (cin >> n) solve(n);

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
