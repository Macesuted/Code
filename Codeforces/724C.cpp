/**
 * @file 724C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define mod 1'000'000'007

int a[maxn], dfn[maxn], low[maxn];
bool inStack[maxn];
stack<int> S;

vector<vector<int>> graph, SCC;

int tim = 0;
void tarjan(int p) {
    dfn[p] = low[p] = ++tim;
    S.push(p), inStack[p] = true;
    for (auto i : graph[p])
        if (!dfn[i])
            tarjan(i), low[p] = min(low[p], low[i]);
        else if (inStack[i])
            low[p] = min(low[p], dfn[i]);
    if (dfn[p] == low[p]) {
        SCC.push_back({});
        while (S.top() != p) SCC.back().push_back(S.top()), inStack[S.top()] = false, S.pop();
        SCC.back().push_back(p), inStack[p] = false, S.pop();
    }
    return;
}

void solve(void) {
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    long long answer = 0, way = 1;
    for (auto i : SCC) {
        int minVal = 0x3f3f3f3f, cnt = 0;
        for (auto j : i)
            if (a[j] < minVal)
                minVal = a[j], cnt = 1;
            else if (a[j] == minVal)
                cnt++;
        answer += minVal;
        way = way * cnt % mod;
    }
    cout << answer << ' ' << way << endl;
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << t2 - t1 << "ms" << endl;
    return 0;
}