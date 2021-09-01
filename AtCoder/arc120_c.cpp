/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 200005

int b[maxn];
map<int, queue<int> > record;

int tree[maxn];

void add(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (register int i = 1, x; i <= n; i++) {
        cin >> x;
        record[x + i].push(i);
    }
    for (register int i = 1, x; i <= n; i++) {
        cin >> x;
        if (record[x + i].empty()) {
            cout << -1 << endl;
            return 0;
        }
        b[i] = record[x + i].front(), record[x + i].pop();
    }
    record.clear();
    long long answer = 0;
    for (register int i = 1; i <= n; i++) {
        answer += i - 1 - sum(b[i]);
        add(b[i], 1);
    }
    cout << answer << endl;
    return 0;
}
