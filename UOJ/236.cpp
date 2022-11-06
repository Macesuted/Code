/**
 * @file 236.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "railroad.h"

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

typedef tuple<int, int, int> tiii;

class UnionSet {
   private:
    int fa[maxn << 1];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

   public:
    void init(int n) {
        for (int i = 0; i < n; i++) fa[i] = i;
        return;
    }
    bool check(int x, int y) { return getfa(x) == getfa(y); }
    bool merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx == fy) return false;
        return fa[fx] = fy, true;
    }
};

UnionSet US;

int deg[maxn << 1], v[maxn << 1];
vector<tiii> edges;

long long plan_roller_coaster(vector<int> s, vector<int> t) {
    int n = (int)s.size();
    for (int i = 0; i < n; i++) v[i] = s[i], v[i + n] = t[i];
    int tn = (sort(v, v + 2 * n), unique(v, v + 2 * n)) - v;
    US.init(tn);
    deg[0]++, deg[tn - 1]--;
    for (int i = 0; i < n; i++)
        deg[s[i] = lower_bound(v, v + tn, s[i]) - v]--, deg[t[i] = lower_bound(v, v + tn, t[i]) - v]++, US.merge(s[i], t[i]);
    int64_t ans = 0;
    for (int i = 0; i < tn; i++)
        if (deg[i]) ans += max(0, -deg[i]) * int64_t(v[i + 1] - v[i]), deg[i + 1] += deg[i], deg[i] = 0, US.merge(i, i + 1);
    for (int i = 1; i < tn; i++)
        if (!US.check(i - 1, i)) edges.emplace_back(v[i] - v[i - 1], i - 1, i);
    sort(edges.begin(), edges.end());
    for (auto i : edges)
        if (US.merge(get<1>(i), get<2>(i))) ans += get<0>(i);
    return ans;
}
