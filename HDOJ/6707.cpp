/**
 * @file 6707.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using namespace std;

#define maxn 100005

bool use[maxn];

int a[maxn], b[maxn];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    for (int i = m; i; i--) {
        if (use[b[i]]) continue;
        cout << b[i] << ' ', use[b[i]] = true;
    }
    for (int i = 1; i <= n; i++)
        if (!use[a[i]]) cout << a[i] << ' ';
    cout << endl;
    return 0;
}