/**
 * @file 3843.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#include "tree.h"
#else

int query(vector<int> a) {
    for (auto i : a) cout << i << ' ';
    cout << endl;
    int t;
    cin >> t;
    return t;
}

#endif

#define maxn 1005

typedef pair<int, int> pii;

pii a[maxn];

int query(int l, int r) {
    vector<int> vec;
    for (int i = l; i <= r; i++) vec.push_back(a[i].second);
    return query(vec);
}

vector<int> solve(int n) {
    for (int i = 1; i <= n; i++) a[i] = {query(vector<int>(1, i)), i};
    sort(a + 1, a + n + 1, greater<pii>());
    vector<int> fa;
    fa.resize(n - 1);
    for (int i = 2; i <= n; i++) {
        int l = 1, r = i;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            query(mid, i - 1) == query(mid, i) ? l = mid : r = mid;
        }
        if (a[i].second != 1) fa[a[i].second - 2] = a[l].second;
    }
    return fa;
}

#ifdef LOCAL

int main() {
    int n;
    cin >> n;
    solve(n);
    return 0;
}

#endif