/**
 * @file 1023B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

#define maxn 200005

int a[maxn], f[maxn], ban[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        while (c != '(' && c != ')') cin >> c;
        a[i] = (c == ')');
    }
    static stack<int> S;
    while (!S.empty()) S.pop();
    for (int i = 1; i <= n; i++)
        if (a[i] == 0)
            S.push(i);
        else
            f[i] = S.top(), S.pop();
    for (int i = n; i && k < n; i--)
        if (a[i] == 1) ban[i] = ban[f[i]] = true, k += 2;
    for (int i = 1; i <= n; i++)
        if (!ban[i]) cout << "()"[a[i]];
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
