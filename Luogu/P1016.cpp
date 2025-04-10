/**
 * @file P1016.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-10
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

double price[10], dist[10];

void solve(void) {
    double Dn, maxGas, gas2Dist;
    int n;
    cin >> Dn >> maxGas >> gas2Dist >> price[0] >> n;
    dist[0] = 0, dist[n + 1] = Dn;
    for (int i = 1; i <= n; i++) cin >> dist[i] >> price[i];

    double ans = 0;

    deque<pair<double, double>> que;
    que.emplace_back(maxGas, price[0]);
    for (int i = 1; i <= n + 1; i++) {
        double costGas = (dist[i] - dist[i - 1]) / gas2Dist, totalUsedGas = 0;
        while (costGas > 0 && !que.empty()) {
            double usedGas = min(costGas, que.front().first);
            costGas -= usedGas, que.front().first -= usedGas, totalUsedGas += usedGas, ans += usedGas * que.front().second;
            if (que.front().first == 0) que.pop_front();
        }

        if (costGas > 0) return cout << "No Solution" << endl, void();

        if (i > n) break;

        while (!que.empty() && que.back().second > price[i]) totalUsedGas += que.back().first, que.pop_back();
        que.emplace_back(totalUsedGas, price[i]);
    }

    cout << setprecision(2) << fixed << ans << endl;

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