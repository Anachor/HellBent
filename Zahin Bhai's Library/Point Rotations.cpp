#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct Point{
    double x, y;

    Point(){
    }

    Point(double xi, double yi){
        x = xi, y = yi;
    }
};

double dis(struct Point A, struct Point B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt((x * x) + (y * y));
}

/// Rotate P anti-clockwise around the centre point by theta (theta in degrees)
struct Point rotate(struct Point centre, struct Point P, double theta){
    P.x -= centre.x, P.y -= centre.y;
    theta = (theta * 2.0 * acos(0.0)) / 180.0;

    double s = sin(theta), c = cos(theta);
    double x = (P.x * c) - (P.y * s);
    double y = (P.x * s) + (P.y * c);
    return Point(x + centre.x, y + centre.y);
}

/// Clockwise rotation from vector A to vector B
double thetaX(struct Point A, struct Point B){
    double dot = (B.x * A.x) + (B.y * A.y);
    double det = (B.x * A.y) - (B.y * A.x);
    double theta = (atan2(det, dot) * 180.0) / (2.0 * acos(0.0));
    if (theta < 0) theta += 360.0;
    return theta;
}

int main(){

}
