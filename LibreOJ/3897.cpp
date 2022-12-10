/**
 * @file 3897.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#ifndef LOCAL
#define endl '\n'
#endif

#define maxn 305
#define maxm 2000005
#define maxk 605

typedef tuple<int, int, int> tiii;

int siz[maxn], a[maxm], pos[maxk], num[maxn];
queue<int> avai;
set<int> S;
vector<tiii> ops;

void solve(void) {
    int n, m, k, emp;
    cin >> n >> m >> k, emp = n;
    ops.clear();
    while (!avai.empty()) avai.pop();
    for (int i = 1; i <= n; i++) siz[i] = 0;
    for (int i = 1; i < n; i++) avai.push(i);
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= k; i++) pos[i] = 0;
    for (int i = 1; i <= m; i++) {
        if (pos[a[i]]) {
            int p = abs(pos[a[i]]);
            if (siz[p]-- == 2) avai.push(p);
            if (pos[a[i]] < 0)
                ops.emplace_back(1, p, 1);
            else {
                ops.emplace_back(1, emp, 0), ops.emplace_back(2, p, emp);
                if (siz[p] == 1) pos[num[p]] = p;
            }
            pos[a[i]] = 0;
        } else if (!avai.empty()) {
            int p = avai.front();
            ops.emplace_back(1, p, 0);
            if (++siz[p] == 2)
                avai.pop(), pos[a[i]] = -p, num[p] = a[i];
            else
                pos[a[i]] = p;
        } else {
            int j;
            for (j = i + 1; j <= m; j++)
                if (pos[a[j]] == 0) {
                    ops.emplace_back(1, emp, -2);
                    for (int k = i + 1; k < j; k++) ops.emplace_back(1, -pos[a[k]], -1);
                    ops.emplace_back(1, emp, 3);
                    break;
                } else if (pos[a[j]] > 0) {
                    int p = pos[a[j]];
                    bool vis = false;
                    for (int k = i + 1; k < j && !vis; k++)
                        if (pos[a[k]] == -p) vis = true;
                    if (vis) {
                        ops.emplace_back(1, emp, -2), siz[emp] = 2, pos[a[i]] = emp;
                        for (int k = i + 1; k < j; k++) {
                            ops.emplace_back(1, -pos[a[k]], -1);
                            if (pos[a[k]] == -p) pos[a[k]] = -emp, num[emp] = a[k];
                        }
                        ops.emplace_back(1, p, 4);
                        siz[emp = p] = 0;
                    } else {
                        ops.emplace_back(1, p, -2);
                        pos[a[i]] = -p, pos[num[p]] = p, num[p] = a[i];
                        for (int k = i + 1; k < j; k++) ops.emplace_back(1, -pos[a[k]], -1);
                        ops.emplace_back(1, emp, 5), ops.emplace_back(2, emp, p);
                    }
                    pos[a[j]] = 0;
                    break;
                } else if (S.count(a[j]))
                    S.erase(a[j]);
                else
                    S.insert(a[j]);
            if (j == m + 1) {
                ops.emplace_back(1, emp, -2);
                for (int k = i + 1; k <= m; k++) ops.emplace_back(1, -pos[a[k]], -1);
            }
            for (auto i : S) siz[-pos[i]]--, avai.push(-pos[i]), pos[i] = 0;
            S.clear();
            i = j;
        }
    }
    cout << ops.size() << endl;
    for (auto i : ops)
        if (get<0>(i) == 1)
            cout << "1 " << get<1>(i) << endl;
        else
            cout << "2 " << get<1>(i) << ' ' << get<2>(i) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef LOCAL
    freopen("meow.in", "r", stdin), freopen("meow.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "MEMORY: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "TIME: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}