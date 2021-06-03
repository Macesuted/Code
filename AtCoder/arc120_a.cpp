/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

int a[maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    long long answer = 0, maxx = 0, sum = 0;
    for (register int i = 1; i <= n; i++) {
        sum += a[i], maxx = max(maxx, 1LL * a[i]);
        answer += sum;
        cout << answer + maxx * i << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    while (_--) work();
    return 0;
}
