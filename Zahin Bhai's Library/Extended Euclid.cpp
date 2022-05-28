#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Bezout's identity, ax + by = gcd(a,b)

int extended_gcd(int a, int b, int& x, int& y){

    if (!b){
        y = 0, x = 1;
        return a;
    }

    int g = extended_gcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}

/// Linear diophantine equation, ax + by = c

void diophantine(int a, int b, int c, int& x, int& y){
    int g = extended_gcd(a, b, x, y);
    assert((c % g) == 0); /// c must be a multiply of g

    c /= g;
    x *= c, y *= c;
}

int main(){
}
