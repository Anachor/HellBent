#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

vector <int> period(char* str){
    int i, l = 0, r = 0, n = strlen(str);
    vector <int> Z(n + 1, 0);

    for (i = 1; i < n; i++){
        Z[i] = max(0, min(Z[i - l], r - i));
        while (str[i + Z[i]] && str[Z[i]] == str[i + Z[i]]) Z[i]++;
        if ((i + Z[i]) > r) l = i, r = i + Z[i];
    }
    Z[0] = n;

    vector <int> v;
    for (l = 1; l <= n; l++){
        if ((n % l) == 0){
            for (i = 0; i < n && Z[i] >= l; i += l){}
            if (i == n) v.push_back(l);
        }
    }
    return v;
}

int main(){
    vector <int> v = period("abaabaabaaba");
    for (int i = 0; i < v.size(); i++) dbg(v[i]);
    return 0;
}
