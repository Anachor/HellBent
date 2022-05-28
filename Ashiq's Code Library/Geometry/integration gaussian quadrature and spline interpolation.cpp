/**
 * Problem: dog (aka Parabellum).
 * Correct solution (must be OK).
 * Author: stgatilov
 *
 * Incrementally integrates time over angle with 3-node Guass quadrature (saving time values)
 * Time for angle is interpolated with cubic spline (Hermite).
 * After period reduction, angle from time is determined with binary search.
 *
 * OK on current tests with maxError = 1e-7 in checker.
 * Time: O(N + N log(eps))      N - number of nodes
 */

//#pragma comment(linker, "/STACK:20000000")
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <unordered_set>
#include <cinttypes>
#include <climits>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
typedef long long int64;
#ifdef HOME
    #define E(c) cerr<<#c
    #define Eo(x) cerr<<#x<<" = "<<(x)<<endl
    #define Ef(...) fprintf(stderr, __VA_ARGS__)
#else
    #define E(c) ((void)0)
    #define Eo(x) ((void)0)
    #define Ef(...) ((void)0)
#endif


struct Point {
    double x, y;

    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    Point operator- (const Point &b) {
        return Point(x - b.x, y - b.y);
    }
    Point operator+ (const Point &b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator* (double coef) {
        return Point(x * coef, y * coef);
    }
};

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double len(const Point &a) {
    return sqrt(dot(a, a));
}
Point polar(double ang) {
    return Point(cos(ang), sin(ang));
}

Point ostapPos, kislaPos;
Point ostapVel;
double kislaSpeed;
double radius, startAngle;

double pi = acos(-1.0);

double CalcAngularSpeed(double deltaAngle) {
    double polarAngle = deltaAngle + (pi/2.0+ startAngle);
    Point dir = polar(polarAngle);

    double qb2 = dot(ostapVel, dir);
    double qc = dot(ostapVel, ostapVel) - (kislaSpeed * kislaSpeed);
    double qd2 = qb2*qb2 - qc;
    assert(qd2 > 0.0);
    double sol = sqrt(qd2) - qb2;

    double angSp = sol / radius;
    return angSp;
}
double CalcDtDa(double deltaAngle) {
    return 1.0 / CalcAngularSpeed(deltaAngle);
}

const int NODES = 100<<10;
double timeVal[NODES + 1], timeDer[NODES + 1];

//const int GAUSS_CNT = 3;
//const double GAUSS_NODES[] = {-sqrt(3.0/5.0), 0.0, sqrt(3.0/5.0)};
//const double GAUSS_WEIGHTS[] = {5.0/9.0, 8.0/9.0, 5.0/9.0};
//

const int GAUSS_CNT = 4;
const double GAUSS_NODES[] = {-sqrt(3.0/7.0 + (2.0/7.0)*sqrt(6.0/5.0)),-sqrt(3.0/7.0 - (2.0/7.0)*sqrt(6.0/5.0)), sqrt(3.0/7.0 - (2.0/7.0)*sqrt(6.0/5.0)),sqrt(3.0/7.0 + (2.0/7.0)*sqrt(6.0/5.0))};
const double GAUSS_WEIGHTS[] = {(18.0-sqrt(30.0))/36.0,(18.0+sqrt(30.0))/36.0,(18.0+sqrt(30.0))/36.0,(18.0-sqrt(30.0))/36.0};

const double STEP = 2*pi / NODES;
void IntegrateTime() {
    timeVal[0] = 0;
    timeDer[0] = CalcDtDa(0);
    for (int i = 0; i < NODES; i++) {
        double integ = 0.0;
        for (int j = 0; j < GAUSS_CNT; j++) {
            double node = STEP * (i + (GAUSS_NODES[j] + 1.0) * 0.5);
            double wgt = GAUSS_WEIGHTS[j] * 0.5;
            integ += wgt * CalcDtDa(node);
        }
        timeVal[i+1] = timeVal[i] + integ * STEP;
        timeDer[i+1] = CalcDtDa(STEP * (i+1));
    }
}

double InterpolateTime(double deltaAngle) {
    double param = deltaAngle * (1.0 / STEP);
    int cell = int(param);
    cell = max(cell, 0);
    cell = min(cell, NODES - 1);
    double t = param - cell;

    double ctrl[4][4];
    ctrl[0][0] = timeVal[cell+0];
    ctrl[0][3] = timeVal[cell+1];
    ctrl[0][1] = ctrl[0][0] + timeDer[cell+0] * STEP / 3.0;
    ctrl[0][2] = ctrl[0][3] - timeDer[cell+1] * STEP / 3.0;
    for (int i = 1; i <= 3; i++)
        for (int j = 0; j <= 3-i; j++)
            ctrl[i][j] = ctrl[i-1][j] * (1-t) + ctrl[i-1][j+1] * t;
    double interp = ctrl[3][0];

    return interp;
}

int q;
vector<double> timeQueries;

int main(int argc, char **argv) {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(10) << fixed;
    cin >> ostapPos.x >> ostapPos.y;
    cin >> kislaPos.x >> kislaPos.y;
    cin >> ostapVel.x >> ostapVel.y;
    cin >> kislaSpeed;
    cin >> q;
    for (int i = 0; i < q; i++) {
        double t;
        cin >> t;
        timeQueries.push_back(t);
    }

    Point startVec = kislaPos - ostapPos;
    radius = len(startVec);
    startAngle = atan2(startVec.y, startVec.x);

    IntegrateTime();
    double period = timeVal[NODES];
    Eo(period);

    for (int i = 0; i < q; i++) {
        double qt = timeQueries[i];
        int laps = int(qt / period);
        double lapRem = qt - laps * period;

        double left = 0.0;
        double right = 2 * pi;
        static const int TIMES = 60;
        for (int z = 0; z < TIMES; z++) {
            double middle = (left + right) / 2;
            if (middle == left || middle == right)
                break;
            if (InterpolateTime(middle) < lapRem)
                left = middle;
            else
                right = middle;
        }

        double polarAngle = startAngle + (left + right) * 0.5;
        Point ostapAt = ostapPos + ostapVel * qt;
        Point kislaAt = ostapAt + polar(polarAngle) * radius;
        cout << kislaAt.x << " " << kislaAt.y << "\n";
    }
    return 0;
}
