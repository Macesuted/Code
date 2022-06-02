/**
 * @file 2290.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 16
#define mod 1000000007

typedef tuple<int, int, int> tiii;

const int BASE = 1 << 20;

vector<tiii> edge[maxn];
unordered_map<int, int> F[BASE];
int n, m;
int xxxx = -1;

int Mod(int x) { return x >= mod ? x - mod : x; }

int getF(int S, int T) {
    int x = S << n | T;
    S = x & (BASE - 1), T = x - S;
    auto p = F[S].find(T);
    if (p == F[S].end()) return -1;
    return p->second;
}
int &getFF(int S, int T) {
    int x = S << n | T;
    S = x & (BASE - 1), T = x - S;
    return F[S][T];
}

int f(int S, int T) {
    if (S == (1 << n) - 1 && T == (1 << n) - 1) return 1;
    if (~getF(S, T)) return getF(S, T);
    int t = 0, p = log2((~S) & -(~S));
    for (auto i : edge[p])
        if (!(S & get<0>(i)) && !(T & get<1>(i))) t = Mod(t + Mod(mod + f(S | get<0>(i), T | get<1>(i)) * get<2>(i)));
    return getFF(S, T) = t;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1, op, a1, b1, a2, b2; i <= m; i++) {
        cin >> op >> a1 >> b1, a1--, b1--;
        if (op == 0)
            edge[a1].emplace_back(1 << a1, 1 << b1, 1);
        else {
            cin >> a2 >> b2, a2--, b2--;
            edge[a1].emplace_back(1 << a1, 1 << b1, 1), edge[a2].emplace_back(1 << a2, 1 << b2, 1);
            if (a1 != a2) edge[min(a1, a2)].emplace_back((1 << a1) | (1 << a2), (1 << b1) | (1 << b2), op == 1 ? 1 : -1);
        }
    }
    cout << f(0, 0) << endl;
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