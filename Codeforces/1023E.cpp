/**
 * @file 1023E.cpp
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

void solve(void) {
    int n;
    cin >> n;
    int x = 1, y = 1;
    static deque<char> ansl, ansr;
    ansl.clear(), ansr.clear();
    for (int _ = n - 1; _; _--) {
        cout << "? " << x + 1 << ' ' << y << ' ' << n << ' ' << n << endl;
        string t;
        cin >> t;
        if (t == "NO")
            y++, ansl.push_back('R');
        else
            x++, ansl.push_back('D');
    }
    int a = n, b = n;
    for (int _ = n - 1; _; _--) {
        cout << "? " << 1 << ' ' << 1 << ' ' << a << ' ' << b - 1 << endl;
        string t;
        cin >> t;
        if (t == "NO")
            a--, ansr.push_front('D');
        else
            b--, ansr.push_front('R');
    }
    cout << "! ";
    for (auto i : ansl) cout << i;
    for (auto i : ansr) cout << i;
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
