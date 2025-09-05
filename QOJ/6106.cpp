/**
 * @file 6106.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

class SegmentTree {
   private:
    array<int, 10> a[maxn << 2];
    int n;

    array<int, 10> merge(const array<int, 10>& x, const array<int, 10>& y) {
        array<int, 10> ans = x;
        for (int i = 0; i < 10; i++) ans[i] += y[i];
        return ans;
    }

    void build(int p, int l, int r, const string& s) {
        if (l == r) {
            x[l] = s[l - 1] - '0';
            for (int t = 0; t < 10; t++) a[p][t] = (x[l] == t);
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, s), build(p << 1 | 1, mid + 1, r, s);
        return a[p] = merge(a[p << 1], a[p << 1 | 1]), void();
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return a[p][x[l]]--, a[p][x[l] = v]++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return a[p] = merge(a[p << 1], a[p << 1 | 1]), void();
    }
    array<int, 10> getPre(int p, int l, int r, int qp) {
        if (r <= qp) return a[p];
        int mid = (l + r) >> 1;
        if (qp <= mid) return getPre(p << 1, l, mid, qp);
        return merge(a[p << 1], getPre(p << 1 | 1, mid + 1, r, qp));
    }
    int getNext(int p, int l, int r, int qp) {
        if (a[p][x[qp]] == r - l + 1) return n + 1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (qp <= mid) {
            int ans = getNext(p << 1, l, mid, qp);
            if (ans != n + 1) return ans;
        }
        return getNext(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    int x[maxn];

    void build(const string& s) { return build(1, 1, n = s.size(), s); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    array<int, 10> getPre(int p) { return getPre(1, 1, n, p); }
    int getNext(int p) { return getNext(1, 1, n, p); }
} SGT;

array<int, 10> cnt;

void solve(void) {
    string X, Y;
    cin >> X >> Y;

    int n = X.size();
    for (int i = 0; i < 10; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[X[i] - '0']++;
    SGT.build(Y);

    auto chk = [&](int p) -> bool {
        array<int, 10> cnt = ::cnt;
        if (p) {
            array<int, 10> pre = SGT.getPre(p);
            for (int i = 0; i < 10; i++)
                if ((cnt[i] -= pre[i]) < 0) return false;
        }

        for (int t = 9, i = p + 1; t >= 0; t--) {
            if (!cnt[t]) continue;
            if (t != SGT.x[i]) return t > SGT.x[i];
            int len = SGT.getNext(i) - i, rlen = min(len, cnt[t]);
            len -= rlen, i += rlen;
            cnt[t] -= rlen;
            if (cnt[t]) return t > SGT.x[i];
        }
        return true;
    };

    int q;
    cin >> q;
    while (q--) {
        int op, i;
        cin >> op >> i;
        if (op == 1) {
            int x;
            cin >> x;
            SGT.update(i, x);
        } else {
            if (!chk(0)) {
                cout << -1 << endl;
                continue;
            }

            int l = 0, r = n + 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                (chk(mid) ? l : r) = mid;
            }

            if (i <= l) {
                cout << SGT.x[i] << endl;
                continue;
            }

            array<int, 10> cnt = ::cnt;
            if (l) {
                array<int, 10> pre = SGT.getPre(l);
                for (int i = 0; i < 10; i++) cnt[i] -= pre[i];
            }

            int d = SGT.x[r] + 1;
            while (!cnt[d]) d++;
            if (i == r) {
                cout << d << endl;
                continue;
            }
            cnt[d]--;

            for (int t = 0, p = r; t <= 9; p += cnt[t++])
                if (i <= p + cnt[t]) {
                    cout << t << endl;
                    break;
                }
        }
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