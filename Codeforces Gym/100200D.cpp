/**
 * @file 100200D.cpp
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

#define maxn 105

int a[maxn][maxn], b[maxn], c[maxn], limb[maxn], limc[maxn];

void split(const string& s, int a[]) {
    if (s == "0") return;
    for (int r = (int)s.size() - 1, l; r >= 0; r = l - 1) {
        l = r;
        while (s[l] != 'x') l--;
        int p = l;
        while (l > 0 && '0' <= s[l - 1] && s[l - 1] <= '9') l--;
        int v = (p == l ? 1 : stoi(s.substr(l, p - l)));
        if (l > 0 && s[l - 1] == '+') l--;
        if (l > 0 && s[l - 1] == '-') v = -v, l--;
        a[stoi(s.substr(p + 1, r - p))] = v;
    }
    return;
}
string merge(int a[], int n) {
    stringstream ssin;
    bool emp = true;
    for (int i = 1; i <= n; i++) {
        if (!a[i]) continue;
        if (a[i] > 0 && !emp) ssin << '+';
        if (a[i] < 0) ssin << '-';
        if (abs(a[i]) > 1) ssin << abs(a[i]);
        ssin << 'y' << i;
        emp = false;
    }
    return emp ? "0" : ssin.str();
}

void solve(void) {
    int n, m;
    string s;
    cin >> n >> m >> s;
    bool type = (s == "min");

    cin >> s, split(s, c);

    cin >> s;  // with
    getline(cin, s);

    for (int i = 1; i <= n; i++) {
        getline(cin, s);
        if (s.back() == 'y') continue;
        int p = s.size() - 1;
        while (s[p] != '=') p--;
        limc[i] = (s[p - 1] == '<' ? -1 : +1);
    }

    cin >> s;  // under

    for (int i = 1; i <= m; i++) {
        cin >> s;
        int p = s.size() - 1;
        while (s[p] != '=') p--;
        b[i] = stoi(s.substr(p + 1));
        if (s[p - 1] == '<') limb[i] = -1, p--;
        if (s[p - 1] == '>') limb[i] = +1, p--;
        split(s.substr(0, p), a[i]);
    }

    for (int i = 1; i <= max(n, m); i++)
        for (int j = i + 1; j <= max(n, m); j++) swap(a[i][j], a[j][i]);

    cout << m << ' ' << n << endl;

    cout << (type ? "max" : "min") << ' ' << merge(b, m) << endl;

    cout << "with" << endl;

    for (int i = 1; i <= m; i++)
        cout << 'y' << i << (limb[i] ? (((limb[i] == +1) ^ type) ? "<=0" : ">=0") : " arbitary") << endl;

    cout << "under" << endl;

    for (int i = 1; i <= n; i++)
        cout << merge(a[i], m) << (limc[i] ? (((limc[i] == +1) ^ type) ? ">=" : "<=") : "=") << c[i] << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("dual.in", "r", stdin), freopen("dual.out", "w", stdout);
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