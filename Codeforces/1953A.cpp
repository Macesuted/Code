/**
 * @file 1953A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef float fp32;
typedef double fp64;
typedef long double fp128;

inline fp128 fabs128(fp128 a) { return a > 0 ? a : -a; }
int getExp(fp64 a) {
    if (fabs(a) == numeric_limits<fp64>::infinity()) return -1;

    uint64_t v = *(uint64_t*)(&a);
    int exp = 0;
    for (int i = 62; i > 51; i--) exp = (exp << 1) | (v >> i & 1);
    return exp - 1023;
}
int getLowbit(fp64 a) {
    uint64_t v = *(uint64_t*)(&a);
    int exp = getExp(a);
    for (int i = 0; i < 52; i++)
        if (v >> i & 1) return exp - (52 - i);
    return exp;
}

class fp16 {
    static const uint32_t mantissaShift = 42;
    static const uint32_t expShiftMid = 56;
    static const uint32_t expShiftOut = 52;
    double dValue_;

   public:
    fp16(double in) : dValue_(in) {
        uint64_t utmp;
        memcpy(&utmp, &dValue_, sizeof utmp);
        // zeroing mantissa bits starting from 11th (this is NOT rounding)
        utmp = utmp >> mantissaShift;
        utmp = utmp << mantissaShift;
        // setting masks for 5-bit exponent extraction out of 11-bit one
        const uint64_t maskExpMid = (63llu << expShiftMid);
        const uint64_t maskExpOut = (15llu << expShiftOut);
        const uint64_t maskExpLead = (1llu << 62);
        const uint64_t maskMantissaD = (1llu << 63) + maskExpLead + maskExpMid + maskExpOut;
        if (utmp & maskExpLead) {     // checking leading bit, suspect overflow
            if (utmp & maskExpMid) {  // Detected overflow if at least 1 bit is non-zero
                // Assign Inf with proper sign
                utmp = utmp | maskExpMid;     // setting 1s in the middle 6 bits of of exponent
                utmp = utmp & maskMantissaD;  // zeroing mantissa irrelative of original values to prevent NaN
                utmp = utmp | maskExpOut;     // setting 1s in the last 4 bits of exponent
            }
        } else {                                      // checking small numbers according to exponent range
            if ((utmp & maskExpMid) != maskExpMid) {  // Detected underflow if at least 1 bit is 0
                utmp = 0;
            }
        }
        memcpy(&dValue_, &utmp, sizeof utmp);
    }

    fp16() : dValue_(0) {}

    fp16& operator=(const fp16& rhs) {
        this->dValue_ = rhs.dValue_;
        return *this;
    }

    fp16& operator=(const fp64& rhs) {
        this->dValue_ = rhs;
        uint64_t utmp;
        memcpy(&utmp, &dValue_, sizeof utmp);
        utmp = utmp >> mantissaShift;
        utmp = utmp << mantissaShift;
        memcpy(&dValue_, &utmp, sizeof utmp);
        return *this;
    }

    friend fp16 operator+(const fp16& lhs, const fp16& rhs) { return fp16(lhs.dValue_ + rhs.dValue_); }

    fp64 convert2Fp64() { return dValue_; }
    fp32 convert2Fp32() { return static_cast<fp32>(dValue_); }
};
class exactFloat {
   private:
    fp128 sum, corr;

   public:
    exactFloat(void) : sum(0), corr(0) {}
    exactFloat(fp64 v) : sum(v), corr(0) {}
    exactFloat(fp128 sum_, fp128 corr_) : sum(sum_), corr(corr_) {}

    exactFloat& operator=(const fp64& o) { return this->sum = o, this->corr = 0, *this; }
    exactFloat operator+(const fp64& o) const {
        volatile fp128 y = static_cast<fp128>(o) - corr, t = sum + y;
        return exactFloat(t, (t - sum) - y);
    }
    exactFloat operator+(const exactFloat& o) const {
        if (sum < o.sum) return o + *this;
        volatile fp128 y = o.sum - corr - o.corr, t = sum + y;
        return exactFloat(t, (t - sum) - y);
    }
    bool operator<(const exactFloat& o) const { return sum < o.sum; }
    bool operator>(const exactFloat& o) const { return sum > o.sum; }

    fp128 convert2Fp128(void) const { return sum; }
    fp64 convert2Fp64(void) const { return sum; }
    fp32 convert2Fp32(void) const { return static_cast<fp32>(sum); }
};

int tim = 0;
struct Float {
    char op;
    int leaf, clk;
    fp64 stimu;
    exactFloat val;
    int valLowbit;
    array<Float*, 2> child;

    Float(void) { val = stimu = 0, valLowbit = 0, leaf = 0, clk = tim; };
    Float(fp64 v, int i) { val = stimu = v, valLowbit = getLowbit(v), leaf = i, clk = tim; }

    void getLeaf(vector<int>& a) const {
        if (leaf) return a.push_back(leaf);
        return child[0]->getLeaf(a), child[1]->getLeaf(a);
    }
    void print(void) const {
        if (leaf) return cout << leaf, void();
        cout << '{' << op << ':', child[0]->print(), cout << ',', child[1]->print(), cout << '}';
        return;
    }
    void erase(int tim = -1) {
        if (tim == -1) tim = clk;
        if (clk != tim) return;
        child[0]->erase(tim), child[1]->erase(tim);
        delete this;
        return;
    }
    fp128 accu(void) const { return fabs128(stimu - val.convert2Fp128()); }
    fp128 accu64(void) const { return fabs128(stimu - val.convert2Fp64()); }
};
struct cmpFloatPtr1 {
    bool operator()(Float* a, Float* b) const { return a->valLowbit > b->valLowbit; }
};
struct cmpFloatPtr2 {
    bool operator()(Float* a, Float* b) const { return fabs(a->val.convert2Fp64()) > fabs(b->val.convert2Fp64()); }
};
struct cmpFloatPtr3 {
    bool operator()(Float* a, Float* b) const { return a->accu() < b->accu(); }
};

fp128 total = 0, thre16, thre32;

int n;
vector<Float*> a;

char checkType(fp64 a, fp64 b) {
    fp64 v16 = (fp16(a) + fp16(b)).convert2Fp64(), v32 = static_cast<fp64>(static_cast<fp32>(a) + static_cast<fp32>(b)),
         v64 = a + b;
    if (!isinf(v16) && fabs(v16 - v64) < thre16) return 'h';
    if (!isinf(v32) && fabs(v32 - v64) < thre32) return 's';
    return 'd';
}
Float* merge(char op, Float* a, Float* b) {
    if (!a) return b;
    if (!b) return a;

    auto p = new Float();
    p->op = op, p->child[0] = a, p->child[1] = b;
    p->val = a->val + b->val, p->valLowbit = getLowbit(p->val.convert2Fp64());
    if (op == 'h') p->stimu = (fp16(a->stimu) + fp16(b->stimu)).convert2Fp64();
    if (op == 's') p->stimu = static_cast<fp64>(static_cast<fp32>(a->stimu) + static_cast<fp32>(b->stimu));
    if (op == 'd') p->stimu = a->stimu + b->stimu;
    return p;
}
Float* merge(Float* a, Float* b) {
    if (!a) return b;
    if (!b) return a;
    return merge(checkType(a->stimu, b->stimu), a, b);
}

void mergeTop1(priority_queue<Float*, vector<Float*>, cmpFloatPtr1>& S) {
    auto p1 = S.top();
    S.pop();
    auto p2 = S.top();
    S.pop();
    S.push(merge(p1, p2));
    return;
}
void mergeTop2(priority_queue<Float*, vector<Float*>, cmpFloatPtr2>& S) {
    auto p1 = S.top();
    S.pop();
    auto p2 = S.top();
    S.pop();
    S.push(merge(p1, p2));
    return;
}
Float* merge(const vector<Float*>& a) {
    if (a.empty()) return nullptr;

    Float* ans;
    {
        tim++;

        priority_queue<Float*, vector<Float*>, cmpFloatPtr1> S;
        for (auto i : a) S.push(i);
        while (S.size() > 1) mergeTop1(S);

        ans = S.top();
    }
    {
        tim++;

        priority_queue<Float*, vector<Float*>, cmpFloatPtr2> S1, S2;
        for (auto i : a) (i->val > 0 ? S1 : S2).push(i);
        while (S1.size() > 1) mergeTop2(S1);
        while (S2.size() > 1) mergeTop2(S2);
        Float* tot = nullptr;
        if (!S1.empty()) tot = merge(tot, S1.top());
        if (!S2.empty()) tot = merge(tot, S2.top());

        if (tot->accu64() < ans->accu64()) ans->erase(), ans = tot;
    }
    {
        tim++;

        priority_queue<Float*, vector<Float*>, cmpFloatPtr2> S;
        for (auto i : a) S.push(i);
        while (S.size() > 1) mergeTop2(S);

        if (S.top()->accu64() < ans->accu64()) ans->erase(), ans = S.top();
    }
    {
        tim++;

        Float* tot = a[0];
        for (int i = 1; i < (int)a.size(); i++) tot = merge(tot, a[i]);

        if (tot->accu64() < ans->accu64()) ans->erase(), ans = tot;
    }
    return ans;
}

Float* solve1(void) {
    priority_queue<Float*, vector<Float*>, cmpFloatPtr3> S;
    for (int l = 0; l + 16 <= n; l += 16) {
        int r = l + 16;

        vector<Float*> T;
        for (int i = l; i < r; i++) T.push_back(a[i]);
        S.push(merge(T));
    }

    {
        int cnt = 0;
        while (S.size() > 1 && (++cnt) * 8000 < n) {
            Float* p1 = S.top();
            S.pop();
            Float *p2 = S.top(), *p3 = merge(p1, p2);
            S.pop();
            vector<int> ids;
            p1->getLeaf(ids), p2->getLeaf(ids);
            vector<Float*> T;
            for (auto i : ids) T.push_back(a[i - 1]);
            Float* p4 = merge(T);
            if (p3->accu() < p4->accu()) {
                p3->erase(), p4->erase(), S.push(p1), S.push(p2);
                break;
            }
            p3->erase(), S.push(p4);
        }
    }

    vector<Float*> Svec;
    while (!S.empty()) Svec.push_back(S.top()), S.pop();
    vector<Float*> T;
    for (int i = n - n % 16; i < n; i++) T.push_back(a[i]);
    return merge(merge(Svec), merge(T));
}
Float* solve2(void) {
    priority_queue<Float*, vector<Float*>, cmpFloatPtr1> S;
    for (int l = 0; l + 16 <= n; l += 16) {
        int r = l + 16;

        priority_queue<Float*, vector<Float*>, cmpFloatPtr1> T;
        for (int i = l; i < r; i++) T.push(a[i]);

        while (T.size() > 1) mergeTop1(T);
        S.push(T.top());
    }

    Float* ans = nullptr;

    while (S.size() > 1) mergeTop1(S);
    if (!S.empty()) ans = S.top();

    {
        priority_queue<Float*, vector<Float*>, cmpFloatPtr1> T;
        for (int i = n - n % 16; i < n; i++) T.push(a[i]);
        while (T.size() > 1) mergeTop1(T);
        if (!T.empty()) ans = merge(ans, T.top());
    }
    return ans;
}
Float* solve3(void) {
    priority_queue<Float*, vector<Float*>, cmpFloatPtr2> S;
    for (int l = 0; l + 16 <= n; l += 16) {
        int r = l + 16;

        priority_queue<Float*, vector<Float*>, cmpFloatPtr2> T;
        for (int i = l; i < r; i++) T.push(a[i]);

        while (T.size() > 1) mergeTop2(T);
        S.push(T.top());
    }

    Float* ans = nullptr;

    while (S.size() > 1) mergeTop2(S);
    if (!S.empty()) ans = S.top();

    {
        priority_queue<Float*, vector<Float*>, cmpFloatPtr2> T;
        for (int i = n - n % 16; i < n; i++) T.push(a[i]);
        while (T.size() > 1) mergeTop2(T);
        if (!T.empty()) ans = merge(ans, T.top());
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        fp64 v;
        cin >> v, total += v;
        a.push_back(new Float(v, i + 1));
    }

    thre16 = thre32 = max(fabs128(total), fp128(1e-200));
    for (int i = 0; i < 80; i++) thre16 /= 2;
    for (int i = 0; i < 80; i++) thre32 /= 2;

    Float *ans1 = solve1(), *ans2 = solve2(), *ans3 = solve3();
    Float* ans = ans1;
    if (ans2->accu64() < ans->accu64()) ans = ans2;
    if (ans3->accu64() < ans->accu64()) ans = ans3;

    if (n <= 40000) {
        Float* ans4 = merge(a);
        if (ans4->accu64() <= ans->accu64()) ans = ans4;
    }

    cerr << setprecision(50) << "!!! " << ans->stimu << ' ' << ans->val.convert2Fp64() << endl;

    ans->print(), cout << endl;

    return 0;
}