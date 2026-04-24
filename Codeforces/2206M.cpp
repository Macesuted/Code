#include <bits/stdc++.h>
using namespace std;

void solve(void) {
    int n;
    string s;
    cin >> n >> s;

    int L = 0, R = 0;

    {
        int sum = 0;

        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] == '(')
                sum++;
            else if (sum)
                sum--;
            else
                L++;

        sum = 0;
        for (int i = (int)s.size() - 1; ~i; i--)
            if (s[i] == ')')
                sum++;
            else if (sum)
                sum--;
            else
                R++;
    }

    vector<int> cnt;
    cnt.push_back(0);
    for (auto c : s)
        if (c == ')')
            cnt.push_back(0);
        else
            cnt.back()++;

    int sum = 0, minv = 0, maxv = 0;
    for (int i = 0; i < (int)cnt.size(); i++) {
        int v = (i & 1) ? -cnt[i] : +cnt[i];
        sum += v, minv = min(minv, sum), maxv = max(maxv, sum);
    }

    cout << min({[=](void) mutable -> int {
                     int ans = L + R, csum = L + sum;

                     if (L + minv < 0) {
                         int delt = -(L + minv);
                         L += delt, R += delt, ans += 2 * delt, csum += delt;
                     }

                     if (csum > 0) {
                         if ((cnt.size() & 1) && !R) L++, R++, ans += 2, csum++;
                         R += csum, ans += csum * 2;
                     }

                     if (!R) ans += 4;

                     return ans;
                 }(),
                 [=](void) mutable -> int {
                     int L1 = L + 1, L2 = 0;
                     int ans = L1 + 1 + L2 + R, csum = L1 - L2 - sum;

                     if (L1 - L2 - maxv < 0) {
                         int delt = -(L1 - L2 - maxv);
                         L1 += delt, R += delt, ans += 2 * delt, csum += delt;
                     }

                     while (csum > 1 && (L1 - 1) - (L2 + 1) - maxv >= 0 && L1 > 1) L1--, L2++, csum -= 2;

                     if (csum > 0) {
                         if (!(cnt.size() & 1) && !R) {
                             if (L1 - (L2 + 1) - maxv >= 0)
                                 L2++, R++, ans += 2, csum--;
                             else
                                 L1++, R++, ans += 2, csum++;
                         }
                         R += csum, ans += csum * 2;
                     }

                     if (!R) ans += 4;

                     return ans;
                 }(),
                 [=](void) mutable -> int {
                     int L1 = L + 1, L2 = 1;
                     int ans = L1 + 1 + L2 + 1 + R, csum = L1 - L2 + sum;

                     if (L1 - L2 + minv < 0) {
                         int delt = -(L1 - L2 + minv);
                         L1 += delt, R += delt, ans += 2 * delt, csum += delt;
                     }

                     while (csum > 1 && (L1 - 1) - (L2 + 1) + minv >= 0 && L1 > 1) L1--, L2++, csum -= 2;

                     if (csum > 0) {
                         if ((cnt.size() & 1) && !R) {
                             if (L1 - (L2 + 1) + minv >= 0)
                                 L2++, R++, ans += 2, csum--;
                             else
                                 L1++, R++, ans += 2, csum++;
                         }
                         R += csum, ans += csum * 2;
                     }

                     if (!R) ans += 4;

                     return ans;
                 }()}) -
                1
         << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}