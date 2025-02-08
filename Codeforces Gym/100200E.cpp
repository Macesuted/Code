/**
 * @file 100200E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-08
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

string name[maxn];

tuple<int, int, int> a[maxn];
int f[maxn][32][6], nxt[maxn][6];
tuple<int, int, int> pre[maxn][32][6];

void update(int x, int y, int z, int fx, int fy, int fz, int det) {
    if (f[x][y][z] < f[fx][fy][fz] + det) f[x][y][z] = f[fx][fy][fz] + det, pre[x][y][z] = {fx, fy, fz};
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c = cin.get();
        while (c != '"') c = cin.get();
        name[i] = '"';
        c = cin.get();
        while (c != '"') name[i].push_back(c), c = cin.get();
        name[i].push_back('"');

        cin >> get<0>(a[i]) >> get<1>(a[i]), get<1>(a[i])--, get<2>(a[i]) = i;
    }
    sort(a + 1, a + n + 1);

    for (int i = 0; i < 5; i++) nxt[n + 1][i] = n + 1;
    for (int i = n; i; i--) {
        for (int j = 0; j < 5; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][get<1>(a[i])] = i;
    }

    for (int i = 0; i < 5; i++) update(nxt[1][i], 1 << i, 0, 0, 0, 0, 1);

    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r < n && get<0>(a[l]) == get<0>(a[r + 1])) r++;

        for (int y = 1; y < 32; y++)
            for (int x = l; x <= r; x++)
                for (int z = 0; z <= 5; z++)
                    for (int c = 0; c < 5; c++) {
                        int tz = z + (get<1>(a[x]) != c);
                        if (tz > 5) continue;
                        if (y >> c & 1) {
                            if (get<1>(a[x]) == c && nxt[x + 1][c] <= r)
                                update(nxt[x + 1][c], y, tz, x, y, z, 1);
                            else
                                update(nxt[r + 1][c], 1 << c, tz, x, y, z, 1);
                        } else {
                            int tx = nxt[l][c];
                            if (tx <= r)
                                update(tx, y | (1 << c), tz, x, y, z, 1);
                            else
                                update(tx, 1 << c, tz, x, y, z, 1);
                        }
                    }
    }

    tuple<int, int, int> pos = {n + 1, 1, 0};
    for (int i = 1; i < 32; i++)
        for (int j = 0; j <= 5; j++)
            if (f[n + 1][i][j] > f[n + 1][get<1>(pos)][get<2>(pos)]) pos = {n + 1, i, j};

    vector<int> ans;
    while (get<0>(pos)) ans.push_back(get<0>(pos)), pos = pre[get<0>(pos)][get<1>(pos)][get<2>(pos)];

    reverse(ans.begin(), ans.end()), ans.pop_back();

    cout << ans.size() << endl;
    for (auto i : ans) cout << name[get<2>(a[i])] << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("dvd.in", "r", stdin), freopen("dvd.out", "w", stdout);
#endif
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