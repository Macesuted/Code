/**
 * @file 551.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define LEN 100000

class HashTable {
   private:
    int key[LEN], val[LEN];
    queue<int> que;

   public:
    void inc(int k) {
        k++;
        int p = k % LEN;
        while (key[p] && key[p] != k)
            if (++p == LEN) p = 0;
        if (key[p]) return val[p]++, void();
        return key[p] = k, val[p] = 1, que.push(p);
    }
    int query(int k) {
        k++;
        int p = k % LEN;
        while (key[p] && key[p] != k)
            if (++p == LEN) p = 0;
        return key[p] ? val[p] : 0;
    }
    void clear(void) {
        while (!que.empty()) key[que.front()] = 0, que.pop();
        return;
    }
};

class Block {
   private:
    int n, m;
    vector<int> L, R, bel, sum;
    vector<HashTable> rec;

    void build(int p) {
        rec[p].clear(), sum[p] = 0;
        for (int i = L[p]; i <= R[p]; i++) rec[p].inc(sum[p] ^= a[i]);
        return;
    }

   public:
    vector<int> a;

    void resize(int _n) {
        n = _n, m = 1, a.resize(n), bel.resize(n);
        int B = min(n, 400);
        L.push_back(0), R.push_back(B - 1);
        while (R[m - 1] != n - 1) L.push_back(R[m - 1] + 1), R.push_back(min(n - 1, R[m - 1] + B)), m++;
        sum.resize(m - 1), rec.resize(m - 1);
        for (int i = 0; i < m; i++)
            for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
        return;
    }
    void build(void) {
        for (int i = 0; i < m - 1; i++) build(i);
        return;
    }
    void update(int p, int v) {
        a[p] ^= v;
        if (bel[p] != m - 1) build(bel[p]);
        return;
    }
    int64_t query(void) {
        int tot = 0, pre = 0;
        for (int i = 0; i < m - 1; pre ^= sum[i++]) tot += R[i] - L[i] + 1 - rec[i].query(pre);
        for (int i = L[m - 1]; i <= R[m - 1]; i++) tot += ((pre ^= a[i]) != 0);
        return pre ? 1e8 : tot;
    }
};

int a[maxn], b[maxn], last[maxn];
vector<Block> BLK;

void solve(void) {
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    b[0] = a[0];
    for (int i = n; i; i--) b[i] = a[i] ^ a[i - 1];
    BLK.resize(k);
    int64_t ans = 0;
    for (int i = 0; i < k; i++) {
        BLK[i].resize((n - i) / k + 1);
        for (int j = 0; j * k + i <= n; j++) BLK[i].a[j] = b[j * k + i];
        BLK[i].build(), ans += last[i] = BLK[i].query();
    }
    while (q--) {
        int p, x, v;
        cin >> p >> x, p--, v = a[p] ^ x, a[p] = x;
        ans -= last[p % k], BLK[p % k].update(p / k, v), ans += last[p % k] = BLK[p % k].query();
        p++, ans -= last[p % k], BLK[p % k].update(p / k, v), ans += last[p % k] = BLK[p % k].query();
        cout << (ans < 1e8 ? ans : -1) << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}