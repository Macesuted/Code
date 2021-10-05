/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 10005

typedef pair<int, int> pii;

int a[maxn];
int n;
bitset<2005> S, base;

bool check(int lim) {
    for (register int i = 0; i < lim; i++) S[i] = base[i] = true;
    for (register int i = lim; i < 2005; i++) S[i] = base[i] = false;
    for (register int i = 1; i <= n; i++) S = ((S << a[i]) | (S >> a[i])) & base;
    for (register int i = 0; i < lim; i++)
        if (S[i]) return true;
    return false;
}

void work(void) {
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    int l = 0, r = 2000;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(mid) ? r = mid : l = mid;
    }
    cout << r - 1 << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}