/**
 * @file 6817.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define maxr 55

typedef pair<int, int> pii;

string s[maxn];
int a[maxr][maxr], n, m, r, c;

pii getPos(pii x, int v) { return {n - (r - x.first) * 2 - v * 3, 1 + (x.second - 1) * 4 + (r - x.first) * 2}; }

void solve(void) {
    cin >> n >> m, c = -1;
    getline(cin, s[0]);
    for (int i = 1; i <= n; i++) getline(cin, s[i]), s[i] = " " + s[i];
    for (auto j : s[n]) c += (j == '+');
    r = (m - 4 * c - 1) / 2;
    for (int i = r; i; i--)
        for (int j = c; j; j--) {
            pii x = getPos({i, j}, a[i][j] = max(a[i + 1][j], a[i][j + 1]));
            while (x.first - 3 >= 1 && x.second + 4 <= m && s[x.first - 3][x.second] == '+' &&
                   s[x.first - 3][x.second + 4] == '+' && s[x.first - 2][x.second] == '|' &&
                   s[x.first - 2][x.second + 4] == '|' && s[x.first - 1][x.second] == '|' &&
                   s[x.first - 1][x.second + 4] == '|')
                a[i][j]++, x.first -= 3;
        }
    int sum = 0;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) sum += a[i][j];
    cout << sum << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
