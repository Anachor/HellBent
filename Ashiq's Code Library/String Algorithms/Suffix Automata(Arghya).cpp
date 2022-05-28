class SuffixAutomaton{
public:
  struct state{
      int edge[27] , len , link , cnt[2] ;
  };

  state *st ; int sz , last ;
  SuffixAutomaton( string &s , int k ) {
    int l = s.length() ; int i , j ;
    st = new state[l*2] ;
    st[0].link = -1  ; st[0].len = 0 ; sz = 1 ; last = 0 ;
    for(i=0 ; i<27 ; i++) st[0].edge[i] = -1 ;

  for(i=0 ; i<l ; i++) {
    int cur = sz++ ;
    for(j=0 ; j<27 ; j++) st[cur].edge[j] = -1 ;
    st[cur].len = st[last].len+1 ;
    int p = last , c = s[i]-'a' ;
    while( p!=-1 && st[p].edge[c] == -1 ) {
      st[p].edge[c] = cur ;
      p = st[p].link ;
    }
    if( p == -1 ) st[cur].link = 0 ;
    else{
      int q = st[p].edge[c] ;
      if( st[p].len+1 == st[ q ].len  ) st[cur].link = q ;
      else{
        int clone = sz++ ;
        for(j=0;j<27;j++) st[clone].edge[j] = st[q].edge[j] ;
        st[clone].len = st[p].len+1 ;
        st[clone].link = st[q].link ;
        while( p!=-1 && st[p].edge[c] == q ) {
          st[p].edge[c] = clone ; p = st[p].link ;
        }
        st[q].link = st[cur].link = clone ;
      }
    }
    last = cur ;
  }
}
  ~SuffixAutomaton() {
    delete []st ;
  }
};
