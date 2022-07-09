/**
 * @file 1442F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1005

vector<int> graph[maxn];
int rk[maxn], indeg[maxn], pt[20], id[maxn], rec[1 << 20];

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), indeg[y]++;
    static queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    int cnt = 0, tn = min(n, 20);
    while (!que.empty()) {
        int p = rk[++cnt] = que.front();
        que.pop();
        for (auto i : graph[p])
            if (!--indeg[i]) que.push(i);
    }
    memset(id, 0xff, sizeof(id));
    for (int i = 0; i < tn; i++) id[pt[i] = rk[n - tn + i + 1]] = i;
    vector<string> ops;
    auto addEdge = [&](int x, int y) { return ops.push_back("+ " + to_string(x) + " " + to_string(y)); };
    auto delEdge = [&](int x, int y) { return ops.push_back("- " + to_string(x) + " " + to_string(y)); };
    for (int i = 0; i < tn; i++) {
        int S = 0;
        for (auto j : graph[pt[i]]) S |= 1 << id[j];
        for (int j = i + 1; j < tn; j++)
            if (!(S >> j & 1)) addEdge(pt[i], pt[j]);
    }
    for (int i = 1; i <= n; i++) {
        if (~id[i]) continue;
        addEdge(i, i);
        int S = 0;
        for (auto j : graph[i])
            if (~id[j]) S |= 1 << id[j];
        if (!rec[S]) {
            rec[S] = i;
            continue;
        }
        bool cont = true;
        for (int x1 = 0; x1 < tn && cont; x1++)
            for (int x2 = 0; x2 < tn && cont; x2++)
                for (int x3 = 0; x3 < tn && cont; x3++) {
                    if (x1 == x2 || x1 == x3 || x2 == x3) continue;
                    int T = S ^ (1 << x1) ^ (1 << x2) ^ (1 << x3);
                    if (rec[T]) continue;
                    rec[T] = i, cont = false;
                    (S >> x1 & 1) ? delEdge(i, pt[x1]) : addEdge(i, pt[x1]);
                    (S >> x2 & 1) ? delEdge(i, pt[x2]) : addEdge(i, pt[x2]);
                    (S >> x3 & 1) ? delEdge(i, pt[x3]) : addEdge(i, pt[x3]);
                    break;
                }
    }
    cout << ops.size() << endl;
    for (auto i : ops) cout << i << endl;
    while (q--) {
        auto ques = [](int x) {
            cout << "? 1 " << x << endl;
            string ret;
            cin >> ret;
            return ret;
        };
        int S = 0;
        bool fin = false;
        for (int i = 0; i < tn; i++) {
            string ret = ques(pt[i]);
            if (ret == "Lose") {
                cout << "! " << pt[i] << endl, fin = true;
                break;
            }
            S |= (ret == "Win") << i;
        }
        if (!fin) cout << "! " << rec[S] << endl;
        string ret;
        cin >> ret;
        assert(ret == "Correct");
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