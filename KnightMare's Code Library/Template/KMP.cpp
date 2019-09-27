#include<bits/stdc++.h>
using namespace std;

/// builds the prefix automaton in O(N*alphabet)
vector< vector< int > >automaton;
void buildAutomaton(const string& s)
{
    int n = s.size(), k = 0;

    vector< int >zer(26, 0);
    for (int i = 0; i <= n; i++) automaton.push_back(zer);

    automaton[0][s[0]-'a'] = 1;
    for (int i = 1; i <= n; i++) {
        automaton[i] = automaton[k];

        if (i < n) {
            automaton[i][s[i]-'a'] = i+1;
            k = automaton[k][s[i]-'a'];
        }
    }
}

/// everything 1-indexed
/// v[i] = 0 -> empty string matched
/// v[i] = k -> prefix s[0..(k-1)] matched
vector<int> prefixFunction(const string& s)
{
    int n = s.size(), k = 0;
    
    vector< int >v(n+1);
    v[1] = 0;

    for (int i = 2; i <= n; i++) {
        while (k > 0 && s[k]!=s[i-1]) k = v[k];
        if (s[k]==s[i-1]) k++;
        v[i] = k;
    }
    return v;
}

int kmpMatcher(const string& text, const string& pattern)
{
    vector<int> pi = prefixFunction(pattern);
    int matchCount = 0, k = 0;

    for (int i = 0; i < text.size(); i++) {
        while (k > 0 && text[i]!=pattern[k]) k = pi[k];
        if (text[i]==pattern[k]) k++;

        if (k==pattern.size()) {    /// full pattern match found
            matchCount++;
            k = pi[k];
        }
    }
    return matchCount;
}

/// LightOJ 1255 - Substring Frequency
/// You are given two non-empty strings A and B, both
/// contain lower case English alphabets. You have to
/// find the number of times B occurs as a substring of A.

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti = 1; ti <= t; ti++) {
        string A, B;
        cin >> A >> B;
        cout << "Case " << ti << ": " <<  kmpMatcher(A, B) << endl;
    }
    return 0;
}
