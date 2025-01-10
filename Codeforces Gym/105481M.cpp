/**
 * @file 105481M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-06
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

#define maxn 100005

typedef tuple<int, int, int> tiii;

int a[maxn], tab[10], vis[maxn], ans[maxn];

void solve(void) {
    int n, m, k, luc, unhappy = 0;
    cin >> n >> m >> k >> luc;

    for (int i = 1; i <= k; i++) cin >> a[i];

    queue<int> que;
    int tcnt = n + 1;
    for (int i = 1; i <= n; i++) que.push(a[i]);

    auto nxt = [&]() {
        if (tcnt <= k)
            que.push(a[tcnt++]);
        else
            unhappy++;
        return;
    };

    for (int i = 1; i <= 9; i++) tab[i] = -1;

    while (true) {
        bool op = false;

        // 1.
        {
            bool cont = false;
            for (int i = 1; i <= 9 && !que.empty(); i++)
                if (tab[i] == -1) {
                    op = true;

                    tab[i] = que.front();
                    que.pop();

                    if (tab[i] == luc) nxt();
                    if (tab[i] == 0) {
                        ans[0]++, tab[i] = -1;
                        nxt();
                        cont = true;
                        break;
                    }
                }
            if (cont) continue;
        }

        // 2.
        {
            bool chk = true;
            for (int i = 1; i <= 9; i++) chk &= (tab[i] != -1);
            if (chk) {
                for (int i = 1; i <= 9; i++) vis[tab[i]]++;
                for (int i = 1; i <= 9; i++) chk &= (vis[tab[i]] == 1);
                for (int i = 1; i <= 9; i++) vis[tab[i]]--;
                if (chk) {
                    op = true;

                    ans[tab[1]]++, tab[1] = -1;
                    continue;
                }
            }
        }

        bool useSpe = false;

        // 3.
        {
            vector<tiii> valid;

            auto chk = [&](int x, int y, int z) {
                if (tab[x] != -1 && tab[x] == tab[y] && tab[y] == tab[z]) {
                    if (x > y) swap(x, y);
                    if (x > z) swap(x, z);
                    if (y > z) swap(y, z);
                    valid.emplace_back(x, y, z);
                }
                return;
            };

            while (true) {
                valid.clear();

                chk(2, 5, 7);
                chk(3, 1, 8);
                chk(4, 6, 9);
                chk(2, 3, 4);
                chk(5, 1, 6);
                chk(7, 8, 9);
                chk(2, 1, 9);
                chk(4, 1, 7);

                if (valid.empty()) break;

                op = true;

                sort(valid.begin(), valid.end());

                auto [x, y, z] = valid.front();
                useSpe |= (x == 1 || y == 1 || z == 1);
                if (x != 1) ans[tab[x]]++, tab[x] = -1;
                if (y != 1) ans[tab[y]]++, tab[y] = -1;
                if (z != 1) ans[tab[z]]++, tab[z] = -1;
                for (int t = 0; t < 5; t++) nxt();
            }
        }

        // 4.
        {
            for (int i = 1; i <= 9; i++)
                for (int j = i + 1; j <= 9; j++)
                    if (tab[i] != -1 && tab[i] == tab[j]) {
                        op = true;

                        useSpe |= (i == 1 || j == 1);
                        if (i != 1) ans[tab[i]]++, tab[i] = -1;
                        if (j != 1) ans[tab[j]]++, tab[j] = -1;
                        nxt();
                    }
        }

        // 5.
        {
            if (useSpe) op = true, ans[tab[1]]++, tab[1] = -1;
        }

        // 6.
        {
            if (!op) {
                for (int i = 1; i <= 9; i++)
                    if (tab[i] != -1) ans[tab[i]]++;
                break;
            } else {
                bool chk = true;
                for (int i = 1; i <= 9; i++) chk &= (tab[i] == -1);
                if (chk)
                    for (int t = 0; t < 10; t++) nxt();
            }
        }
    }

    for (int i = 0; i <= m; i++) cout << ans[i] << ' ';
    cout << endl;
    if (unhappy) cout << "Unhappy! " << unhappy << endl;

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