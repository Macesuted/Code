/**
 * @file arc133_a.cpp
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

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> rec;
    rec.push_back(a[1]);
    for (int i = 2; i <= n; i++)
        if (a[i] != a[i - 1]) rec.push_back(a[i]);
    if (rec.size() == 1) return;
    int banP = rec.back();
    for (int i = 1; i < (int)rec.size(); i++)
        if (rec[i] < rec[i - 1]) {
            banP = rec[i - 1];
            break;
        }
    for (int i = 1; i <= n; i++)
        if (a[i] != banP) cout << a[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
