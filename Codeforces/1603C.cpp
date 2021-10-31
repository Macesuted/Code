#include <bits/stdc++.h>
using namespace std;

#define int long long

bool mem1;

#define maxn 100005
#define mod 998244353

typedef pair<int, int> pii;

int a[maxn];

vector<pii> record[2];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    record[0].clear(), record[1].clear();
    int answer = 0;
    for (int l = n, last = 0; l; l--) {
        bool thi = l & 1, tha = !thi;
        record[thi].clear();
        record[thi].emplace_back(a[l], 1);
        for (auto i = record[tha].begin(); i != record[tha].end(); i++) {
            int t = (a[l] - 1) / i->first;
            last = (last + t * i->second) % mod;
            if (record[thi].back().first == a[l] / (t + 1))
                record[thi].back().second += i->second;
            else
                record[thi].emplace_back(a[l] / (t + 1), i->second);
        }
        answer = (answer + last) % mod;
    }
    cout << answer << endl;
    return;
}

bool mem2;

signed main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;
    ios::sync_with_stdio(false);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}