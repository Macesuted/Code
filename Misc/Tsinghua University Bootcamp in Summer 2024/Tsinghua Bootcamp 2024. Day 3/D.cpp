/**
 * @file D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

int64_t l[maxn], r[maxn];

bool mem2;

void solve(void) {
    int n;
    int64_t sum, suml = 0, sumr = 0;
    cin >> n >> sum;
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i], suml += l[i], sumr += r[i];
    for (int i = 1; i <= n; i++) {
        suml -= l[i], sumr -= r[i];
        int64_t vl = max(l[i], sum - sumr), vr = min(r[i], sum - suml);
        cout << max((int64_t)0, vr - vl + 1) << ' ';
        suml += l[i], sumr += r[i];
    }
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}