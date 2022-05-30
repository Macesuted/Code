/**
 * @file 2035.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 3005

typedef pair<int, int> pii;

int a[maxn], s[maxn], f[maxn][maxn];
deque<pii> que;

double slope(pii a, pii b) { return (b.second - a.second) / (b.first - a.first); }
int calc(int x, pii f) { return x * f.first + f.second; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i - 1] + a[i];
    for (int i = 0; i <= n; i++) f[1][i] = s[i] * s[i];
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            pii node = {2 * s[j], f[i - 1][j] + s[j] * s[j]};
            while (que.size() > 1 && slope(que[que.size() - 2], que.back()) > slope(que.back(), node)) que.pop_back();
            que.push_back(node);
            while (que.size() > 1 && calc(-s[j], que.front()) > calc(-s[j], que[1])) que.pop_front();
            f[i][j] = calc(-s[j], que.front()) + s[j] * s[j];
        }
        que.clear();
    }
    cout << m * f[m][n] - s[n] * s[n] << endl;
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