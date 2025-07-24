/**
 * @file 104396F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

double f[maxn];

void solve(void) {
    int A, B;
    double P, Q;
    cin >> A >> B >> P >> Q, P /= 100, Q /= 100;

    for (int i = B; i <= A; i++)
        f[i] = max(f[i - B] + 1 + P, B == 1 ? f[i - 1] + 1 / (1 - Q) : 1 + f[i - B] * (1 - Q) + f[i - B + 1] * Q);

    cout << fixed << setprecision(15) << f[A] << endl;

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