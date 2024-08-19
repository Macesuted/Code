/**
 * @file 7535.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int a[maxn], b[maxn];

bool solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
    int cnt = 0;
    for (int i = 1; i < n; i++) cnt += (a[i] == a[i + 1]);
    if (cnt == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "shuishui" : "sha7dow") << endl;

    return 0;
}