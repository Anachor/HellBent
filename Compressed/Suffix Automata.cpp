// 0 is the root-(null string)
//First Occ of each state:
// new : firstpos(cur)=len(cur)-1
// cloned : firstpos(clone) = firstpos(q)
const int AL = 26;
namespace SuffixAutomata {
  vector<vector<int>> to, go;
  vector<int> link, len; int n, sz, cur;
  void add(int c) {
    int p = cur;
    cur = ++sz; len[cur] = len[p] + 1;
    while(!to[p][c])
      to[p][c] = cur, p = link[p];
    if(to[p][c] == cur) {
      link[cur] = 0; return;
    }
    int q = to[p][c];
    if (len[q] == len[p] + 1) {
        link[cur] = q; return;
    }
    int cl = ++sz;to[cl] = to[q];
    link[cl] = link[q]; len[cl]=len[p]+1;
    link[cur] = link[q] = cl;
    while (to[p][c] == q)
        to[p][c] = cl, p = link[p];
  }
  int advance(int st, int c) {
    if(go[st][c] != -1) return go[st][c];
    int nst;
    if(to[st][c]) nst = to[st][c];
    else if(st) nst=advance(link[st],c);
    else nst = st;
    return go[st][c] = nst;
  }
  void build(string &s) {
    cur = sz = 0; n = s.size();
    to.assign(2*n+1,vector<int>(AL,0));
    go.assign(2*n+1,vector<int> (AL,-1));
    link.assign(2*n+1,0);len=link;
    for(int i=0;i<n;i++) add(s[i]-'a');
  }
}