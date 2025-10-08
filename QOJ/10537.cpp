/**
 * @file 10537.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-07
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

#define maxn 2005

struct ST {
    int16_t a[4];
    int siz = 0;

    bool find(int16_t v) { return count(a, a + siz, v); }
    void add(int16_t v) { return !v || find(v) || siz == 4 ? 0 : a[siz++] = v, void(); }
    void add(const ST& o) {
        for (int i = 0; i < o.siz; i++) add(o.a[i]);
        return;
    }
};

int a[maxn][maxn];
ST NW[maxn][maxn], NE[maxn][maxn], SW[maxn][maxn], SE[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            NW[i][j].add(a[i][j]), NE[i][j].add(a[i][j]), SW[i][j].add(a[i][j]), SE[i][j].add(a[i][j]);
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) NW[i][j].add(NW[i - 1][j]), NW[i][j].add(NW[i][j - 1]);

    for (int i = 1; i <= n; i++)
        for (int j = n; j >= 1; j--) NE[i][j].add(NE[i - 1][j]), NE[i][j].add(NE[i][j + 1]);

    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= n; j++) SW[i][j].add(SW[i + 1][j]), SW[i][j].add(SW[i][j - 1]);

    for (int i = n; i >= 1; i--)
        for (int j = n; j >= 1; j--) SE[i][j].add(SE[i + 1][j]), SE[i][j].add(SE[i][j + 1]);

    int ans = 0;
    for (int i = 2; i < n; i++)
        for (int j = 2; j < n; j++) {
            if (a[i][j]) continue;

            array<ST, 4> rec = {NW[i - 1][j - 1], NE[i - 1][j + 1], SW[i + 1][j - 1], SE[i + 1][j + 1]};

            sort(rec.begin(), rec.end(), [](const ST& a, const ST& b) -> bool { return a.siz < b.siz; });

            bool brk = false;
            for (int id1 = 0; id1 < rec[0].siz && !brk; id1++) {
                int i1 = rec[0].a[id1];
                for (int id2 = 0; id2 < rec[1].siz && !brk; id2++) {
                    int i2 = rec[1].a[id2];
                    if (i1 != i2)
                        for (int id3 = 0; id3 < rec[2].siz && !brk; id3++) {
                            int i3 = rec[2].a[id3];
                            if (i1 != i3 && i2 != i3)
                                for (int id4 = 0; id4 < rec[3].siz && !brk; id4++) {
                                    int i4 = rec[3].a[id4];
                                    if (i1 != i4 && i2 != i4 && i3 != i4) ans++, brk = true;
                                }
                        }
                }
            }
        }

    cout << ans << endl;

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
    return 0