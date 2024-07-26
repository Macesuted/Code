/**
 * @file 7457.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005
#define mod 998244353

int f[maxn], g[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    f[1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j * i <= n; j++) f[i * j + 1] = Mod(f[i * j + 1] + f[i]), g[i * j] = Mod(g[i * j] + f[i]);

    for (int i = 1; i <= n; i++) cout << g[i] << ' ';
    cout << endl;

    return 0;
}