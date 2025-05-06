/**
 * @file 108199A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005
#define maxl 105

using tiii = tuple<int, int, int>;

bool mem1;

pair<char*, int> s[maxn];
int pos[maxn], tans[maxn];

bool mem2;

void solve(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        s[i].first = (char*)malloc(sizeof(char) * maxl);
        scanf("%s", s[i].first);
        s[i].second = i;
    }
    sort(s + 1, s + n + 1, [&](const auto& x, const auto& y) {
        int p = 0;
        while (x.first[p] == y.first[p]) p++;
        return x.first[p] < y.first[p];
    });
    for (int i = 1; i <= n; i++) pos[s[i].second] = i;

    set<tiii> S;
    int64_t ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && s[l].first[0] == s[r + 1].first[0]) r++;
        ans++, S.emplace(l, r, 0);
    }

    for (int i = n; i; i--) {
        tans[i] = ans;

        int p = pos[i];

        auto it = --S.lower_bound({p + 1, 0, 0});
        auto [l, r, d] = *it;
        ans--, S.erase(it);

        for (int td = d + 1; l < p; td++)
            for (int r; s[l].first[td] != s[p].first[td]; l = r + 1) {
                r = l;
                while (r + 1 < p && s[l].first[td] == s[r + 1].first[td]) r++;
                ans++, S.emplace(l, r, td);
            }
        for (int td = d + 1; p < r; td++)
            for (int l; s[r].first[td] != s[p].first[td]; r = l - 1) {
                l = r;
                while (p < l - 1 && s[l - 1].first[td] == s[r].first[td]) l--;
                ans++, S.emplace(l, r, td);
            }
    }

    for (int i = 1; i <= n; i++) printf("%d\n", tans[i]);

    return;
}

int main() {
    int _ = 1;
    while (_--) solve();

    return 0;
}