#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct Point {
    long long x, y; /// x*x or y*y should fit long long because of cross() function

    Point(){}
    Point(long long a, long long b){
        x = a, y = b;
    }

    inline bool operator < (const Point &p) const {
        return ((x < p.x) || (x == p.x && y < p.y));
    }
};

long long cross(const Point &O, const Point &A, const Point &B){
    return ((A.x - O.x) * (B.y - O.y)) - ((A.y - O.y) * (B.x - O.x));
}

bool isConvex(vector <Point> P){ /// Polygon P convex or not, P is given in clock-wise of anti-clockwise order
    int n = P.size();
    ///sort(P.begin(), P.end());
    if (n <= 2) return false; /// Line or point is not convex

    n++, P.push_back(P[0]); /// Last point = first point
    bool flag = (cross(P[0], P[1], P[2]) > 0);
    for (int i = 1; (i + 1) < n; i++){
        bool cmp = (cross(P[i], P[i + 1], (i + 2) == n ? P[1] : P[i + 2]) > 0);
        if (cmp ^ flag) return false;
    }

    return true;
}

/// Convex hull using the monotone chain algorithm
vector <Point> convex_hull (vector<Point> P){
    int i, t, k = 0, n = P.size();
    vector<Point> H(n << 1);
    sort(P.begin(), P.end()); /// Can be converted to O(n) using radix sort

    for (i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) < 0) k--;
        H[k++] = P[i];
    }
    for (i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) < 0) k--;
        H[k++] = P[i];
    }

    H.resize(k - 1); /// The last point is the same as the first in this implementation
    return H;
}

int main(){

}
