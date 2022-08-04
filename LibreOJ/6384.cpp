/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 10005
#define maxk 205

long long a[maxn], s[maxn], t[maxn];
int rec[maxn];
int n, k;

long long f[2][maxn];

inline long long cost(int l, int r) {
    return l * (s[r - 1] - s[l] - a[l] * (r - l - 1)) + 4 * (t[r - 1] - t[l]) - (s[r - 1] - s[l]) * (l + r) * 2 +
           (n - r + 1) * ((r - l - 1) * a[r] - (s[r - 1] - s[l]));
}

void update(bool thi, bool tha, int l, int r, int lastl, int lastr) {
    int mid = (l + r) >> 1, arg = 0;
    for (register int i = lastl; i <= lastr && i < mid; i++) {
        long long val = f[tha][i] + cost(i, mid);
        if (val < f[thi][mid]) f[thi][mid] = val, arg = i;
    }
    rec[mid] = arg;
    if (l < mid) update(thi, tha, l, mid - 1, lastl, arg);
    if (r > mid) update(thi, tha, mid + 1, r, arg, lastr);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> k) {
        for (register int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i - 1] + a[i], t[i] = t[i - 1] + i * a[i];
        memset(f[1], 0x3f, sizeof(f[1])), f[1][0] = 0;
        for (register int i = 0; i <= k; i++) {
            bool thi = i & 1, tha = !thi;
            memset(f[thi], 0x3f, sizeof(f[thi])), f[thi][0] = 0;
            update(thi, tha, 0, n + 1, 0, n + 1);
        }
        cout << f[k & 1][n + 1] << endl;
    }
    return 0;
}
