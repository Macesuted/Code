/**
 * @file 1724A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef pair<int, int> pii;
typedef pair<double, int> pdi;
typedef pair<double, double> pdd;
typedef tuple<int, int, int> tiii;

struct _VMBase {
    int cor, cpu, mem;
};

vector<_VMBase> VMType;

#ifdef LOCAL
#define SEED chrono::system_clock::now().time_since_epoch().count()
#elif
#define SEED 962000536 
#endif

mt19937 rnd(SEED);

class _SP {
   private:
    struct _PG {
        int k, a, n, r, cnt, NTid;
        map<int, int> NTCnt;
        map<pii, int> RKBel, RKCnt;
        map<tiii, int> PMCnt;

        _PG(void) = default;
        _PG(int _k, int _a, int _n, int _r) : k(_k), a(_a), n(_n), r(_r), cnt(0), NTid(-1) {}
    };
    struct _VM {
        int typ, pg, NT, RK, PM;
        vector<int> CR;
        _VM(void) : typ(0), pg(0), NT(0), RK(0), PM(-1) {}
    };

    class _NT {
       private:
        class _RK {
           private:
            class _PM {
               private:
                struct _CR {
                    int CPU, MEM, restCPU, restMEM;

                    _CR(int _CPU, int _MEM) : CPU(_CPU), MEM(_MEM), restCPU(_CPU), restMEM(_MEM) {}
                    double usage(void) const { return max(double(CPU - restCPU) / CPU, double(MEM - restMEM) / MEM); }
                    int calcVM(int typ) const { return min(restCPU / VMType[typ].cpu, restMEM / VMType[typ].mem); }
                    void createVM(int typ) { return restCPU -= VMType[typ].cpu, restMEM -= VMType[typ].mem, void(); }
                    void deleteVM(int typ) { return restCPU += VMType[typ].cpu, restMEM += VMType[typ].mem, void(); }
                };

               public:
                vector<_CR> CR;
                vector<int> numVM;
                int totCPU, totMEM, usedCPU, usedMEM;

                _PM(int K, vector<int> C, vector<int> M) {
                    CR.reserve(K);
                    for (int i = 0; i < K; i++) CR.emplace_back(C[i], M[i]);
                    recalcVM();
                }
                _CR& operator[](const size_t x) { return CR[x]; }
                double usage(void) const { return max(double(usedCPU) / totCPU, double(usedMEM) / totMEM); }
                void recalcVM(void) {
                    numVM.clear(), numVM.resize(VMType.size());
                    for (int i = 0; i < (int)VMType.size(); i++)
                        if (VMType[i].cor == 1)
                            for (int j = 0; j < (int)CR.size(); j++) numVM[i] += CR[j].calcVM(i);
                        else
                            for (int j = 0; j < (int)CR.size(); j += 2)
                                numVM[i] += min(CR[j].calcVM(i), CR[j ^ 1].calcVM(i));
                    totCPU = totMEM = usedCPU = usedMEM = 0;
                    for (const auto& i : CR)
                        totCPU += i.CPU, totMEM += i.MEM, usedCPU += i.CPU - i.restCPU, usedMEM += i.MEM - i.restMEM;
                    return;
                }
                void deleteVM(_VM vm) {
                    for (auto i : vm.CR) CR[i].deleteVM(vm.typ);
                    return recalcVM();
                }
            };

           public:
            vector<_PM> PM;
            vector<int> numVM;
            int totCPU, totMEM, usedCPU, usedMEM;

            _RK(int S, int K, vector<int> C, vector<int> M) : PM(vector<_PM>(S, _PM(K, C, M))) { recalcVM(); }
            _PM& operator[](const size_t x) { return PM[x]; }
            double usage(void) const { return max(double(usedCPU) / totCPU, double(usedMEM) / totMEM); }
            void recalcVM(void) {
                numVM.clear(), numVM.resize(VMType.size());
                for (int i = 0; i < (int)VMType.size(); i++)
                    for (const auto& j : PM) numVM[i] += j.numVM[i];
                totCPU = totMEM = usedCPU = usedMEM = 0;
                for (const auto& i : PM)
                    totCPU += i.totCPU, totMEM += i.totMEM, usedCPU += i.usedCPU, usedMEM += i.usedMEM;
                return;
            }
            _VM createVM(pii loc, int typ, _PG& pg, bool force) {
                vector<pii> order;
                for (int i = 0; i < (int)PM.size(); i++)
                    for (int j = 0; j < (int)PM[i].CR.size(); j += VMType[typ].cor)
                        if (PM[i][j].calcVM(typ) && (VMType[typ].cor == 1 || PM[i][j ^ 1].calcVM(typ)) &&
                            (!force || !pg.a || pg.PMCnt[{loc.first, loc.second, i}] < pg.a))
                            order.emplace_back(i, j);
                sort(order.begin(), order.end(), [&](pii a, pii b) {
                    if (PM[0].CR.size() == 2)
                        if (VMType[typ].cor == 1)
                            return PM[a.first][a.second].usage() < PM[b.first][b.second].usage();
                        else
                            return PM[a.first].numVM[typ] < PM[b.first].numVM[typ];
                    else {
                        if (VMType[typ].cor == 1) {
                            bool pa = (PM[a.first][a.second].calcVM(typ) - 1 >= PM[a.first][a.second ^ 1].calcVM(typ)),
                                 pb = (PM[b.first][b.second].calcVM(typ) - 1 >= PM[b.first][b.second ^ 1].calcVM(typ));
                            if (pa != pb) return pa;
                            return min(PM[a.first][a.second].calcVM(typ) - 1, PM[a.first][a.second ^ 1].calcVM(typ)) <
                                   min(PM[b.first][b.second].calcVM(typ) - 1, PM[b.first][b.second ^ 1].calcVM(typ));
                        } else
                            return min(PM[a.first][a.second].calcVM(typ), PM[a.first][a.second ^ 1].calcVM(typ)) <
                                   min(PM[b.first][b.second].calcVM(typ), PM[b.first][b.second ^ 1].calcVM(typ));
                    }
                });
                if (order.empty()) return _VM();
                pii ans = order.front();
                _VM ret;
                ret.PM = ans.first, ret.CR.push_back(ans.second), PM[ans.first][ans.second].createVM(typ);
                if (VMType[typ].cor == 2) ret.CR.push_back(ans.second ^ 1), PM[ans.first][ans.second ^ 1].createVM(typ);
                return PM[ret.PM].recalcVM(), recalcVM(), ret;
            }
            void deleteVM(_VM vm) { return PM[vm.PM].deleteVM(vm), recalcVM(); }
        };

       public:
        vector<_RK> RK;
        vector<int> numVM;
        int totCPU, totMEM, usedCPU, usedMEM;

        _NT(int R, int S, int K, vector<int> C, vector<int> M) : RK(vector<_RK>(R, _RK(S, K, C, M))) { recalcVM(); }
        _RK& operator[](const size_t x) { return RK[x]; }
        double usage(void) const { return max(double(usedCPU) / totCPU, double(usedMEM) / totMEM); }
        void recalcVM(void) {
            numVM.clear(), numVM.resize(VMType.size());
            for (int i = 0; i < (int)VMType.size(); i++)
                for (const auto& j : RK) numVM[i] += j.numVM[i];
            totCPU = totMEM = usedCPU = usedMEM = 0;
            for (const auto& i : RK) totCPU += i.totCPU, totMEM += i.totMEM, usedCPU += i.usedCPU, usedMEM += i.usedMEM;
            return;
        }
        _VM createVM(int loc, int typ, _PG& pg, int par, bool force) {
            vector<int> order;
            for (int i = 0; i < (int)RK.size(); i++)
                if (RK[i].numVM[typ] && (!par || !pg.RKBel.count({loc, i}) || pg.RKBel[{loc, i}] == par))
                    order.push_back(i);
            sort(order.begin(), order.end(), [&](int a, int b) { return RK[a].usage() > RK[b].usage(); });
            if (par) {
                vector<int> cache;
                for (auto i : order)
                    if (pg.RKBel.count({loc, i})) cache.push_back(i);
                // sort(cache.begin(), cache.end(), [&](int a, int b) { return pg.RKCnt[{loc, a}] > pg.RKCnt[{loc, b}];
                // });
                shuffle(cache.begin(), cache.end(), rnd);
                for (auto i : order)
                    if (!pg.RKBel.count({loc, i})) cache.push_back(i);
                order = cache;
            }
            for (auto i : order) {
                _VM ret = RK[i].createVM({loc, i}, typ, pg, force);
                if (~ret.PM) return ret.RK = i, recalcVM(), ret;
            }
            if (force)
                for (auto i : order) {
                    _VM ret = RK[i].createVM({loc, i}, typ, pg, false);
                    if (~ret.PM) return ret.RK = i, recalcVM(), ret;
                }
            return _VM();
        }
        void deleteVM(_VM vm) { return RK[vm.RK].deleteVM(vm), recalcVM(); }
    };

    vector<_NT> NT;
    map<int, _PG> PG;

    _VM createVM(int typ, _PG& pg, int par, bool force) {
        if (pg.n == 2) {
            int NTid = (int)NT.size() - 1;
            vector<int> order;
            for (int i = (int)NT[NTid].RK.size() - 1; ~i; i--)
                if (NT[NTid][i].numVM[typ]) order.push_back(i);
            for (auto i : order) {
                _VM ret = NT.back()[i].createVM({NTid, i}, typ, pg, force);
                if (~ret.PM) return ret.NT = NTid, ret.RK = i, NT[NTid].recalcVM(), ret;
            }
            return _VM();
        }
        if (force && pg.n && pg.NTCnt.size() > 1) return _VM();
        vector<int> order;
        for (int i = 0; i < (int)NT.size() - 1; i++)
            if (NT[i].numVM[typ]) order.push_back(i);
        sort(order.begin(), order.end(), [&](int a, int b) { return NT[a].numVM[typ] < NT[b].numVM[typ]; });
        if (force && pg.n && pg.NTCnt.empty())
            reverse(order.begin(), order.end());
        else if (force && pg.n) {
            order.clear(), order.push_back(pg.NTCnt.begin()->first);
        } else if (!force && pg.n) {
            vector<int> cache1, cache2;
            for (auto i : order)
                if (pg.NTCnt.count(i)) cache1.push_back(i);
            sort(cache1.begin(), cache1.end(), [&](int a, int b) { return pg.NTCnt[a] > pg.NTCnt[b]; });
            for (auto i : order)
                if (!pg.NTCnt.count(i)) cache2.push_back(i);
            shuffle(cache2.begin(), cache2.end(), rnd);
            order = cache1;
            for (auto i : cache2) order.push_back(i);
        }
        order.push_back((int)NT.size() - 1);
        for (auto i : order) {
            _VM ret = NT[i].createVM(i, typ, pg, par, force);
            if (~ret.PM) {
                if (~pg.NTid) pg.NTid = i;
                return ret.NT = i, ret;
            }
        }
        return _VM();
    }

   public:
    map<int, _VM> VM;
    int soft;

    _SP(void) = default;
    _SP(int N, int R, int S, int K, vector<int> C, vector<int> M) : NT(vector<_NT>(N, _NT(R, S, K, C, M))) { soft = 0; }
    void createPG(int id, int k, int a, int n, int r) { return PG[id] = _PG(k, a, n, r), void(); }
    bool createVM(int num, int typ, int _pg, int par, vector<int> ids, bool force) {
        _PG& pg = PG[_pg];
        if (!pg.r || (pg.r == 1 && !force)) {
            for (int i = 0; i < num; i++) {
                _VM ret = VM[ids[i]] = createVM(typ, pg, ~par ? par : i + 1, force);
                if (!~ret.PM) {
                    for (int j = 0; j < i; j++) deleteVM(ids[j]);
                    return false;
                }
                VM[ids[i]].typ = typ, VM[ids[i]].pg = _pg;
                pg.cnt++, pg.NTCnt[VM[ids[i]].NT]++, pg.PMCnt[{VM[ids[i]].NT, VM[ids[i]].RK, VM[ids[i]].PM}]++;
                if (par) pg.RKBel[{VM[ids[i]].NT, VM[ids[i]].RK}] = par, pg.RKCnt[{VM[ids[i]].NT, VM[ids[i]].RK}]++;
            }
            return true;
        }
        vector<pii> order;
        for (int i = (int)NT.size() - 1; i < (int)NT.size(); i++)
            for (int j = 0; j < (int)NT[i].RK.size(); j++)
                if (NT[i][j].numVM[typ] >= num) order.emplace_back(i, j);
        sort(order.begin(), order.end(), [&](pii a, pii b) {
            return pdd{NT[a.first].usage(), NT[a.first][a.second].usage()} >
                   pdd{NT[b.first].usage(), NT[b.first][b.second].usage()};
        });
        {
            vector<pii> cache;
            for (int i = 0; i < (int)NT.size() - 1; i++)
                for (int j = 0; j < (int)NT[i].RK.size(); j++)
                    if (NT[i][j].numVM[typ] >= num) cache.emplace_back(i, j);
            sort(cache.begin(), cache.end(), [&](pii a, pii b) {
                return pdd{NT[a.first].usage(), NT[a.first][a.second].usage()} >
                       pdd{NT[b.first].usage(), NT[b.first][b.second].usage()};
            });
            for (auto i : cache) order.push_back(i);
        }
        for (auto [i, j] : order) {
            bool success = true;
            for (int x = 0; x < num; x++) {
                _VM ret = VM[ids[x]] = NT[i][j].createVM({i, j}, typ, pg, force);
                if (!~ret.PM) {
                    for (int y = 0; y < x; y++) deleteVM(ids[y]);
                    success = false;
                    break;
                }
                VM[ids[x]].typ = typ, VM[ids[x]].pg = _pg, VM[ids[x]].NT = i, VM[ids[x]].RK = j;
                pg.cnt++, pg.NTCnt[i]++, pg.PMCnt[{i, j, VM[ids[x]].PM}]++;
                if (par) pg.RKBel[{i, j}] = par, pg.RKCnt[{i, j}]++;
            }
            if (success) return true;
        }
        return false;
    }
    void createVM(int num, int typ, int _pg, int par, vector<int> ids) {
        _PG& pg = PG[_pg];
        if ((pg.a > 0 || pg.n == 1 || pg.r == 1) && createVM(num, typ, _pg, par, ids, true)) return soft += num, void();
        if (createVM(num, typ, _pg, par, ids, false)) return;
        return cout << -1 << endl, cerr << "SOFT: " << soft << endl, exit(0);
    }
    void deleteVM(int id) {
        _VM vm = VM[id];
        _PG& pg = PG[vm.pg];
        NT[vm.NT].deleteVM(vm);
        if (pg.r) return;
        pg.cnt--, pg.PMCnt[{vm.NT, vm.RK, vm.PM}]--;
        if (!--pg.NTCnt[vm.NT]) pg.NTCnt.erase(vm.NT);
        if (pg.k && !--pg.RKCnt[{vm.NT, vm.RK}]) pg.RKBel.erase({vm.NT, vm.RK}), pg.RKCnt.erase({vm.NT, vm.RK});
        VM.erase(id);
        return;
    }
} center;

void solve(void) {
    int N, R, S, K, F;
    cin >> N >> R >> S >> K;
    vector<int> C(K), M(K);
    for (int i = 0; i < K; i++) cin >> C[i] >> M[i];
    cin >> F;
    for (int i = 0, cor, cpu, mem; i < F; i++) cin >> cor >> cpu >> mem, VMType.push_back(_VMBase{cor, cpu, mem});
    center = _SP(N, R, S, K, C, M);
    while (true) {
        int T;
        cin >> T;
        if (T == 1) {
            int id, k, a, n, r;
            cin >> id >> k >> a >> n >> r, center.createPG(id, k, a, n, r);
        } else if (T == 2) {
            int l, f, j, p;
            cin >> l >> f >> j >> p;
            vector<int> ids(l);
            for (int i = 0; i < l; i++) cin >> ids[i];
            center.createVM(l, f - 1, j, p, ids);
            for (auto i : ids) {
                cout << center.VM[i].NT + 1 << ' ' << center.VM[i].RK + 1 << ' ' << center.VM[i].PM + 1;
                for (auto j : center.VM[i].CR) cout << ' ' << j + 1;
                cout << endl;
            }
        } else if (T == 3) {
            int l;
            cin >> l;
            for (int i = 0, v; i < l; i++) cin >> v, center.deleteVM(v);
        } else
            return cerr << "SOFT: " << center.soft << endl, void();
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int _ = 1;
    while (_--) solve();
    return 0;
}