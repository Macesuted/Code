/**
 * @file 3501.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
bool mem1;
#endif

template <typename T>
T read(void) {
    T f = +1, num = 0;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
    return f * num;
}
template <typename T>
void write(T num) {
    if (num == 0) return putchar('0'), void();
    if (num < 0) putchar('-'), num = -num;
    if (num > 9) write(num / 10);
    putchar((num % 10) ^ 48);
    return;
}

#define maxn 1005
#define maxm 200005

int graph[maxn][maxn], ans[maxm];

int cmin(int x, int y) { return x > y ? y : x; }
int cmax(int x, int y) { return x > y ? x : y; }

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) graph[i][j] = ((i == j) ? 0 : 0x3f3f3f3f);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        graph[x][y] = m - i + 1;
    }
    for (int k = n; k; k--) {
        for (int i = 1; i <= n; i++)
            if (graph[i][k] != 0x3f3f3f3f)
                for (int j = 1; j <= n; j++) graph[i][j] = cmin(graph[i][j], cmax(graph[i][k], graph[k][j]));
        for (int i = k; i <= n; i++)
            if (cmax(graph[i][k], graph[k][i]) != 0x3f3f3f3f) ans[cmax(graph[i][k], graph[k][i])]++;
    }
    for (int i = 1; i <= m; i++) ans[i] += ans[i - 1];
    for (int i = m; ~i; i--) write(ans[i]), putchar(" \n"[i == 0]);
    return;
}

#ifdef LOCAL
bool mem2;
#endif

int main() {
#ifndef LOCAL
    // freopen("graph.in", "r", stdin), freopen("graph.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << " MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << " ms" << endl;
#endif

    return 0;
}