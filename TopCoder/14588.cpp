/**
 * @file 14588.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL

bool mem1;

#endif

#define Class DFSCount
#define Method count

#define maxn 14

class Class {
   private:
    int n, graph[maxn][maxn];
    int64_t f[1 << maxn][maxn];

    int getfa(int fa[], int p) { return fa[p] == p ? p : fa[p] = getfa(fa, fa[p]); }

    int64_t F(int S, int p) {
        if (~f[S][p]) return f[S][p];
        f[S][p] = 1;
        int fa[maxn];
        for (int i = 0; i < n; i++) fa[i] = i;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!(S >> i & 1) && !(S >> j & 1) && graph[i][j]) fa[getfa(fa, i)] = getfa(fa, j);
        map<int, int64_t> rec;
        for (int i = 0; i < n; i++)
            if (!(S >> i & 1) && graph[p][i]) {
                int T = (1 << n) - 1;
                for (int j = 0; j < n; j++)
                    if (getfa(fa, j) == getfa(fa, i)) T ^= 1 << j;
                rec[getfa(fa, i)] += F(T | (1 << i), i);
            }
        for (auto i : rec) f[S][p] *= i.second;
        for (int i = 1; i <= (int)rec.size(); i++) f[S][p] *= i;
        return f[S][p];
    }

   public:
    int64_t Method(vector<string> G) {
        n = G.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) graph[i][j] = (G[i][j] == 'Y');
        memset(f, 0xff, sizeof(f));
        int64_t ans = 0;
        for (int i = 0; i < n; i++) ans += F(1 << i, i);
        return ans;
    }
};

#ifdef LOCAL

Class _;

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    vector<string> G;
    G.resize(1);
    cin >> G[0];
    int n = G[0].size();
    G.resize(n);
    for (int i = 1; i < n; i++) cin >> G[i];

    cout << _.Method(G) << endl;

    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
    return 0;
}

#endif