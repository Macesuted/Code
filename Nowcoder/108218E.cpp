/**
 * @file 108218E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

char buf[1 << 21], *p1 = buf, *p2 = buf;
char gc() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? -1 : *p1++); }
int64_t read() {
    int64_t x = 0;
    char c = gc();
    while (c < 48 || c > 57) c = gc();
    for (; c > 47 && c < 58; c = gc()) x = x * 10 + (c ^ 48);
    return x;
}

#define maxn 1000005
#define mod 998244353
#define B 405

using tiii = tuple<int, int, int>;

int f[B][B][B];

int main() {
    int n = read(), q = read();

    while (n--) {
        int m = read();

        vector<tiii> a;
        for (int i = 1, x, y, z; i <= m; i++) x = read(), y = read(), z = read(), a.emplace_back(z, x, y);
        sort(a.begin(), a.end());

        map<int, int> S;

        S[0] = 401, S[401] = 0;
        for (auto [z, x, y] : a) {
            auto g = f[z];

            auto update = [&](auto pl, auto pc, auto pr, int delt) -> void {
                g[pc->first][pc->second] += delt;
                g[pc->first][pl->second] -= delt;
                g[pr->first][pc->second] -= delt;
                g[pr->first][pl->second] += delt;
                return;
            };

            auto pl = --S.upper_bound(x);
            if (pl->second <= y) continue;
            if (pl->first == x) pl--;
            auto pr = next(pl);

            while (pr->second >= y) {
                auto pc = pr;
                pr++;
                update(pl, pc, pr, -1);
                S.erase(pc);
            }

            auto pc = S.emplace(x, y).first;
            update(pl, pc, pr, +1);
        }
    }

    for (int i = 1; i < B; i++)
        for (int j = 1; j < B; j++)
            for (int k = 1; k < B; k++) f[i][j][k] += f[i - 1][j][k];
    for (int i = 1; i < B; i++)
        for (int j = 1; j < B; j++)
            for (int k = 1; k < B; k++) f[i][j][k] += f[i][j - 1][k];
    for (int i = 1; i < B; i++)
        for (int j = 1; j < B; j++)
            for (int k = 1; k < B; k++) f[i][j][k] += f[i][j][k - 1];

    int64_t seed = read(), lastans = 0, ans = 0;
    mt19937 rng(seed);
    uniform_int_distribution<> u(1, 400);
    seed %= mod;
    while (q--) {
        int x = (u(rng) ^ lastans) % 400 + 1;
        int y = (u(rng) ^ lastans) % 400 + 1;
        int z = (u(rng) ^ lastans) % 400 + 1;
        lastans = f[z][x][y];
        ans = (ans * seed + lastans) % mod;
    }

    cout << ans << endl;

    return 0;
}