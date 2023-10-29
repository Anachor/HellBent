///Author: anachor
#include<bits/stdc++.h>
using namespace std;


template <int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const {
    modint<MOD> x = *this, y = 1;
    for (; k; k >>= 1) {
      if (k & 1) y *= x;
      x *= x;
    }
    return y;
  }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }


typedef long long LL;
template <typename T, int X>
struct SqrtField {
    T a, b;     /// (a + b*sqrt(X))/c;
    SqrtField(T A=0, T B=0) : a(A), b(B) {}

    SqrtField operator+(const SqrtField &y) const {
        return SqrtField(a+y.a, b+y.b);
    }

    SqrtField operator-(const SqrtField &y) const {
        return SqrtField(a-y.a, b-y.b);
    }

    SqrtField operator*(const SqrtField &y) const {
        return SqrtField(a*y.a + T(X)*y.b*b, a*y.b + b*y.a);
    }

    SqrtField inv() const {
        auto norm = a*a - T(X)*b*b;
        return SqrtField(a/norm, -b/norm);
    }

    SqrtField operator/(const SqrtField &y) const {
        return *this*y.inv();
    }

    SqrtField pow(uint64_t p) const{
        if (p == 0) return T(1);
        auto ans = pow(p/2);
        ans = ans * ans;
        if (p%2)    ans = ans * *this;
        return ans;
    }
};
template<typename T, int X>
ostream& operator<<(ostream &os, const SqrtField<T, X> &x) {
    return os<<x.a<<"+"<<x.b<<"<"<<X<<">";
}

const int M = 1e9+7;
typedef  modint<M> mint;
typedef SqrtField<mint, 5> T;
int main() {
    T a = T(1, 1)/mint(2), b = T(1, -1)/mint(2), rt5 = T(0, 1);
    cout<<a<<endl;
    for (int i=0; i<=10; i++) {
        cout<<(a.pow(i)-b.pow(i))/rt5<<endl;
    }
}

