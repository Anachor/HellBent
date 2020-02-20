struct Point {
  LD x,y ;
  LD operator*(const Point &a)const {
    return x*a.y-y*a.x;}
  LD operator/(const Point &a)const {
    return sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y));}
}po[N];
LD r[N];
int sgn(LD x) {return fabs(x)<EPS?0:(x>0.0?1:-1);}
pair<LD,bool> ARG[2*N] ;
LD cir_union(Point c[],LD r[],int n) {
  LD sum = 0.0 , sum1 = 0.0 ,d,p1,p2,p3 ;
  for(int i = 0 ; i < n ; i++) {
    bool f = 1 ;
    for(int j = 0 ; f&&j<n ; j++)
      if(i!=j && sgn(r[j]-r[i]-c[i]/c[j])!=-1)f=0;
    if(!f) swap(r[i],r[--n]),swap(c[i--],c[n]);
  }
  for(int i = 0; i < n; i++) {
      int k = 0, cnt = 0;
      for(int j = 0; j < n; j++) {
        if(i!=j&&sgn((d=c[i]/c[j])-r[i]-r[j])<=0){
          p3=acos((r[i]*r[i]+d*d-r[j]*r[j])/
                                    (2.0*r[i]*d));
          p2=atan2(c[j].y-c[i].y,c[j].x-c[i].x);
          p1 = p2-p3; p2 = p2+p3;
          if(sgn(p1+PI)==-1) p1+=2*PI,cnt++;
          if(sgn(p2-PI)==1) p2-=2*PI,cnt++;
          ARG[k++] = make_pair(p1,0);
          ARG[k++] = make_pair(p2,1);
        }
      }
      if(k) {
        sort(ARG,ARG+k) ;
        p1 = ARG[k-1].first-2*PI;
        p3 = r[i]*r[i] ;
        for(int j = 0 ; j < k ; j++) {
          p2 = ARG[j].first;
          if(cnt==0) {
            sum+=(p2-p1-sin(p2-p1))*p3 ;
            sum1+=(c[i]+Point(cos(p1),sin(p1))*
                    r[i])*(c[i]+
                    Point(cos(p2),sin(p2))*r[i]);
          }
          p1 = p2;
          ARG[j].second ? cnt--:cnt++;
        }
      }
      else sum += 2*PI*r[i]*r[i];
  }
  return (sum+fabs(sum1))*0.5 ;
}