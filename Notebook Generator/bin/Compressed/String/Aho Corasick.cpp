struct AC {
struct state {
  int to[ALPHA],depth,sLink,
  int par,parLet,cnt,nxt[ALPHA];
}states[N];
vector<int> suff_tree[N]; int tot_nodes;
void init() {
  for(int i = 0; i < N; i++) suff_tree[i].clear();
  tot_nodes = 1; clr(states); //careful,memset TLE
}
int add_string(string &str) {
  int cur = 1;
  for(int i = 0; i < str.size(); i++) {
    int c = str[i]-'a';
    if(!states[cur].to[c]) {
      states[cur].to[c] = ++tot_nodes;
      states[tot_nodes].par = cur;
      states[tot_nodes].depth=states[cur].depth+1;
      states[tot_nodes].parLet = c;
    }
    cur = states[cur].to[c];
  }
  return cur;
}
void push_links() {
  queue <int> qq;
  qq.push(1);
  while (!qq.empty()) {
    int node = qq.front();
    qq.pop();
    if (states[node].depth <= 1)
      states[node].sLink = 1;
    else {
      int cur = states[states[node].par].sLink;
      int parLet = states[node].parLet;
      while (cur > 1 and !states[cur].to[parLet]){
        cur = states[cur].sLink;
      }
      if (states[cur].to[parLet]) {
        cur = states[cur].to[parLet];
      }
      states[node].sLink = cur;
    }
    if(node!=1)
      suff_tree[states[node].sLink].pb(node);
    for (int i = 0 ; i < ALPHA; i++) {
      if(states[node].to[i])
        qq.push(states[node].to[i]);
    }
  }
}
int next_state(int from, int c) {
  if(states[from].nxt[c])
    return states[from].nxt[c];
  int cur = from;
  while(cur>1&&!states[cur].to[c])
    cur=states[cur].sLink;
  if(states[cur].to[c]) cur = states[cur].to[c];
  return states[from].nxt[c] = cur;
}
void dfs(int u) {
  for(int v : suff_tree[u]) {
    dfs(v); states[u].cnt += states[v].cnt;
  }
}
}aho;
