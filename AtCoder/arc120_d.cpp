/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 400005

typedef pair<int, int> pii;

int a[maxn];
pii b[maxn];
bool vis[maxn];

stack<pii> S;

string answer;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    n <<= 1;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= n; i++) b[i] = (pii){a[i], i};
    sort(b + 1, b + n + 1, greater<pii>());
    for (register int i = 1; i * 2 <= n; i++) vis[b[i].second] = true;
    answer.resize(n);
    for (register int i = 1; i <= n; i++)
        if (S.empty() || vis[i] == S.top().second)
            S.push((pii){i, vis[i]});
        else
            answer[S.top().first - 1] = '(', answer[i - 1] = ')', S.pop();
    cout << answer << endl;
    return 0;
}
