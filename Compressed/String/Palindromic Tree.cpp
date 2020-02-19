struct node { int next[26] , len , sufflink;};
int len, sz, suff; char str[N]; node tree[N];
bool addLetter(int pos) {
  int cur = suff, curlen = 0, let = str[pos]-'a';
  while (true) {
    curlen = tree[cur].len;
    if (pos-curlen>=1&&str[pos-1-curlen]==str[pos])
      break;
    cur = tree[cur].sufflink;
  }
  if (tree[cur].next[let]) {
    suff = tree[cur].next[let]; return false;
  }
  suff = ++sz; tree[sz].len = tree[cur].len + 2;
  tree[cur].next[let] = sz;
  if (tree[sz].len==1){
    tree[sz].sufflink = 2; return 1;
  }
  while (true) {
    cur=tree[cur].sufflink; curlen=tree[cur].len;
    if(pos-curlen>=1&&str[pos-1-curlen]==str[pos]){
      tree[sz].sufflink=tree[cur].next[let];break;
    }
  }
  return true;
}
void initTree() {
  memset (tree, 0, sizeof tree); sz = 2; suff = 2;
  tree[1].len = -1; tree[1].sufflink = 1;
  tree[2].len = 0; tree[2].sufflink = 1;
}
