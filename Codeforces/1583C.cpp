#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 1000005

typedef pair<int, int> pii;

string a[maxn];
set<int> S;

void solve(void) {
    int n, m;
    cin >> n >> m;
    S.clear();
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = ' ' + a[i];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (a[i][j + 1] == 'X' && a[i + 1][j] == 'X') S.insert(j);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        auto x = S.lower_bound(l);
        if (x != S.end() && *x < r)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    return;
}

bool mem2;

signed main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    while (_--) solve();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}