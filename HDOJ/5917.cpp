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
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 55
#define mod 1000000007

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

vector<bitset<maxn>> graph;
int C[maxn][maxn];

int c[7], n, m;
int dfs(int p, int dep) {
    c[dep] = p;
    int answer = 0;
    if (dep >= 3) {
        for (int i = 1; i <= dep && !answer; i++)
            for (int j = i + 1; j <= dep && !answer; j++)
                for (int k = j + 1; k <= dep && !answer; k++) {
                    int cnt = (int)graph[c[i]][c[j]] + (int)graph[c[i]][c[k]] + (int)graph[c[j]][c[k]];
                    if (cnt == 0 || cnt == 3) answer = 1;
                }
    }
    if (dep < 5) {
        for (int i = p + 1; i <= n; i++) answer = (answer + dfs(i, dep + 1)) % mod;
    }
    return answer;
}

void solve(void) {
    n = read<int>(), m = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        graph[x][y] = graph[y][x] = true;
    }
    long long answer = dfs(0, 0);
    if (n > 5) {
        answer = (answer + Pow(2, n)) % mod;
        for (int i = 0; i <= 5; i++) answer = (answer + mod - C[n][i]) % mod;
    }
    cout << answer << endl;
    graph.clear();
    return;
}

int main() {
    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    ios::sync_with_stdio(false);
    int _ = read<int>();
    for (int __ = 1; __ <= _; __++) {
        cout << "Case #" << __ << ": ";
        solve();
    }
    return 0;
}