///Author: anachor
#include<bits/stdc++.h>
using namespace std;

const int M = 1e9+7;
typedef long long LL;

LL mod(LL x) {
    LL ans = x%M;
    if (ans < 0)    ans += M;
    return ans;
}

template <LL X>
struct SqrtField {
    LL a, b, c;     /// (a + b*sqrt(X))/c;
    SqrtField(LL A=0, LL B=0, LL C=1) : a(A), b(B), c(C) {}


    SqrtField operator+(const SqrtField &y) {
        return SqrtField(mod(a*y.c + y.a*c), mod(b*y.c + y.b*c), mod(c*y.c));
    }

    SqrtField operator-(const SqrtField &y) {
        return SqrtField(mod(a*y.c - y.a*c), mod(b*y.c - y.b*c), mod(c*y.c));
    }

    SqrtField operator*(const SqrtField &y) {
        return SqrtField(mod(a*y.a + X*y.b*b), mod(a*y.b + b*y.a), mod(c*y.c));
    }

    SqrtField operator/(const SqrtField &y) {
        LL A = mod(a*y.a - X*y.b*b);
        LL B = mod(b*y.a - a*y.b);
        LL C = mod(y.a*y.a - X*y.b*y.b);
        A = mod(A*y.c);
        B = mod(B*y.c);
        C = mod(C*c);
        return SqrtField(A,B,C);
    }
};

template<LL X>
ostream& operator<<(ostream &os, const SqrtField<X> &x) {
    return os<<"("<<x.a<<"+"<<x.b<<"V"<<X<<")/"<<x.c;
}

int main() {
    SqrtField<2> c(5);          ///5
    SqrtField<2> b(0, 1);       ///3 sqrt(2)
    SqrtField<2> a(3,7,2);      ///(3+7*sqrt(2))/2

    cout<<a+b<<" "<<a-b<<" "<<a*b<<" "<<a/c<<endl;
    cout<<a*2<<" "<<a/2<<" "<<a+2<<" "<<a-1<<endl;
}
