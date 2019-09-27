#include <bits/stdtr1c++.h>

#define LET 26
#define MAX 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

char str[MAX];

namespace ptree{ /// hash = 232659
    char S[MAX];
    int idx, cur, slen, lps, len[MAX], link[MAX], counter[MAX], trie[MAX][LET];
    /// len[i] = length of the palindrome at node i, link[i] = suffix link of node i
    /// link[i] = v, where v is the node representing the longest proper suffix-palindrome of i
    /// trie[i][c] = node where the palindrome is c + palindrome at i + c, e.g, i = "aba", c = 'd', trie[i][c] = "dabad"

    void init(){
        cur = 0, slen = 1, lps = 0, idx = 2;
        clr(S), clr(len), clr(link), clr(trie), clr(counter);

        S[0] = -1;
        link[0] = 1, len[0] = 0;
        link[1] = 0, len[1] = -1;
    }

    inline int nextlink(int cur){ /// Matching similar to fail function as in KMP/Aho-corasick
        while (S[slen - len[cur] - 2] != S[slen - 1]) cur = link[cur];
        return cur;
    }

    /// Returns true if a new distinct palindromic substring appears after adding current character
    inline bool insert(char ch){
        S[slen++] = ch, cur = nextlink(cur);
        int c = ch - 'a', flag = trie[cur][c]; /// Change here if any non-lower case character can occur

        if (!flag){
            len[idx] = len[cur] + 2;
            link[idx] = trie[nextlink(link[cur])][c];
            trie[cur][c] = idx++;
        }

        cur = trie[cur][c];
        counter[cur]++; /// count of palindromic substring cur in the string
        lps = max(lps, len[cur]); /// Update the longest palindromic substring after adding this character
        return !flag;
    }

    /// IMPORTANT: do this in main to update count of all palindromic nodes
    for (int i = idx; i >= 0; i--) counter[link[i]] += counter[i];
}

int main(){

}
