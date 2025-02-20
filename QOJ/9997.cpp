/**
 * @file 9997.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

int a[maxn], pos[maxn];

vector<int> graph[maxn], son[maxn];
string ans[maxn];
int dep[maxn], conn[maxn];

void dfs(int p) {
    for (auto i : graph[p]) dfs(i);

    vector<tuple<int, int, int>> rec;

    int d = 0, lst = 0;
    for (vector<int>::iterator l = son[p].begin(), r, c = graph[p].begin(); l != son[p].end(); l = r + 1) {
        r = l;
        while (r + 1 != son[p].end() && *(r + 1) == *r - 1 && a[*(r + 1)] == a[*r] + 1) r++;
        while (c != graph[p].end() && *c > *r) d = max(d, dep[*(c++)]);
        if (l != r) {
            if (l != son[p].begin()) rec.emplace_back(lst, l - son[p].begin(), d);
            for (auto i = l + 1; i <= r; i++) ans[*i] = "*";
            lst = r - son[p].begin(), d = 0;
        }
    }
    rec.emplace_back(lst, son[p].size() - 1, d);

    for (int x = 0; x < (int)rec.size(); x++) {
        int l = get<0>(rec[x]), r = get<1>(rec[x]), d = get<2>(rec[x]);
        if (l == r) continue;
        dep[p] = max(dep[p], ++d);
        for (int i = l; i <= r; i++)
            if (i > l) {
                ans[son[p][i]] = to_string(d) + "-" + to_string(i - l + 1) + ans[son[p][i]];
                for (int j = 0; j < conn[son[p][i]] - 1; j++) ans[son[p][i] + j].push_back('#');
            } else
                ans[son[p][i] + conn[son[p][i]] - 1] = to_string(d) + "-1" + ans[son[p][i]];
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i, conn[i] = 1;
    vector<int> rec;

    for (int i = n - 1; i; i--)
        if (a[i] + 1 == a[i + 1]) conn[i] += conn[i + 1];

    for (int l = 1, r; l <= n; l = r + conn[pos[r]]) {
        r = l;
        son[pos[l]].push_back(pos[l]);
        while (r + conn[pos[r]] <= n && pos[r + conn[pos[r]]] < pos[r]) son[pos[l]].push_back(pos[r += conn[pos[r]]]);
        while (!rec.empty() && son[rec.back()].back() > pos[r]) graph[pos[l]].push_back(rec.back()), rec.pop_back();
        if (!rec.empty() && rec.back() > pos[r]) return cout << -1 << endl, void();
        rec.push_back(pos[l]);
    }

    for (auto i : rec) dfs(i);

    for (int i = 1; i <= n; i++) cout << '.' << ans[i];
    cout << endl;

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