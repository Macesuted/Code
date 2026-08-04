/**
 * @file 2254G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-08-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int a[maxn], dep[maxn], fa[maxn];
multiset<int>* S[maxn];
vector<vector<int>> child;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    child.clear(), child.resize(n + 1);
    for (int i = 2; i <= n; i++) cin >> fa[i], dep[i] = dep[fa[i]] + 1, child[fa[i]].push_back(i);

    vector<int> p;
    for (int i = 1; i <= n; i++) p.push_back(i);
    sort(p.begin(), p.end(), [&](int x, int y) -> bool { return dep[x] > dep[y]; });

    int64_t ans = 0;
    for (auto x : p) {
        if (child[x].empty()) {
            S[x] = new multiset<int>();
            S[x]->insert(a[x]), ans += a[x];
        } else {
            int ty = child[x][0];
            for (auto y : child[x])
                if (S[y]->size() > S[ty]->size()) ty = y;
            S[x] = S[ty], S[ty] = nullptr;
            for (auto y : child[x])
                if (y != ty) {
                    for (auto v : *S[y]) S[x]->insert(v);
                    delete S[y], S[y] = nullptr;
                }

            if (a[x] > *S[x]->begin()) {
                S[x]->insert(a[x]), ans += a[x];
                ans -= *S[x]->begin(), S[x]->erase(S[x]->begin());
            }
        }
    }

    int siz = S[1]->size();

    vector<int> rest;
    for (int i = 1; i <= n; i++)
        if (S[1]->find(a[i]) != S[1]->end())
            S[1]->erase(S[1]->find(a[i]));
        else
            rest.push_back(a[i]);

    sort(rest.begin(), rest.end());

    delete S[1];

    for (int i = 1; i <= n; i++) {
        if (i < siz)
            cout << -1 << ' ';
        else {
            if (i > siz) ans += rest.back(), rest.pop_back();
            cout << ans << ' ';
        }
    }

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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
