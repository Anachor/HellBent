#include <bits/stdc++.h>
using namespace std ;

struct Point {
    int x , y , z;
    Point() {}
    Point(int x_,int y_,int z_) {x=x_,y=y_,z=z_;}
    Point operator + (const Point &p) {
        return {x+p.x,y+p.y,z+p.z} ;
    }
    Point operator - (const Point &p) {
        return {x-p.x,y-p.y,z-p.z} ;
    }
    Point operator * (const int &t) {
        return {x*t,y*t,z*t} ;
    }
    int operator * (const Point &p) {
        return x*p.x + y*p.y + z*p.z;
    }
    Point operator ^ (const Point &p) {
        return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y - y*p.x);
    }
};

int main() {
    //freopen ("in.txt","r",stdin);
    int n; cin >> n;
    vector <Point> P(n);
    vector <double> prob(n);
    double cc = 1.0;
    for(int i = 0 ; i < n ; i++) {
        cin >> prob[i] ;
        cc *= (1.0-prob[i]);
        cin >> P[i].x >> P[i].y >> P[i].z ;
    }
    double f = 0;
    double ans = 0;
    double chance = 1.0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1 ; j < n; j++) {
            for(int k = j+1; k < n; k++) {
                Point norm = (P[j]-P[i])^(P[k]-P[i]);
                double probUp = 1.0 , probDown = 1.0;
                double just = prob[i]*prob[j]*prob[k];
                for(int l = 0; l < n; l++) {
                    if (l == i or l == j or l == k) continue;
                    just *= (1.0-prob[l]);
                    if (norm*(P[l]-P[i]) > 0) {
                        probUp *= (1.0-prob[l]);
                    }
                    else {
                        probDown *= (1.0-prob[l]);
                    }
                }
                double cur = prob[i]*prob[j]*prob[k]*(probUp + probDown - 2.0*probUp*probDown);
                f += cur;
                ans += 3.0*just;
                chance -= just;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            double just = prob[i]*prob[j];
            for(int k = 0; k < n; k++) {
                if (k == i or k == j) continue;
                just *= (1.0-prob[k]);
            }
            ans += 2.0*just;
            chance -= just;
        }
    }
    for(int i = 0; i < n; i++) {
        double just = prob[i];
        for(int j = 0; j < n; j++) {
            if (j == i) continue;
            just *= (1.0-prob[j]);
        }
        ans += just;
        chance -= just;
    }
    chance -= cc;

    double e = 1.5*f ;
    ans += e - f + 2.0*chance ;
    cout << setprecision(12) << ans << endl;
}
