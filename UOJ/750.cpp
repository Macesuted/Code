/**
 * @file train.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-07
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

int64_t a[45], f[1 << 22], mod;
int lg2[1 << 22];
vector<pll> A1, A2;

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n;
    cin >> n >> mod;
    int m = n / 2;
    for (int i = 0; i < n; i++) cin >> a[i];
    A1.emplace_back(f[0] = 0, 0);
    for (int i = 0; i < 22; i++) lg2[1 << i] = i;
    for (int S = 1; S < (1 << m); S++) {
        int lbt = S & -S;
        A1.emplace_back(f[S] = Mod(a[lg2[lbt]] + f[S ^ lbt]), S);
    }
    A2.emplace_back(f[0] = 0, 0);
    for (int S = 1; S < (1 << (n - m)); S++) {
        int lbt = S & -S;
        A2.emplace_back(f[S] = Mod(a[lg2[lbt] + m] + f[S ^ lbt]), S);
    }
    sort(A1.begin(), A1.end()), sort(A2.begin(), A2.end());
    for (int i = 1; i < (int)A1.size(); i++)
        if (A1[i - 1].first == A1[i].first) {
            int S = A1[i - 1].second, T = A1[i].second;
            for (int x = 0; x < m; x++) cout << (S >> x & 1) - (T >> x & 1) << ' ';
            for (int x = m; x < n; x++) cout << 0 << ' ';
            cout << endl;
            return;
        }
    for (int i = 1; i < (int)A2.size(); i++)
        if (A2[i - 1].first == A2[i].first) {
            int S = A2[i - 1].second, T = A2[i].second;
            for (int x = 0; x < m; x++) cout << 0 << ' ';
            for (int x = m; x < n; x++) cout << (S >> (x - m) & 1) - (T >> (x - m) & 1) << ' ';
            cout << endl;
            return;
        }
    int64_t l = 0, r = mod - 1;
    while (l < r) {
        int64_t mid = (l + r) >> 1, cnt = 0;
        for (int t = 0; t < 2; t++)
            for (auto i = A1.begin(), jl = A2.end(), jr = A2.end(); i != A1.end(); i++) {
                while (jl != A2.begin() && i->first + (jl - 1)->first >= l + t * mod) jl--;
                while (jr != A2.begin() && i->first + (jr - 1)->first > mid + t * mod) jr--;
                cnt += jr - jl;
            }
        if (cnt > mid - l + 1)
            r = mid;
        else
            l = mid + 1;
    }
    int64_t X = -1;
    for (auto i : A1)
        for (int t = 0; t < 2; t++) {
            auto p = lower_bound(A2.begin(), A2.end(), pll{l + t * mod - i.first, 0});
            if (p != A2.end() && p->first == l + t * mod - i.first) {
                int64_t S = i.second | (p->second << m);
                if (X == -1) {
                    X = S;
                    continue;
                }
                for (int i = 0; i < n; i++) cout << (S >> i & 1) - (X >> i & 1) << ' ';
                cout << endl;
                return;
            }
        }
    cout << "IMPOSSIBLE" << endl;
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