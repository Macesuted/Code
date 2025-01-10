/**
 * @file 105631C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
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

typedef tuple<int, int64_t, int> tili;

set<tili> S;

int pel[maxn][27];
tili cur[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; i++) S.emplace(cur[i] = {0, 0, i});

    int rank0 = 1;
    while (m--) {
        string tim;
        int team;
        char prob;
        string status;
        cin >> tim >> team >> prob >> status;

        int clk = stoi(tim.substr(0, 2)) * 60 + stoi(tim.substr(3, 2));

        if (pel[team][prob - 'A'] == -1) continue;

        if (status == "RJ") {
            pel[team][prob - 'A'] += 20;
            continue;
        }

        tili oCur = cur[team];
        get<0>(cur[team])--, get<1>(cur[team]) += clk + pel[team][prob - 'A'];
        pel[team][prob - 'A'] = -1;

        if (team) {
            S.erase(oCur);
            S.insert(cur[team]);
            if (cur[team] < cur[0] && cur[0] < oCur) rank0++;
            continue;
        }

        int ork = rank0;

        auto p = S.erase(S.find(oCur));
        while (p != S.begin() && cur[0] < *prev(p)) p--, rank0--;
        S.insert(cur[0]);

        cout << tim << ' ' << prob << " #" << ork << " -> #" << rank0 << endl;
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