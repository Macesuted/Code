/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define maxn 1000005

typedef pair<long long, int> pli;

long long a[maxn], b[maxn], A[maxn], B[maxn];

priority_queue<pli, vector<pli>, greater<pli> > que;

int main() {
    ios::sync_with_stdio(false);
    int _, Case = 0;
    cin >> _;
    while (_--) {
        int l, n, m;
        cin >> l >> n >> m;
        for (register int i = 1; i <= n; i++) cin >> a[i];
        for (register int i = 1; i <= m; i++) cin >> b[i];
        while (!que.empty()) que.pop();
        for (register int i = 1; i <= n; i++) que.push((pli){a[i], i});
        for (register int i = 1; i <= l; i++) {
            long long v = que.top().first, p = que.top().second;
            que.pop(), A[i] = v, que.push((pli){v + a[p], p});
        }
        while (!que.empty()) que.pop();
        for (register int i = 1; i <= m; i++) que.push((pli){b[i], i});
        for (register int i = 1; i <= l; i++) {
            long long v = que.top().first, p = que.top().second;
            que.pop(), B[i] = v, que.push((pli){v + b[p], p});
        }
        long long answer = 0;
        for (register int i = 1; i <= l; i++) answer = max(answer, A[i] + B[l - i + 1]);
        cout << "Case #" << ++Case << ": " << answer << endl;
    }
    return 0;
}