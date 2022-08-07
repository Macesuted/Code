/**
 * @file 751.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "tree.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 131105

typedef pair<int, int> pii;

int S[maxn], fa[maxn], indeg[maxn];
vector<int> bel[maxn], siz;
vector<vector<int>> V;
queue<int> que;

vector<pii> solve(int n) {
    int lim = (n <= 2000 ? 14 : 20);
    for (int i = 0, x = 0; i < n - 1; i++, x++) {
        while (__builtin_popcount(x) != lim / 2) x++;
        S[i] = x;
    }
    for (int i = 0; i < lim; i++) {
        vector<int> ques;
        for (int j = 0; j < n - 1; j++) ques.emplace_back(S[j] >> i & 1);
        auto ret = query(ques);
        for (auto x : ret) {
            for (auto p : x) bel[p].push_back(V.size());
            siz.push_back(x.size()), V.push_back(x);
        }
    }
    for (int i = 0; i < n; i++)
        for (auto j : bel[i]) indeg[i] += (siz[j] > 1);
    for (int i = 0; i < n; i++)
        if (indeg[i] == lim / 2) que.push(i);
    memset(fa, 0xff, sizeof(fa));
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto i : bel[p]) {
            if (siz[i] == 1)
                for (auto j : V[i])
                    if (j != p) {
                        int cnt = 0;
                        for (auto x : bel[j])
                            for (auto y : bel[p]) cnt += (x == y);
                        if (cnt == lim / 2) fa[j] = p;
                    }
            if (--siz[i] == 1)
                for (auto j : V[i])
                    if (j != p && --indeg[j] == lim / 2) que.push(j);
        }
    }
    vector<pii> ans;
    for (int i = 0; i < n; i++)
        if (fa[i] != -1) ans.emplace_back(i, fa[i]);
    return ans;
}