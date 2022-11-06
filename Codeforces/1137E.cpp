/**
 * @file 1137E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

typedef pair<int64_t, int64_t> pll;

deque<pll> S;

void solve(void) {
    int64_t n, m, mul = 0, plus = 0;
    cin >> n >> m;
    S.emplace_back(0, 0);
    auto calc = [&](pll a) { return a.first * mul + plus + a.second; };
    auto slope = [&](pll a, pll b) { return 1. * (a.second - b.second) / (b.first - a.first); };
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k;
            cin >> k;
            while (!S.empty()) S.pop_back();
            S.emplace_back(0, 0), mul = plus = 0, n += k;
        } else if (op == 2) {
            int k;
            cin >> k;
            if (calc(S.back())) {
                pll p = {n, -mul * n - plus};
                while (S.size() > 1 && slope(S[S.size() - 2], S[S.size() - 1]) < slope(S[S.size() - 1], p)) S.pop_back();
                S.push_back(p);
            }
            n += k;
        } else {
            int64_t b, s;
            cin >> b >> s;
            mul = mul + s, plus = plus + b;
            while ((S.size() > 1 && calc(S[S.size() - 2]) <= calc(S[S.size() - 1]))) S.pop_back();
        }
        cout << S.back().first + 1 << ' ' << calc(S.back()) << endl;
    }
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