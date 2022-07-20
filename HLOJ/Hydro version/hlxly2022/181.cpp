/**
 * @file 181.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

typedef __int128_t int128_t;
typedef pair<int, int> pii;

pii LP[maxn], RP[maxn];
int X;

struct COMP {
    bool operator()(int a, int b) const {
        return (RP[b].first - LP[b].first) * (LP[a].second * int128_t(RP[a].first - LP[a].first) +
                                              (RP[a].second - LP[a].second) * int128_t(X - LP[a].first)) <
               (RP[a].first - LP[a].first) * (LP[b].second * int128_t(RP[b].first - LP[b].first) +
                                              (RP[b].second - LP[b].second) * int128_t(X - LP[b].first));
    }
};

set<int, COMP> lines;
vector<int> graph[maxn], lis;
map<int, int> S1, S2, rec[2], id;
int indeg[maxn], f[maxn];
vector<int> nodes;

void solve(void) {
    int L, R, n;
    cin >> L >> R >> n;
    for (int i = 1; i <= n; i++) {
        cin >> LP[i].first >> LP[i].second >> RP[i].first >> RP[i].second;
        if (LP[i].first > RP[i].first) swap(LP[i], RP[i]);
        rec[0][LP[i].first] = rec[1][RP[i].first] = i;
    }
    auto p0 = rec[0].begin(), p1 = rec[1].begin();
    while (p0 != rec[0].end() || p1 != rec[1].end()) {
        X = min(p0 == rec[0].end() ? INT_MAX : p0->first, p1 == rec[1].end() ? INT_MAX : p1->first);
        if (p0 != rec[0].end() && p0->first == X) {
            auto p = lines.insert((p0++)->second).first, pl = p, pr = p;
            if (pl != lines.begin()) graph[*p].push_back(*(--pl));
            if (++pr != lines.end()) graph[*pr].push_back(*p);
        }
        if (p1 != rec[1].end() && p1->first == X) lines.erase((p1++)->second);
    }
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i]) indeg[j]++;
    static queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop(), lis.push_back(p);
        for (auto i : graph[p])
            if (!--indeg[i]) que.push(i);
    }
    S1[0] = 1e9, S2[L] = -1e9, S1[R + 1] = 1e9, S2[1e9 + 1] = -1e9;
    auto inc = [&](int p) {
        if (!S2.count(p))
            S1[p]++;
        else if (!++S2[p])
            S2.erase(p);
        return;
    };
    auto dec = [&](int p) {
        if (!S1.count(p))
            S2[p]--;
        else if (!--S1[p])
            S1.erase(p);
        return;
    };
    for (auto p : lis) {
        if (LP[p].second > RP[p].second) {
            map<int, int>::iterator pl = S1.lower_bound(LP[p].first + 1);
            while (pl != S1.end() && pl->first <= RP[p].first) {
                auto pr = S2.lower_bound(pl->first);
                if (pr == S2.end() || pr->first > RP[p].first + 1) {
                    S1[RP[p].first + 1] += pl->second, pl = S1.erase(pl);
                    continue;
                }
                int v = min(pl->second, -pr->second);
                pl->second -= v, pr->second += v;
                if (!pl->second) pl = S1.erase(pl);
                if (!pr->second) S2.erase(pr);
            }
            inc(LP[p].first + 1), dec(RP[p].first);
        } else {
            map<int, int>::iterator pr = S2.lower_bound(RP[p].first + 1);
            while (pr != S2.begin() && (--pr)->first > LP[p].first) {
                auto pl = S1.lower_bound(pr->first);
                if (pl == S1.begin() || (--pl)->first < LP[p].first) {
                    S2[LP[p].first] += pr->second, pr = S2.erase(pr);
                    continue;
                }
                int v = min(pl->second, -pr->second);
                pl->second -= v, pr->second += v;
                if (!pl->second) S1.erase(pl);
                if (!pr->second)
                    pr = S2.erase(pr);
                else
                    pr++;
            }
            inc(LP[p].first + 1), dec(RP[p].first);
        }
    }
    int ans = INT_MAX, tot = 0;
    auto pl = S1.begin(), pr = S2.begin();
    S1[L] += 0;
    while (pl != S1.end() || pr != S2.end()) {
        int pos = min(pl == S1.end() ? INT_MAX : pl->first, pr == S2.end() ? INT_MAX : pr->first);
        if (pl != S1.end() && pl->first == pos) tot += (pl++)->second;
        if (pr != S2.end() && pr->first == pos) tot += (pr++)->second;
        if (L <= pos && pos <= R) ans = min(ans, tot);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("rain.in", "r", stdin), freopen("rain.out", "w", stdout);
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