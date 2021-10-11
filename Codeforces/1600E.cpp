/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar())
        x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 200005

int a[maxn];

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    int l = 1, r = n;
    while (l < n && a[l] < a[l + 1]) l++;
    while (r > 1 && a[r - 1] > a[r]) r--;
    r = n - r + 1;
    if (a[1] > a[n]) swap(l, r);
    return cout << ((l & 1) || (r & 1) ? "Alice" : "Bob") << endl, 0;
    return 0;
}