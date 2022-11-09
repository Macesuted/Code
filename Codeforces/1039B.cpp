/**
 * @file 1039B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

bool query(int64_t l, int64_t r) {
    cout << l << ' ' << r << endl;
    string s;
    cin >> s;
    return s == "Yes";
}

void solve(void) {
    int64_t n;
    int k;
    cin >> n >> k;
    int64_t l = 1, r = n;
    mt19937 rnd(114514);
    while (true) {
        if (r - l + 1 <= 60) {
            int64_t p = rnd() % (r - l + 1) + l;
            if (query(p, p)) return;
            l = max((int64_t)1, l - k), r = min(n, r + k);
        }
        int64_t mid = (l + r) >> 1;
        if (query(l, mid)) {
            if (l == mid) return;
            r = mid;
        } else
            l = mid + 1;
        l = max((int64_t)1, l - k), r = min(n, r + k);
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}