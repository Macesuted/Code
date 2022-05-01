/**
 * @file 1621C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 10005

int a[maxn];

int ask(int p) {
    cout << "? " << p << endl;
    int t;
    cin >> t;
    return t;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) a[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i]) continue;
        int x = 0, last = i;
        while (x != i) x = ask(i);
        x = ask(i);
        while (x != i) a[last] = x, last = x, x = ask(i);
        a[last] = i;
    }
    cout << "!";
    for (int i = 1; i <= n; i++) cout << ' ' << a[i];
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
