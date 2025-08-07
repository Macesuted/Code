#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1505

using pll = pair<int64_t, int64_t>;
using tlli = tuple<int64_t, int64_t, int>;

class FenwickTree {
   private:
    vector<int> a;
    int n;

   public:
    void resize(int _n) { return a.resize((n = _n) + 1); }
    void add(int p, int v) {
        for (int i = p; i <= n; i += i & -i) a[i] += v;
        return;
    }
    int sum(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += a[i];
        return ans;
    }
};

int id[maxn];
pll a[maxn];
tlli delt[maxn][maxn];
long double f[maxn][2];

bool operator<(const tlli& a, const tlli& b) { return get<0>(a) * get<1>(b) < get<1>(a) * get<0>(b); }

int64_t sqr(int64_t x) { return x * x; }
long double dist(int x, int y) { return sqrtl(sqr(a[x].first - a[y].first) + sqr(a[x].second - a[y].second)); }

void solve(void) {
    int n;
    long double K;
    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second, f[i][0] = f[i][1] = 1e18;

    f[1][0] = f[1][1] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) delt[i][j] = {a[j].first - a[i].first, a[j].second - a[i].second, j};

    for (int i = 1; i < n; i++) {
        f[i][0] = min(f[i][0], f[i][1] + K);
        f[i][1] = min(f[i][1], f[i][0] + K);

        vector<tlli> rec;
        for (int j = i + 1; j <= n; j++) rec.push_back(delt[i][j]);
        sort(rec.begin(), rec.end(), [&](const tlli& a, const tlli& b) { return a < b; });

        for (int j = 0; j < (int)rec.size(); j++) id[get<2>(rec[j])] = j + 1;

        FenwickTree FT;
        FT.resize(rec.size());

        f[i + 1][0] = min(f[i + 1][0], f[i][0] + dist(i, i + 1));
        f[i + 1][1] = min(f[i + 1][1], f[i][1] + dist(i, i + 1));

        for (int j = i + 2; j <= n; j++) {
            int ret = FT.sum(id[j]);
            bool it = delt[i][i + 1] < delt[i][j], jt = delt[i][j] < delt[j - 1][j];
            f[j][jt] = min(f[j][jt], f[i][it] + ret * K + dist(i, j));
            FT.add(min(id[j - 1], id[j]), +1);
            FT.add(max(id[j - 1], id[j]) + 1, -1);
        }
    }

    cout << setprecision(20) << fixed << min(f[n][0], f[n][1]) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}