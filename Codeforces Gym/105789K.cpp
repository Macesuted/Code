/**
 * @file 105789K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-20
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

using int128_t = __int128_t;

vector<int64_t> mul, add;
int att = 0;

void solve(void) {
    int n;
    int64_t ans = 0, P, H;
    cin >> n >> P >> H;

    for (int i = 1; i <= n; i++) {
        char op;
        cin >> op;
        if (op == '!')
            att++;
        else {
            int v;
            cin >> v;
            if (op == '*') {
                if (v > 1) mul.push_back(v);
            } else
                add.push_back(v);
        }
    }

    sort(add.begin(), add.end(), greater<int64_t>());
    sort(mul.begin(), mul.end(), greater<int64_t>());

    if (!att) return cout << '*' << endl, void();

    int64_t addSum = 0;
    for (auto i : add) addSum += i;

    if (!addSum && !P) return cout << '*' << endl, void();

    if (mul.empty()) {
        auto getSum = [&](int k) -> int128_t { return att * min((int128_t)H, k * P + (int128_t)k * (k + 1) / 2 * addSum); };

        int l = 0, r = 1e9 + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (getSum(mid) < H ? l : r) = mid;
        }

        H -= getSum(l), ans += (int64_t)l * n, P += l * addSum;
    } else {
        auto getAtt = [&](void) -> int64_t {
            int64_t val = P;
            val += addSum;
            if (val > H) return H;
            for (auto x : mul) {
                val *= x;
                if (val > H) return H;
            }
            return val;
        };

        int64_t val = getAtt();
        while (val * att < H) P = val, H -= val * att, ans += n, val = getAtt();
    }

    int64_t minAns = INT_MAX;

    for (int x = -1; x < (int)add.size(); x++) {
        P += (x == -1 ? 0 : add[x]);
        if (!P) continue;
        int64_t nP = P;
        for (int y = -1; y < (int)mul.size(); y++) {
            nP = min(H, nP * (y == -1 ? 1 : mul[y]));
            if (nP * att >= H) minAns = min(minAns, x + y + 2 + H / nP + (H % nP > 0));
        }
    }

    cout << ans + minAns << endl;

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