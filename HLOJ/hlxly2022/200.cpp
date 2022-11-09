/**
 * @file 200.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-21
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

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int64_t ans = 0;

int64_t P2(int64_t a) { return a * (a - 1) / 2; }

class UnionSet {
   private:
    int fa[maxn], siz[maxn];
    stack<pii> S;

   public:
    vector<int> vec[maxn];

    int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
    void build(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1, vec[i].push_back(i);
        return;
    }
    tiii merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return S.emplace(-1, -1), tiii{-1, -1, -1};
        if (siz[fx] > siz[fy]) swap(fx, fy);
        ans = ans - P2(siz[fx]) - P2(siz[fy]) + P2(siz[fx] + siz[fy]);
        fa[fx] = fy, siz[fy] += siz[fx];
        for (auto i : vec[fx]) vec[fy].push_back(i);
        return S.emplace(fx, fy), tiii{fx, fx, fy};
    }
    tiii undo(void) {
        int x, y;
        tie(x, y) = S.top(), S.pop();
        if (pii{x, y} == pii{-1, -1}) return {-1, -1, -1};
        fa[x] = x, siz[y] -= siz[x];
        ans = ans - P2(siz[x] + siz[y]) + P2(siz[x]) + P2(siz[y]);
        for (int i = 0; i < (int)vec[x].size(); i++) vec[y].pop_back();
        return {x, y, x};
    }
} SA, SB;

vector<tiii> GA, GB;
map<pii, int> SAB;
pii v[maxn];

void solve(void) {
    int n, A, B;
    int64_t K;
    cin >> n >> A >> B >> K;
    for (int i = 1, x, y, w; i <= A; i++) cin >> x >> y >> w, GA.emplace_back(w, x, y);
    for (int i = 1, x, y, w; i <= B; i++) cin >> x >> y >> w, GB.emplace_back(w, x, y);
    sort(GA.begin(), GA.end()), sort(GB.begin(), GB.end()), SA.build(n), SB.build(n);
    for (int i = 0; i < B; i++) SB.merge(get<1>(GB[i]), get<2>(GB[i]));
    for (int i = 1; i <= n; i++) ans -= SAB[v[i] = {i, SB.getfa(i)}]++;
    int answer = INT_MAX;
    for (int i = -1, j = B - 1; i < A; i++) {
        if (~i) {
            tiii ret = SA.merge(get<1>(GA[i]), get<2>(GA[i]));
            if (get<1>(ret) != get<2>(ret)) {
                for (auto i : SA.vec[get<0>(ret)]) ans += --SAB[v[i]];
                for (auto i : SA.vec[get<0>(ret)]) v[i].first = get<2>(ret), ans -= SAB[v[i]]++;
            }
        }
        while (j >= -1 && ans >= K)
            if (--j >= -1) {
                tiii ret = SB.undo();
                if (get<1>(ret) != get<2>(ret)) {
                    for (auto i : SB.vec[get<0>(ret)]) ans += --SAB[v[i]];
                    for (auto i : SB.vec[get<0>(ret)]) v[i].second = get<2>(ret), ans -= SAB[v[i]]++;
                }
            }
        if (j != B - 1) answer = min(answer, (~i ? get<0>(GA[i]) : 0) + (j == -2 ? 0 : get<0>(GB[j + 1])));
    }
    cout << (answer == INT_MAX ? -1 : answer) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("graph.in", "r", stdin), freopen("graph.out", "w", stdout);
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