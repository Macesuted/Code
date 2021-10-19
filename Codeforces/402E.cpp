/**
 * @file 402E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 2005

int dfn[maxn], low[maxn];
bool inStack[maxn];
stack<int> S;

vector<vector<int>> graph;
int cnt = 0;

int tim = 0;
void tarjan(int p) {
    dfn[p] = low[p] = ++tim;
    S.push(p), inStack[p] = true;
    for (auto i : graph[p])
        if (!dfn[i])
            tarjan(i), low[p] = min(low[p], low[i]);
        else if (inStack[i])
            low[p] = min(low[p], dfn[i]);
    if (low[p] == dfn[p]) {
        cnt++;
        while (S.top() != p) inStack[S.top()] = false, S.pop();
        inStack[p] = false, S.pop();
    }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.resize(n + 1);
    for (int i = 1, t; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> t;
            if (t) graph[i].push_back(j);
        }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    cout << (cnt == 1 ? "YES" : "NO") << endl;
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