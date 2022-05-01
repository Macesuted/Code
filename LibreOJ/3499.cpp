/**
 * @file 3499.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
bool mem1;
#endif

template <typename T>
T read(void) {
    T f = +1, num = 0;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
    return f * num;
}
template <typename T>
void write(T num) {
    if (num == 0) return putchar('0'), void();
    if (num < 0) putchar('-'), num = -num;
    if (num > 9) write(num / 10);
    putchar((num % 10) ^ 48);
    return;
}

#define maxn 1000005

typedef pair<int, int> pii;

pii a[maxn * 2];
int cnt[maxn], cntn, use;

void add(int p) {
    int x = abs(a[p].second);
    if (!cnt[x]) cntn++;
    if (!cnt[x] && a[p].second < 0) use++;
    if (cnt[x] && a[p].second > 0) use--;
    cnt[x]++;
    return;
}
void del(int p) {
    int x = abs(a[p].second);
    cnt[x]--;
    if (!cnt[x]) cntn--;
    if (!cnt[x] && a[p].second < 0) use--;
    if (cnt[x] && a[p].second > 0) use++;
    return;
}

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) a[i] = {read<int>(), +i};
    for (int i = 1; i <= n; i++) a[n + i] = {read<int>(), -i};
    sort(a + 1, a + 2 * n + 1);
    cntn = 0, use = 0;
    int ans = numeric_limits<int>::max();
    for (int l = 1, r = 1; r <= 2 * n; del(l++)) {
        while (r <= 2 * n && (cntn < n || use > m)) add(r++);
        if (cntn < n || use > m) continue;
        ans = min(ans, a[r - 1].first - a[l].first);
    }
    write(ans), putchar('\n');
    return;
}

#ifdef LOCAL
bool mem2;
#endif

int main() {
#ifndef LOCAL
    // freopen("card.in", "r", stdin), freopen("card.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << " MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << " ms" << endl;
#endif

    return 0;
}