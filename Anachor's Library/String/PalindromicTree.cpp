///Source: Ashiq vai(?)

#include<bits/stdc++.h>
using namespace std;

/// Palindromic Tree code tested on 2018 KAIST RUN Spring QueryreuQ
/// https://codeforces.com/gym/101806/problem/Q

const int MAXN = 1e5+7; ///set to at least max length of a string + 3
namespace PalTree {
    struct node {
        int len;        ///length of the palindrome of this node
        int sufflink;   ///largest suffix palindrome of this node
        int chain;      ///# of non-empty nodes on the chain of suffix links
        int next[26];   ///next[c] is the palindrome by adding c to both sides
    } tree[MAXN];

    int size;   /// number of nodes currently in Palindromic Tree
    int suff;   /// max suffix palindrome of the currently processed prefix
    string s;   /// the string we will built our Palindromic Tree on
    bool addLetter(int pos) {
        int cur = suff, curlen = 0, let = s[pos]-'a';
        while (true) {
            curlen = tree[cur].len;
            if (pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) break;
            cur = tree[cur].sufflink;
        }
        if (tree[cur].next[let]) {
            suff = tree[cur].next[let];
            return false;
        }
        ///create new node
        suff = ++size;
        tree[cur].next[let] = size;
        tree[size].len = tree[cur].len+2;
        if (tree[size].len == 1) {
            tree[size].sufflink = 2;
            tree[size].chain = 1;
            return true;
        }
        while (true) {
            cur = tree[cur].sufflink;
            curlen = tree[cur].len;
            if (pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]) {
                tree[size].sufflink = tree[cur].next[let];
                break;
            }
        }
        tree[size].chain = 1+tree[tree[size].sufflink].chain;
        return true;
    }
    void initTree() {
        memset(tree, 0, sizeof tree);   ///CAREFUL: SEVERAL TESTCASES
        size = 2;
        suff = 2;
        ///1: root with len -1; 2: root with len 0
        tree[1].len = -1; tree[1].sufflink = 1;
        tree[2].len = 0; tree[2].sufflink = 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    string operations;
    cin >> operations;

    PalTree::initTree();
    vector< int >subs;
    vector< int >suffs;
    subs.push_back(0);
    suffs.push_back(PalTree::suff);

    for (char c : operations) {
        if (c == '-') {
            subs.pop_back();
            suffs.pop_back();
            PalTree::s.pop_back();
            PalTree::suff = suffs.back();
        } else {
            PalTree::s += c;
            PalTree::addLetter(PalTree::s.size()-1);
            suffs.push_back(PalTree::suff);
            subs.push_back(subs.back()+PalTree::tree[PalTree::suff].chain);
        }
        cout << subs.back() << " ";
    }

	return 0;
}


