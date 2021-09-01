/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[300005];

map<int, int> record;

signed main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= k; i++) record[a[i]]++;
    int answer = record.size();
    for (register int i = k + 1; i <= n; i++) {
        record[a[i]]++;
        if (!--record[a[i - k]]) record.erase(a[i - k]);
        answer = max(answer, (long long)record.size());
    }
    cout << answer << endl;
    return 0;
}