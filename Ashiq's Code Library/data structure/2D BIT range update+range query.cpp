const int mx = 1002,my = 1002;
long long bit[4][mx][my];
void update( int x, int y, int val, int i ) {
    int y1;
    while( x<=mx ) {
        y1=y;
        while( y1<=my ) {
            bit[i][x][y1] += val;
            y1 += (y1&-y1);
        }
        x += (x&-x);
    }
}
long long query( int x, int y, int i ) {
    long long ans=0; int y1;
    while( x>0 ) {
        y1 = y;
        while( y1>0 ) {
            ans += bit[i][x][y1];
            y1 -= (y1&-y1);
        }
        x -= (x&-x);
    }
    return ans;
}
// add value k from (x1,y1) to (x2,y2) inclusive
void add( int x1, int y1, int x2, int y2, int k )
{
    update(x1,y1,k,0);
    update(x1,y2+1,-k,0);
    update(x2+1,y1,-k,0);
    update(x2+1,y2+1,k,0);
    update(x1,y1,k*(1-y1),1);
    update(x1,y2+1,k*y2,1);
    update(x2+1,y1,k*(y1-1),1);
    update(x2+1,y2+1,-y2*k,1);
    update(x1,y1,k*(1-x1),2);
    update(x1,y2+1,k*(x1-1),2);
    update(x2+1,y1,k*x2,2);
    update(x2+1,y2+1,-x2*k,2);
    update(x1,y1,(x1-1)*(y1-1)*k,3);
    update(x1,y2+1,-y2*(x1-1)*k,3);
    update(x2+1,y1,-x2*(y1-1)*k,3);
    update(x2+1,y2+1,x2*y2*k,3);
}
// get value from (x1,y1) to (x2,y2) inclusive
long long get( int x1, int y1, int x2, int y2 )
{
  intl v1=query(x2,y2,0)*x2*y2+query(x2,y2,1)*x2+
          query(x2,y2,2)*y2+query(x2,y2,3);
  intl v2=query(x2,y1-1,0)*x2*(y1-1)+ query(x2,y1-1,1)*x2+
          query(x2,y1-1,2)*(y1-1)+query(x2,y1-1,3);
  intl v3=query(x1-1,y2,0)*(x1-1)*y2+query(x1-1,y2,1)*(x1-1)+
          query(x1-1,y2,2)*y2+query(x1-1,y2,3);
  intl v4=query(x1-1,y1-1,0)*(x1-1)*(y1-1)+
          query(x1-1,y1-1,1)*(x1-1)+
          query(x1-1,y1-1,2)*(y1-1)+query(x1-1,y1-1,3);
  intl ans=v1-v2-v3+v4;
  return ans;
}

