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

typedef tuple<int, int, int, int> tiiii;

vector<int> edge1[maxn];
vector<tiiii> edge2[maxn];
unordered_map<int, int> F[1 << maxn];
int n, m;

int f(int S, int T) {
    if (S == (1 << n) - 1 && T == (1 << n) - 1) return 1;
    if (F[S].count(T)) return F[S][T];
    int& t = F[S][T];
    int p = 0;
    while (S >> p & 1) p++;
    for (auto i : edge1[p])
        if (!(T >> i & 1)) t = (t + f(S | (1 << p), T | (1 << i))) % mod;
    for (auto i : edge2[p])
        if (!(T >> get<0>(i) & 1) && !(S >> get<1>(i) & 1) && !(T >> get<2>(i) & 1))
            t = (t + 1LL * f(S | (1 << p) | (1 << get<1>(i)), T | (1 << get<0>(i)) | (1 << get<2>(i))) * get<3>(i)) % mod;
    return t;
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1, op, a1, b1, a2, b2; i <= m; i++) {
        cin >> op;
        if (op == 0)
            cin >> a1 >> b1, a1--, b1--, edge1[a1].push_back(b1);
        else {
            cin >> a1 >> b1 >> a2 >> b2, a1--, b1--, a2--, b2--;
            edge1[a1].push_back(b1), edge1[a2].push_back(b2);
            if (a1 != a2) edge2[min(a1, a2)].emplace_back(b1, max(a1, a2), b2, op == 1 ? 1 : mod - 1);
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