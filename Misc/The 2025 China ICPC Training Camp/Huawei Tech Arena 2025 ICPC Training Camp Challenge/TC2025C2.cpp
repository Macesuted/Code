/**
 * @file TC2025C2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-17
 *
 * @copyright Copyright (c) 2025
 * @brief 845042 pts with 44% hit
 *
 */

#include <bits/stdc++.h>
using namespace std;

const double ALPHA_X = 8.0;
const double ALPHA_Y = 8.0;

inline double sqr(const double &x) { return x * x; }

struct Point {
    double X, Y;
};

class Vehicle {
   private:
   public:
    int type;
    Point nodes[4], center, size;
    double vx, vy;
    double dx, dy;

    double calcDeltaX(const Vehicle &o) const {
        return (abs(this->center.X - o.center.X) - (this->size.X + o.size.X) / 2) / (ALPHA_X * abs(this->vx - o.vx) + 1);
    }
    double calcDeltaY(const Vehicle &o) const {
        return (abs(this->center.Y - o.center.Y) - (this->size.Y + o.size.Y) / 2) / (ALPHA_Y * abs(this->vy - o.vy) + 1);
    }
    double calcDelta(const Vehicle &o) const {
        // if (o.center.X < this->center.X || o.vx > this->vx) return 1e18;
        double vx = calcDeltaX(o), vy = calcDeltaY(o);
        if (vx < 0 || vy < 0) return 1e18;
        return sqrt(sqr(vx) + sqr(vy));
        // return min(vx, vy);
    }

   public:
    void input(bool inputType = true, bool inputY = true, bool inputA = true) {
        type = 0;
        if (inputType) cin >> type;

        for (int t = 0; t < 4; t++) cin >> nodes[t].X >> nodes[t].Y;

        center.X = center.Y = 0;
        for (int t = 0; t < 4; t++) center.X += nodes[t].X, center.Y += nodes[t].Y;
        center.X /= 4, center.Y /= 4;

        double maxX = nodes[0].X, minX = nodes[0].X, maxY = nodes[0].Y, minY = nodes[0].Y;
        for (int t = 0; t < 4; t++) {
            maxX = max(maxX, nodes[t].X), minX = min(minX, nodes[t].X);
            maxY = max(maxY, nodes[t].Y), minY = min(minY, nodes[t].Y);
        }
        size.X = maxX - minX, size.Y = maxY - minY;

        cin >> vx;
        vy = 0;
        if (inputY) cin >> vy;

        dx = dy = 0;
        if (inputA) cin >> dx >> dy;

        return;
    }
    void move(double K) {
        center.X += K * vx + dx / 2 * K * K;
        center.Y += K * vy + dy / 2 * K * K;
        vx += dx * K;
        vy += dy * K;
        return;
    }

    double calcRisk(const Vehicle &o) const { return 1 / (this->calcDelta(o) + 1); }
};

const double K = 0.2;
const double SAFE_LIM = 0.801;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int M;
    cin >> M;

    for (int test = 1; test <= M; test++) {
        Vehicle Ego;
        Ego.input(false, true, true);
        double oax = Ego.dx, oay = Ego.dy;

        size_t N;
        cin >> N;
        vector<Vehicle> Objs(N);
        for (size_t i = 0; i < N; i++) Objs[i].input(true, true, true), Objs[i].move(K);

        vector<tuple<double, double, double>> avaiA;

        for (double ax = -6; ax <= +2; ax += 0.1)
            for (double ay = -5; ay <= +5; ay += 0.1) {
                if (!(-4 * K <= ax - oax && ax - oax <= +1 * K)) continue;
                if (!(-1 * K <= ay - oay && ay - oay <= +1 * K)) continue;

                Vehicle newEgo = Ego;
                newEgo.dx = ax, newEgo.dy = ay, newEgo.move(K);

                if (!(0 <= newEgo.vx && newEgo.vx <= 36)) continue;
                if (!(0 <= newEgo.vy && newEgo.vy <= 36)) continue;

                double maxSafe = 0;
                for (size_t i = 0; i < N; i++) maxSafe = max(maxSafe, newEgo.calcRisk(Objs[i]));

                avaiA.emplace_back(maxSafe, ax, ay);
            }

        if (avaiA.empty()) {
            cout << 0 << ' ' << 0 << endl;
            continue;
        }

        sort(avaiA.begin(), avaiA.end());

        double ansx = 0, ansy = 0;
        if (get<0>(avaiA.front()) <= SAFE_LIM) {
            double d;
            tie(d, ansx, ansy) = avaiA.front();
            for (auto [d, ax, ay] : avaiA)
                if (d <= SAFE_LIM && (abs(ay) < abs(ansy) || (abs(ay) == abs(ansy) && abs(ax) <= abs(ansx))))
                    tie(ansx, ansy) = {ax, ay};
        } else {
            double d;
            tie(d, ansx, ansy) = avaiA.front();
        }

        cout << ansx << ' ' << ansy << endl;
    }

    return 0;
}
