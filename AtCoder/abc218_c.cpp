/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 205

char a[maxn][maxn], b[maxn][maxn], x[maxn][maxn], y[maxn][maxn];

typedef pair<int, int> pii;

void roll(int n) {
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) b[n - j + 1][i] = a[i][j];
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) a[i][j] = b[i][j];
    return;
}
bool check(int n) {
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) x[i][j] = a[i][j];
    while (true) {
        bool check = true;
        for (register int i = 1; i <= n; i++)
            if (x[1][i] == '#') check = false;
        if (!check) break;
        for (register int i = 1; i < n; i++)
            for (register int j = 1; j <= n; j++) x[i][j] = x[i + 1][j];
        for (register int i = 1; i <= n; i++) x[n][i] = '.';
    }
    while (true) {
        bool check = true;
        for (register int i = 1; i <= n; i++)
            if (x[i][1] == '#') check = false;
        if (!check) break;
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j < n; j++) x[i][j] = x[i][j + 1];
        for (register int i = 1; i <= n; i++) x[i][n] = '.';
    }
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            if (x[i][j] != y[i][j]) return false;
    return true;
}

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) cin >> a[i][j];
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++) cin >> y[i][j];
    while (true) {
        bool check = true;
        for (register int i = 1; i <= n; i++)
            if (y[1][i] == '#') check = false;
        if (!check) break;
        for (register int i = 1; i < n; i++)
            for (register int j = 1; j <= n; j++) y[i][j] = y[i + 1][j];
        for (register int i = 1; i <= n; i++) y[n][i] = '.';
    }
    while (true) {
        bool check = true;
        for (register int i = 1; i <= n; i++)
            if (y[i][1] == '#') check = false;
        if (!check) break;
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j < n; j++) y[i][j] = y[i][j + 1];
        for (register int i = 1; i <= n; i++) y[i][n] = '.';
    }
    if (roll(n), check(n)) return cout << "Yes" << endl, void();
    if (roll(n), check(n)) return cout << "Yes" << endl, void();
    if (roll(n), check(n)) return cout << "Yes" << endl, void();
    if (roll(n), check(n)) return cout << "Yes" << endl, void();
    cout << "No" << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cout << setprecision(11);
    // cin >> _;
    while (_--) work();
    return 0;
}