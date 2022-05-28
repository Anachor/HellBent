#include <bits/stdtr1c++.h>

#define sqr(x) ((x) * (x))
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct Point{
    double x, y;

    Point() {
    }

    Point(double a, double b){
        x = a, y = b;
    }
};

struct Circle{
    Point centre;
    double radius;

    Circle(){
    }

    Circle(double a, double b, double c){
        radius = c;
        centre = Point(a, b);
    }

    Circle(struct Point c, double r){
        centre = c;
        radius = r;
    }
};

const double pi = 2.0 * acos(0.0);

double dis(Point A, Point B){
    double x = (A.x - B.x);
    double y = (A.y - B.y);
    double res = sqrt((x * x) + (y * y));
    return res;
}

double Area(Circle C){
    return (pi * sqr(C.radius));
}

double intersection(Circle A, Circle B){
    double x = A.radius + B.radius;
    double y = dis(A.centre, B.centre);
    if ((fabs(x - y) <= 1e-8) || (y > x)) return 0.0;

    double c = y;
    double x0 = A.centre.x, y0 = A.centre.y, r0 = A.radius;
    double x1 = B.centre.x, y1 = B.centre.y, r1 = B.radius;

    x = (sqr(r1) + sqr(c) - sqr(r0)) / (2.0 * r1 * c);
    double CBD = acos(x) * 2.0;
    y = (sqr(r0) + sqr(c) - sqr(r1)) / (2.0 * r0 * c);
    double CAD = acos(y) * 2.0;


    double res = (0.5 * CBD * sqr(r1)) - (0.5 * sqr(r1) * sin(CBD)) + (0.5 * CAD * sqr(r0)) - (0.5 * sqr(r0) * sin(CAD));
    return res;
}

bool Inside(Circle A, Circle B){
    double x = dis(A.centre, B.centre) + B.radius;
    if ((fabs(x - A.radius) <= 1e-8) || (x < A.radius)) return true;
    return false;
}

int main(){
    double res;
    int T = 0, t, i, a, b, c;

    scanf("%d", &t);
    while (t--){
        scanf("%d %d %d", &a, &b, &c);
        Circle grass = Circle(a, b, c);
        scanf("%d %d %d", &a, &b, &c);
        Circle wolf = Circle(a, b, c);

        if (Inside(wolf, grass)) res = 0.0;
        else if (Inside(grass, wolf)) res = Area(grass) - Area(wolf);
        else{
            res = Area(grass) - intersection(grass, wolf);
        }

        printf("Case #%d: %0.12f\n", ++T, res + 1e-15);
    }
    return 0;
}
