//finds x/y with min y st: L <= (x/y) < R
pair<LL,LL>solve(LD L, LD R){
  pair<LL, LL> l(0, 1), r(1, 1);
  if(L==0.0) return l; // corner case
  while(true) {
    pair<int, int> m(l.x+r.x, l.y+r.y);
    if(m.x<L*m.y){ // move to the right
      LL kl=1, kr=1;
      while(l.x+kr*r.x <= L*(l.y+kr*r.y)) kr*=2;
      while(kl!=kr){
        LL km = (kl+kr)/2;
        if(l.x+km*r.x < L*(l.y+km*r.y)) kl=km+1;
        else kr=km;
      }
      l={l.x+(kl-1)*r.x,l.y+(kl-1)*r.y};
    }
    else if(m.x>=R*m.y){//move to left
      LL kl=1, kr=1;
      while(r.x+kr*l.x>=R*(r.y+kr*l.y)) kr*=2;
      while(kl!=kr){
        LL km = (kl+kr)/2;
        if(r.x+km*l.x>=R*(r.y+km*l.y))  kl = km+1;
        else kr = km;
      }
      r={r.x+(kl-1)*l.x,r.y+(kl-1)*l.y};
    }
    else return m;
  }
}
