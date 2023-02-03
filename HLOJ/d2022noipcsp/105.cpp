/**
 * @file 105.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef __int128_t int128_t;
typedef pair<int, int> pii;

vector<vector<int>> graph;
bitset<maxn> S[205], T;
int id[maxn], num[maxn];
bool large[maxn];

int128_t C3(int128_t n) { return n * (n - 1) * (n - 2) / 6; }
int128_t calc(int x, int y, int z) {
    int128_t ans = 0;
    if (x > 3) ans += z * C3(x - 2) + (y - 1 - z) * C3(x - 1);
    if (y > 3) ans += z * C3(y - 2) + (x - 1 - z) * C3(y - 1);
    return ans;
}
ostream& operator<<(ostream& o, int128_t a) {
    if (!a) return o.put('0'), o;
    if (a < 0) o.put('-'), a = -a;
    char s[40];
    int p = 0;
    while (a) s[p++] = '0' + (a % 10), a /= 10;
    while (p) o.put(s[--p]);
    return o;
}

void solve(void) {
    int n, m;
    cin >> n >> m, graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) id[i] = i, sort(graph[i].begin(), graph[i].end());
    sort(id + 1, id + n + 1, [&](int x, int y) { return graph[x].size() > graph[y].size(); });
    int B = min(n, 200);
    for (int i = 1; i <= B; i++) {
        large[id[i]] = true, num[id[i]] = i;
        for (auto j : graph[id[i]]) S[i].set(j);
    }
    int128_t ans = 0;
    for (int i = 1; i <= n; i++) {
        if (large[i]) continue;
        for (auto j : graph[i]) T[j] = true;
        for (auto j : graph[i]) {
            if (!large[j] && j < i) continue;
            int cnt = 0;
            if (large[j])
                for (auto x : graph[i]) cnt += S[num[j]][x];
            else
                for (auto x : graph[j]) cnt += T[x];
            ans += calc(graph[i].size(), graph[j].size(), cnt);
        }
        for (auto j : graph[i]) T[j] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (!large[i]) continue;
        for (auto j : graph[i])
            if (large[j] && i < j) ans += calc(graph[i].size(), graph[j].size(), (S[num[i]] & S[num[j]]).count());
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("counting.in", "r", stdin), freopen("counting.out", "w", stdout);
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