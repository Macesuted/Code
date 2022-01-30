/**
 * @file 1622C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    long long k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int minVal = 0x3f3f3f3f;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        minVal = min(minVal, a[i]);
    }
    priority_queue<int, vector<int>, less<int>> que;
    for (int i = 1; i <= n; i++) que.push(a[i]);
    long long ans = max(0LL, sum - k), csum = 0;
    int cnt = 0;
    while (que.size() > 1) {
        sum -= que.top() - minVal, cnt++, que.pop();
        ans = min(ans, cnt + max(0LL, (sum - k + cnt) / (cnt + 1)));
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
