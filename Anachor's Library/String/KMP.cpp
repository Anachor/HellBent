/**
Knuth Morris Pratt String Matching
Complexity: build - O(n)
            match - O(n+m)
            prefix automaton - O(n*alphabet)

source: anachor, solaimanope (prefix automaton)
*/

#include<bits/stdc++.h>
using namespace std;

struct KMP {
    string s;
    int n;
    vector<int> fail;

    KMP(const string &ss) {
        s = ss;
        n = s.size();
        fail.assign(n+1, 0);

        fail[0] = fail[1] = 0;

        for (int i=2; i<=n; i++) {
            fail[i] = (s[i-1] == s[0]);
            for (int j = fail[i-1]; j>0; j = fail[j])
                if (s[j] == s[i-1]) {
                    fail[i] = j+1;
                    break;
                }
        }
    }

    int match(string t) { ///No of matches
        int cur = 0, ans = 0;
        for (int i=0; i<t.size();) {
            if (t[i] == s[cur]) cur++, i++;
            else if (cur==0) i++;
            else cur = fail[cur];
            if (cur==n) ans++, cur = fail[cur];
        }
        return ans;
    }

    vector<vector<int>> prefixAutomaton() {
        vector<vector<int>> automaton(n+1, vector<int> (26, 0));
        automaton[0][s[0]-'a'] = 1;
        for (int i=1, k=0; i<=n; i++) {
            automaton[i] = automaton[k];
            if (i < n) {
                automaton[i][s[i]-'a'] = i+1;
                k = automaton[k][s[i]-'a'];
            }
        }
        return automaton;
    }
};

///Solves LightOJ 1255 - substring frequency
///Basically, given a text and a pattern find
///how many times the pattern appears in text

const int N = 1e6+7;
char buffer[N];
int main()
{
    int t;
    scanf("%d", &t);

    for (int cs=1; cs<=t; ++cs) {
        string a, b;
        scanf("%s", buffer); a=buffer;
        scanf("%s", buffer); b=buffer;
        KMP matcher(b);
        printf("Case %d: %d\n", cs, matcher.match(a));
    }
}
