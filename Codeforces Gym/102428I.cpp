/**
 * @file 102428I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 2005
#define mod 1000000007

vector<int> graph[maxn];

int f[maxn];
int n, m;

int64_t dfs(int p) {
    if (p > m) return f[p] = 1;
    f[p] = 0;
    for (auto i : graph[p])
        if (f[i])
            f[p] = (f[p] + f[i]) % mod;
        else
            f[p] = (f[p] + dfs(i)) % mod;
    return f[p];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1, s, x; i <= m; i++) {
        cin >> s;
        while (s--) cin >> x, graph[i].push_back(x);
    }

    cout << dfs(1) << ' ';

    int tot = 0;
    for (int i = m + 1; i <= n; i++) tot += f[i];

    cout << tot << endl;

    return 0;
}