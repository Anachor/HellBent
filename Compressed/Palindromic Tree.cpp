struct node {int next[26],len,slink;};
char str[N]; node tree[N]; int sz, suff;
bool addLetter(int pos) {
  int cur=suff,curlen=0,let=str[pos]-'a';
  while (true) {
    curlen = tree[cur].len;
    if(pos - 1 - curlen >= 0 &&
      str[pos-1-curlen]==str[pos]) break;
    cur = tree[cur].slink;
  }
  if(tree[cur].next[let]){
    suff=tree[cur].next[let]; return 0;
  }
  suff = ++sz; tree[cur].next[let] = sz;
  tree[sz].len = tree[cur].len + 2;
  if (tree[sz].len == 1) {
    tree[sz].slink = 2; return true;
  }
  while (true) {
    cur = tree[cur].slink;
    curlen = tree[cur].len;
    if(pos-1-curlen >= 0 &&
       str[pos-1-curlen]==str[pos]) {
      tree[sz].slink=tree[cur].next[let];
      break;
    }
  }
  return true;
}
void initTree() {
    memset (tree , 0 , sizeof tree) ;
    sz = 2; suff = 2;
    tree[1].len = -1; tree[1].slink = 1;
    tree[2].len = 0; tree[2].slink = 1;
}