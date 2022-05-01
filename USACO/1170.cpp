/**
 * @file 1170.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

typedef pair<long long, int> pli;

long long solve2(long long x, long long y) {
    long long cnt = 0, ans = 0x3f3f3f3f3f3f3f3f;
    while (x <= y) {
        ans = min(ans, y - x + cnt);
        cnt++;
        if (y & 1)
            y--;
        else
            y >>= 1;
    }
    return ans;
}
long long solve1(long long x, long long y) {
    long long ans = 0x3f3f3f3f3f3f3f3f, cnt = 0;
    if (x == 1) ans = solve2(x, y);
    while (x > 1) {
        if (x <= y) ans = min(ans, cnt + solve2(x, y));
        cnt++;
        if (x & 1)
            x++;
        else
            x >>= 1;
    }
    return ans;
}

void solve(void) {
    long long a, b;
    cin >> a >> b;
    cout << solve1(a, b) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
