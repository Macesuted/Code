/**
 * @file 102465B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int l[maxn], r[maxn];
multiset<int> Sl, Sr;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];

    int ans = 1;
    for (int i = 1, j = 0; i <= n; i++) {
        if (j < i) j++, Sl.insert(l[j]), Sr.insert(r[j]);
        int len = r[i] - l[i] + 1;
        while (j < n && j - i + 1 < len && min(*Sr.begin(), r[j + 1]) - max(*Sl.rbegin(), l[j + 1]) + 1 > j - i + 1)
            j++, Sl.insert(l[j]), Sr.insert(r[j]), ans = max(ans, j - i + 1);
        Sl.erase(Sl.find(l[i])), Sr.erase(Sr.find(r[i]));
    }
    cout << ans << endl;
    return 0;
}