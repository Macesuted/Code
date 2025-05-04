/**
 * @file 108217E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

#define maxn 1000005
#define maxm 10005
#define mod 998244353

using pil = pair<int, int64_t>;

int a[maxm], f[maxn];
bool S[maxn * 2], T[maxn * 2];

int Mod(int x) { return x >= mod ? x - mod : x; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, m, L;
    cin >> n >> m >> L;

    for (int i = 1; i <= m; i++) cin >> a[i], S[a[i]] = true, T[a[i] + L] = true;

    sort(a + 1, a + m + 1);

    auto solve = [&](int l, int r) -> int64_t {
        deque<pil> que;
        for (int i = 1; i <= n; i++) f[i] = 0;
        f[l] = 1;
        for (int i = 1; i <= n; i++) {
            bool upd = false;
            f[i] = Mod(f[i] + f[i - 1]);
            if (T[i]) f[i] = Mod(f[i] + que[0].second), que.pop_front();
            if (S[i]) que.emplace_back(i, 0), upd = true;
            if (upd) {
                que[0].second = Mod(que[0].second + f[i]);
                for (int i = 1; i < (int)que.size(); i++) que[i].second = Mod(que[i].second + que[i - 1].second);
            }
        }
        return f[r];
    };

    cout << ((solve(2, n - 1) + solve(1, n) * solve(2, n - 1) - solve(1, n - 1) * solve(2, n)) % mod + mod) % mod;

    return 0;
}