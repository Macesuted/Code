#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int a[maxn], b[maxn];

set<pii> S;

void work(int n, int v[]) {
    v[0] = 0;
    for (int i = 1; i <= n; i++) {
        v[i] = v[i - 1];
        int p = 0;
        while (true) {
            auto j = S.lower_bound({p, 0});
            if (j == S.end()) break;
            v[i]++, p = j->second + 1;
            S.erase(j);
        }
    }
    return;
}

void solve(void) {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++) {
        int l, r;
        cin >> l >> r;
        S.insert({l, r});
    }
    work(n, a);
    S.clear();
    for (int i = 1; i <= m2; i++) {
        int l, r;
        cin >> l >> r;
        S.insert({l, r});
    }
    work(n, b);
    S.clear();
    int answer = 0;
    for (int i = 0; i <= n; i++) answer = max(answer, a[i] + b[n - i]);
    cout << answer << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("airport.in", "r", stdin), freopen("airport.out", "w", stdout);
#endif
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    clock_t tim1 = clock();
    ios::sync_with_stdio(false);

    solve();

    clock_t tim2 = clock();
    cerr << "Time: " << (tim2 - tim1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}