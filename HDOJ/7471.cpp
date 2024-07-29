/**
 * @file 7471.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

typedef pair<int, int> pii;

vector<int> prime;
bool notPrime[maxn];

int a[maxn], f[maxn];
int64_t sum[maxn];
int n, k;

int read() {
    char ch = getchar();
    int res = 0, f = +1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res * f;
}

bool check(int64_t lim) {
    set<pii> S;
    for (int r = 1, cnt = 0; r <= n; r++) {
        S.emplace(sum[r - 1], r);
        for (auto [v, l] : S) {
            if (sum[r] - v < lim) break;
            if (notPrime[r - l + 1]) continue;
            cnt++, S.clear();
            break;
        }
        if (cnt == k) return true;
    }
    return false;
}

void solve(void) {
    n = read(), k = read();
    for (int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i - 1] + a[i];

    if (2 * k > n) return cout << "impossible" << endl, void();

    int64_t l = -1e6, r = +1e6;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1;
        (check(mid) ? l : r) = mid;
    }

    cout << l << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    notPrime[1] = true;
    for (int i = 2; i < maxn; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxn; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = read();
    while (_--) solve();

    return 0;
}