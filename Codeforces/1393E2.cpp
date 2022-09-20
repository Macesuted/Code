/**
 * @file 1393E2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-20
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
#define maxl 1000005
#define mod 1000000007

const int INF = 0x7f7f7f7f;

string a[maxn];
vector<int> pos[maxn], f[maxn];
int difl[maxl], difc[maxl], difr[maxl];

string *A, *B;
bool cmp(int x, int y) {
    if (difc[0] < min(x, y)) return (*A)[difc[0]] < (*B)[difc[0]];
    if (x < y && difl[x + 1] <= y) return (*A)[difl[x + 1]] < (*B)[difl[x + 1] - 1];
    if (x > y && difr[y] < x) return (*A)[difr[y]] < (*B)[difr[y] + 1];
    int p = difc[max(x, y) + 1];
    return p == INF ? (A->size() - (x != (int)A->size()) < B->size() - (y != (int)B->size())) : ((*A)[p] < (*B)[p]);
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(difl, 0x7f, sizeof(difl)), memset(difc, 0x7f, sizeof(difc)), memset(difr, 0x7f, sizeof(difr));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= (int)a[i].size(); j++) pos[i].push_back(j);
        for (int j = (int)a[i].size() - 1, p = INF; j; j--) {
            if (a[i][j] != a[i][j - 1]) p = j;
            difl[j] = p;
        }
        for (int j = (int)a[i].size() - 1; ~j; j--) difc[j] = INF;
        for (int j = (int)a[i].size() - 2, p = INF; ~j; j--) {
            if (a[i][j] != a[i][j + 1]) p = j;
            difr[j] = p;
        }
        A = B = &a[i], sort(pos[i].begin(), pos[i].end(), cmp);
        for (int j = (int)a[i].size() - 1; j; j--) difl[j] = INF;
        for (int j = (int)a[i].size() - 1; ~j; j--) difc[j] = INF;
        for (int j = (int)a[i].size() - 2; ~j; j--) difr[j] = INF;
    }
    f[1].resize(pos[1].size());
    for (int i = 0; i <= (int)a[1].size(); i++) f[1][i] = 1;
    for (int i = 1; i < n; i++) {
        f[i + 1].resize(pos[i + 1].size());
        for (int j = min(a[i + 1].size() - 1, a[i].size()), p = INF; j; j--) {
            if (a[i + 1][j] != a[i][j - 1]) p = j;
            difl[j] = p;
        }
        for (int j = min(a[i + 1].size() - 1, a[i].size() - 1), p = INF; ~j; j--) {
            if (a[i + 1][j] != a[i][j]) p = j;
            difc[j] = p;
        }
        for (int j = min(a[i + 1].size() - 1, a[i].size() - 2), p = INF; ~j; j--) {
            if (a[i + 1][j] != a[i][j + 1]) p = j;
            difr[j] = p;
        }
        A = &a[i + 1], B = &a[i];
        for (int j = 0, k = 0; j <= (int)a[i].size(); j++) {
            while (k <= (int)a[i + 1].size() && cmp(pos[i + 1][k], pos[i][j])) k++;
            if (k <= (int)a[i + 1].size()) f[i + 1][k] = (f[i + 1][k] + f[i][j]) % mod;
        }
        for (int j = 1; j <= (int)a[i + 1].size(); j++) f[i + 1][j] = (f[i + 1][j] + f[i + 1][j - 1]) % mod;
        for (int j = min(a[i + 1].size() - 1, a[i].size()); j; j--) difl[j] = INF;
        for (int j = min(a[i + 1].size() - 1, a[i].size() - 1); ~j; j--) difc[j] = INF;
        for (int j = min(a[i + 1].size() - 1, a[i].size() - 2); ~j; j--) difr[j] = INF;
    }
    int sum = 0;
    for (int i = 0; i <= (int)a[n].size(); i++) sum = (sum + f[n][i]) % mod;
    cout << sum << endl;
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