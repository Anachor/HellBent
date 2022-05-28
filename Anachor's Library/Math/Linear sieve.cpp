///Source: cp-algo
#include<bits/stdc++.h>
using namespace std;

const int N = 1e8;
int lp[N];
vector<int> pr;

void pre() {
    for (int i=2; i<N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

int main()
{
    pre();
    cout<<pr.size()<<endl;
}
