/**
 * @file 6039.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1000005
#define maxc 305

vector<int> a[maxc];
int64_t f[2][maxn], sum[maxn];
int n, K;

void solve(int x, int y, int l, int r, int vl, int vr) {
    if (l > r) return;
    bool t = x & 1;
    int mid = (l + r) >> 1, vmid = -1;
    f[t][mid * x + y] = -1;
    for (int i = max(mid - (int)a[x].size(), vl); i <= min(mid, vr); i++)
        if (f[!t][i * x + y] + sum[mid - i] > f[t][mid * x + y]) f[t][mid * x + y] = f[!t][i * x + y] + sum[mid - i], vmid = i;
    return solve(x, y, l, mid - 1, vl, vmid), solve(x, y, mid + 1, r, vmid, vr);
}

void solve(void) {
    cin >> n >> K;
    for (int i = 1, c, v; i <= n; i++) cin >> c >> v, a[c].push_back(v);
    for (int i = 1; i <= 300; i++) {
        sort(a[i].begin(), a[i].end(), greater<int>());
        sum[0] = 0;
        for (int j = 1; j <= (int)a[i].size(); j++) sum[j] = sum[j - 1] + a[i][j - 1];
        for (int j = 0; j < i; j++) solve(i, j, 0, K / i - (K % i < j), 0, K / i - (K % i < j));
    }
    for (int i = 1; i <= K; i++) cout << f[0][i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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