/**
 * @file 1023D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

int a[maxn], l[maxn], r[maxn], c[maxn];

set<int> pos;
int n, q;

void work(int p) {
    if (l[p] == n + 1 && r[p] == 1) return;
    static vector<int> cache;
    cache.clear();
    for (auto i = pos.lower_bound(l[p]); i != pos.end() && *i <= r[p]; i++) c[*i] = p, cache.push_back(*i);
    for (auto i : cache) pos.erase(i);
    auto x = pos.lower_bound(r[p]);
    while (x != pos.end() && c[*x] == 0) c[*x] = p, pos.erase(x), x = pos.lower_bound(r[p]);
    x = pos.lower_bound(l[p]);
    while (x != pos.begin() && c[*(--x)] == 0) c[*x] = p, pos.erase(x), x = pos.lower_bound(l[p]);
    return;
}

void solve(void) {
    cin >> n >> q;
    for (int i = 1; i <= q; i++) l[i] = n + 1, r[i] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], c[i] = a[i];
        l[a[i]] = min(l[a[i]], i), r[a[i]] = max(r[a[i]], i);
        pos.insert(i);
    }
    if (l[q] == n + 1 && r[q] == 1) {
        int p = 0, cnt = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] == 0) p = i, cnt++;
        if (p == 0) return cout << "NO" << endl, void();
        if (cnt == n) {
            cout << "YES" << endl;
            for (int i = 1; i <= n; i++) cout << q << ' ';
            cout << endl;
            return;
        }
        c[p] = q, pos.erase(p);
    } else
        work(q);
    for (int i = q - 1; i; i--) work(i);
    for (int i = 1; i <= n; i++)
        if (c[i] == 0 || (a[i] != 0 && c[i] != a[i]))
            return cout << "NO" << endl, void();
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) cout << c[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
