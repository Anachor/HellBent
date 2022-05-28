///Author: anachor
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;


struct PrimeSig{
    vector<int> primes;

    PrimeSig() {
        int MX = 100;
        vector<bool> isp(MX, 1);
        for (int i=2; i<MX; i++)
            if (isp[i]) {
                primes.push_back(i);
                for (int j=2*i; j<MX; j+=i)
                    isp[j] = 0;
            }
    }


    LL LIM;
    vector<pair<vector<int>, LL>> ans;
    vector<int> ps;

    void go(int idx, LL val, int mx) {
        assert(ans.size() < 100000);
        assert(idx < primes.size());

        ans.push_back({ps, val});
        int p = primes[idx];
        ps.push_back(0);

        for (int i=1; i<=mx; i++) {
            if (val > LIM/p)    break;
            ps.back()++;
            val *= p;
            go(idx+1, val, i);
        }
        ps.pop_back();
    }


    ///first = signature, second = min value with that signature
    vector<pair<vector<int>, LL>> getAllSignature(LL lim) {
        LIM = lim;
        ans.clear();
        ps.clear();
        go(0, 1, 100);
        return ans;
    }
};


/// Solves Timus 1748 - The most complex number
int main() {
    map<int, LL> mp;
    PrimeSig solver;

    for (auto pr: solver.getAllSignature(LLONG_MAX)) {
        int ans = 1;
        for (int x: pr.first)   ans *= (x+1);
        if (mp.count(ans) == 0) mp[ans] = pr.second;
        else                    mp[ans] = min(mp[ans], pr.second);
    }

    vector<pair<LL, LL>> ans;
    for (auto pr: mp) {
        while (ans.size() && ans.back().first > pr.second)     ans.pop_back();
        ans.push_back({pr.second, pr.first});
    }


    int q;
    cin>>q;

    while (q--) {
        long long x;
        cin>>x;

        int idx = upper_bound(ans.begin(), ans.end(),make_pair(x+1LL, -1LL)) - ans.begin()-1;
        cout<<ans[idx].first<<" "<<ans[idx].second<<endl;
    }
}
