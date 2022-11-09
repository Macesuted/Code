/**
 * @file 102.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define maxsqrtn 500

int a[maxn], L[maxsqrtn], R[maxsqrtn], bel[maxn], cnt[2][maxsqrtn][maxsqrtn * 2], sum[maxsqrtn];
int64_t val[2][maxsqrtn][maxsqrtn * 2];
bool rev[maxsqrtn];

void build(int b) {
    memset(cnt[0][b], 0, sizeof(cnt[0][b])), memset(cnt[1][b], 0, sizeof(cnt[1][b]));
    if (rev[b])
        for (int i = L[b]; i <= R[b]; i++) a[i] = -a[i];
    rev[b] = false, sum[b] = 0;
    for (int i = L[b]; i <= R[b]; i++)
        sum[b] += a[i], (a[i] == +1) ? cnt[0][b][maxsqrtn + sum[b]]++ : cnt[1][b][maxsqrtn - sum[b]]++;
    for (int t = 0; t < 2; t++)
        for (int i = 1; i < 2 * maxsqrtn; i++)
            val[t][b][i] = val[t][b][i - 1] + 1LL * cnt[t][b][i] * (i - maxsqrtn), cnt[t][b][i] += cnt[t][b][i - 1];
    return;
}

void solve(void) {
    int n, q;
    string s;
    cin >> n >> q >> s;
    for (int i = 1; i <= n; i++) a[i] = (s[i - 1] == '(' ? +1 : -1);
    int len = sqrt(n), bcnt = n / len;
    for (int i = 1; i <= bcnt; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + len;
    if (R[bcnt] != n) L[bcnt + 1] = R[bcnt] + 1, R[++bcnt] = n;
    for (int i = 1; i <= bcnt; i++)
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
    for (int i = 1; i <= bcnt; i++) build(i);
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int bl = bel[l], br = bel[r];
            if (bl == br) {
                for (int i = l; i <= r; i++) a[i] = -a[i];
                build(bl);
                continue;
            }
            for (int i = l; i <= R[bl]; i++) a[i] = -a[i];
            for (int i = L[br]; i <= r; i++) a[i] = -a[i];
            build(bl), build(br);
            for (int i = bl + 1; i < br; i++) rev[i] ^= true, sum[i] = -sum[i];
        } else {
            int bl = bel[l], br = bel[r], tot = 0;
            int64_t ans = 0;
            if (bl == br) {
                build(bl);
                for (int i = l; i <= r; i++) tot += a[i];
                ans = abs(tot);
                for (int i = l, pre = -max(0, tot); i <= r; i++) {
                    pre += a[i];
                    if (a[i] == +1) ans += max(0, -pre + 1);
                }
                if (tot < 0) ans += -tot * (1LL - tot) / 2;
            } else {
                build(bl), build(br);
                for (int i = l; i <= R[bl]; i++) tot += a[i];
                for (int i = bl + 1; i < br; i++) tot += sum[i];
                for (int i = L[br]; i <= r; i++) tot += a[i];
                ans = abs(tot);
                int pre = -max(0, tot);
                for (int i = l; i <= R[bl]; i++) {
                    pre += a[i];
                    if (a[i] == +1) ans += max(0, -pre + 1);
                }
                for (int i = bl + 1; i < br; i++) {
                    if (maxsqrtn - pre + 1 > 0)
                        ans += -val[rev[i]][i][maxsqrtn + min(maxsqrtn - 1, -pre + 1)] +
                               cnt[rev[i]][i][maxsqrtn + min(maxsqrtn - 1, -pre + 1)] * (-pre + 1LL);
                    pre += sum[i];
                }
                for (int i = L[br]; i <= r; i++) {
                    pre += a[i];
                    if (a[i] == +1) ans += max(0, -pre + 1);
                }
                if (tot < 0) ans += -tot * (1LL - tot) / 2;
            }
            cout << ans << endl;
        }
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