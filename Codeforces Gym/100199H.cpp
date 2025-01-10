/**
 * @file 100199H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

#define maxn 105
#define maxv 100005

typedef __int128_t int128_t;

vector<int> primes;
bool notp[maxv];
int128_t base[maxn];

void solve(void) {
    int t, m;
    cin >> t >> m;

    for (int i = 2; (int)primes.size() < t; i++) {
        if (!notp[i]) primes.push_back(i);
        for (auto j = primes.begin(); i * *j < maxv; j++) {
            notp[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int128_t ans = 1;
    for (int i = 1, v; i <= m; i++) {
        cin >> v;

        int128_t x = 0;
        for (int j = 0; j < t; j++)
            while (v % primes[j] == 0) x ^= (int128_t)1 << j, v /= primes[j];

        for (int j = 0; j < t; j++) {
            if (!(x >> j & 1)) continue;
            if (!base[j]) {
                base[j] = x;
                break;
            }
            x ^= base[j];
        }
        if (!x) ans <<= 1;
    }

    ans--;
    if (!ans) return cout << 0 << endl, void();
    string str;
    while (ans) str.push_back('0' + ans % 10), ans /= 10;
    reverse(str.begin(), str.end());
    cout << str << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("rsa.in", "r", stdin), freopen("rsa.out", "w", stdout);
#endif
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