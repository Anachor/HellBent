#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct Point{
    long long x, y;

    Point(){
    }

    Point(long long xi, long long yi){
        x = xi, y = yi;
    }
};

struct Segment{
    struct Point P1, P2;

    Segment(){
    }

    Segment(struct Point P1i, struct Point P2i){
        P1 = P1i, P2 = P2i;
    }
};

/// Returns 0 if ABC is collinear, positive if ABC is a left turn, negative if ABC is a right turn
long long ccw(struct Point A, struct Point B, struct Point C){
    return ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y));
}

/// Returns true if Point P lies on the Segment (both end-points inclusive)
bool PointOnSeg(struct Segment S, struct Point P){
    long long x = P.x, y = P.y, x1 = S.P1.x, y1 = S.P1.y, x2 = S.P2.x, y2 = S.P2.y;
    long long a = x - x1, b = y - y1, c = x2 - x1, d = y2 - y1, dot = (a * c) + (b * d), len = (c * c) + (d * d);

    if (x1 == x2 && y1 == y2) return (x1 == x && y1 == y);
    if (dot < 0 || dot > len) return false;
    return ((((x1 * len) + (dot * c)) == (x * len)) && (((y1 * len) + (dot * d)) == (y * len)));
}

struct Polygon{
    #define CLOCKWISE 11230926
    #define ANTICLOCK 37281927

    int n; /// n should be greater than 1
    struct Point ar[MAX]; /// Points in polygon in clockwise order

    Polygon(){
    }

    /// Points in T are either in anti-clockwise or clockwise order
    Polygon(int ni, struct Point* T, int flag){
        n = ni;
        for (int i = 0; i < n; i++){
            if (flag == CLOCKWISE) ar[i] = T[i];
            else ar[i] = T[n - i - 1];
        }
    }

    /// strictly should be true if P needs to be strictly contained in the polygon
    bool contains(struct Point P, bool strictly){
        int mid, low = 1, high = n - 1, idx = 1;

        while (low <= high){
            mid = (low + high) >> 1;
            if (ccw(ar[0], P, ar[mid]) > 0) low = mid + 1;
            else idx = mid, high = mid - 1;
        }

        if (!strictly && PointOnSeg(Segment(ar[0], ar[n - 1]), P)) return true;
        if (!strictly && PointOnSeg(Segment(ar[idx], ar[idx - 1]), P)) return true;
        if (idx == 1 || ccw(ar[0], P, ar[n - 1]) == 0) return false;
        return (ccw(ar[idx], P, ar[idx - 1]) < 0);
    }
};

int main(){
}
