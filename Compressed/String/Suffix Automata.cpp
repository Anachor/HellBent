//# No of Occ of each state:init each state(except
//the clones) with cnt[state]=1, loop dec order of
//len[state],and do: cnt[link[state]]+=cnt[state]
//# First Occ of each state:
// for new state: firstpos(cur) = len(cur)-1
// for cloned state: firstpos(clone) = firstpos(q)
const int ALPHA = 26;
namespace SuffixAutomata {
vector<vector<int>> to, nstate;
vector<int> link, len;
int n, sz, cur;
void add(int c) {
  int p = cur;
  cur = ++sz; len[cur] = len[p] + 1;
  while (to[p][c]==0) {to[p][c]=cur; p = link[p];}
  if (to[p][c] == cur) {link[cur] = 0;return;}
  int q = to[p][c];
  if (len[q] == len[p] + 1) link[cur] = q;return;
  int cl = ++sz;
  to[cl] = to[q]; link[cl] = link[q];
  len[cl] = len[p] + 1; link[cur] = link[q] = cl;
  while (to[p][c] == q) {to[p][c]=cl; p=link[p];}
}
int advance(int state, int c) {
  if(nstate[state][c]!=-1)return nstate[state][c];
  int nstate;
  if(to[state][c]) nstate = to[state][c];
  else if(state) nstate = advance(link[state], c);
  else nstate = state;
  return nstate[state][c] = nstate;
}
void build(string &s) {
  cur = sz = 0; n = s.size();
  to.assign(2*n+1, vector<int> (ALPHA, 0));
  nstate.assign(2*n+1, vector<int> (ALPHA, -1));
  link.assign(2*n+1, 0); len.assign(2*n+1, 0);
  for(int i = 0; i < n; i++) add(s[i]-'a');
}
}
