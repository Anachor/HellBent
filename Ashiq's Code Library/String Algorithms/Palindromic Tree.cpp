/// Palindromic Tree
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

struct node {
    int next[26] , len , sufflink , num ;
    /// len : length of the palindrome in node
    /// num : depth of the suffix link
};

int len;
char str[N];
node tree[N];
int sz;            /// node 1 - root with len -1, node 2 - root with len 0
int suff;           /// max suffix palindrome
long long ans;

bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = str[pos] - 'a';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && str[pos - 1 - curlen] == str[pos])
            break;
        cur = tree[cur].sufflink;
    }
    if (tree[cur].next[let]) {
        suff = tree[cur].next[let];
        return false;
    }

    suff = ++sz;
    tree[sz].len = tree[cur].len + 2;
    tree[cur].next[let] = sz;

    if (tree[sz].len == 1) {
        tree[sz].sufflink = 2;
        tree[sz].num = 1;
        return true;
    }

    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && str[pos - 1 - curlen] == str[pos]) {
            tree[sz].sufflink = tree[cur].next[let];
            break;
        }
    }

    tree[sz].num = 1 + tree[tree[sz].sufflink].num;

    return true;
}

void initTree() {
    memset (tree , 0 , sizeof tree) ;
    sz = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
}

int main() {
    scanf ("%s" , &str) ;
    len = strlen(str);
    initTree();
    for (int i = 0; i < len; i++) {
        ans += addLetter(i);
        printf ("%d " , ans) ;
    }

    return 0;
}
