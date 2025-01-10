/**
 * @file 105631F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

string a;
bool chk[27];
int cnt[27], len[27], nxt[27][27], jmp[27];

void dfs(int p) {
    if (jmp[p] >= 0)
        dfs(jmp[p]), len[p] = len[jmp[p]] + 1;
    else
        len[p] = (chk[p] ? 1 : -1);
    return;
}

void solve(void) {
    int n;
    cin >> n >> a, a = ' ' + a;
    for (int i = 1; i <= n; i++) cnt[a[i] - 'a']++;
    for (int i = 1; i < n; i++) nxt[a[i] - 'a'][a[i + 1] - 'a']++;

    int q;
    cin >> q;
    while (q--) {
        int pos;
        char c;
        cin >> pos >> c;

        cnt[a[pos] - 'a']--;
        if (pos > 1) nxt[a[pos - 1] - 'a'][a[pos] - 'a']--;
        if (pos < n) nxt[a[pos] - 'a'][a[pos + 1] - 'a']--;
        a[pos] = c;
        if (pos > 1) nxt[a[pos - 1] - 'a'][a[pos] - 'a']++;
        if (pos < n) nxt[a[pos] - 'a'][a[pos + 1] - 'a']++;
        cnt[a[pos] - 'a']++;

        int mx = 0;
        for (int i = 0; i < 26; i++) mx = max(mx, cnt[i]);
        for (int i = 0; i < 26; i++) {
            jmp[i] = -1;
            if (cnt[i] < mx || a[n] - 'a' == i) continue;
            for (int j = 0; j < 26; j++)
                if (nxt[i][j] > 0) {
                    if (jmp[i] == -1)
                        jmp[i] = j;
                    else
                        jmp[i] = -2;
                }
            if (jmp[i] >= 0 && cnt[jmp[i]] < mx) jmp[i] = -1;
        }
        for (int i = 0; i < 26; i++) chk[i] = (cnt[i] == mx), len[i] = 0;
        for (int i = 0; i < 26; i++)
            if (!len[i]) dfs(i);
        int ans = 0, mxlen = 0;
        for (int i = 0; i < 26; i++)
            if (len[i] > 0) ans += len[i], mxlen = max(mxlen, len[i]);
        cout << 3 * ans - mxlen << endl;
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