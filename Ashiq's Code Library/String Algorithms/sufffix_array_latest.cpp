#include <bits/stdc++.h>
using namespace std ;

/**

sa[i] = i'th suffix, i from 0 to n-1
everything is in 0'th base
lcp[i] = lcp of (i-1)th and ith suffix, i from 0 to n-1
adjust the alpha, usually for string ALPHA = 128 (max ascii value)
notice if clearing may cause tle
remove range_lcp_init() if not required

**/

const int N = 2e4 + 5;
const int ALPHA = 128, LOG = 20;

struct SuffixArray {
    int sa[N],data[N],rnk[N],height[N],n;
    int wa[N],wb[N],wws[N],wv[N];
    int lg[N], rmq[N][LOG], rev_sa[N];
    int cmp(int *r,int a,int b,int l){
        return (r[a]==r[b]) && (r[a+l]==r[b+l]);
    }
    void DA(int *r,int *sa,int n,int m){
        int i,j,p,*x=wa,*y=wb,*t;
        for(i=0;i<m;i++) wws[i]=0;
        for(i=0;i<n;i++) wws[x[i]=r[i]]++;
        for(i=1;i<m;i++) wws[i]+=wws[i-1];
        for(i=n-1;i>=0;i--) sa[--wws[x[i]]]=i;
        for(j=1,p=1;p<n;j*=2,m=p) {
            for(p=0,i=n-j;i<n;i++) y[p++]=i;
            for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
            for(i=0;i<n;i++) wv[i]=x[y[i]];
            for(i=0;i<m;i++) wws[i]=0;
            for(i=0;i<n;i++) wws[wv[i]]++;
            for(i=1;i<m;i++) wws[i]+=wws[i-1];
            for(i=n-1;i>=0;i--) sa[--wws[wv[i]]]=y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
                x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
    }
    void calheight(int *r,int *sa,int n){
        int i,j,k=0;
        for(i=1;i<=n;i++) rnk[sa[i]]=i;
        for(i=0;i<n;height[rnk[i++]]=k)
            for(k?k--:0,j=sa[rnk[i]-1];r[i+k]==r[j+k];k++);
    }
    void suffix_array (string  &A) {
        n = A.size();
        for(int i=0;i<max(n+5,ALPHA);i++) sa[i]=data[i]=rnk[i]=height[i]=wa[i]=wb[i]=wws[i]=wv[i]=0;
        for (int i = 0; i < n; i++) data[i] = A[i];
        DA(data,sa,n+1,ALPHA);
        calheight(data,sa,n);
        for(int i = 0;i < n; i++) sa[i] = sa[i+1], height[i] = height[i+1], rev_sa[sa[i]] = i;
        range_lcp_init();
    }

    /** LCP for range : build of rmq table **/
    void range_lcp_init() {
        for(int i = 0; i < n; i++) rmq[i][0] = height[i];
        for(int j = 1; j < LOG; j++) {
            for(int i = 0; i < n; i++) {
                if (i+(1<<j)-1 < n) rmq[i][j] = min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
                else break;
            }
        }
        lg[0] = lg[1] = 0;
        for(int i = 2; i <= n; i++) {
            lg[i] = lg[i/2] + 1;
        }
    }

    /** lcp between l'th to r'th suffix **/
    int query_lcp(int l, int r) {
        assert(l <= r);
        assert(l>=0 && l<n && r>=0 && r<n);
        if(l == r) return n-sa[l];
        l++;
        int k = lg[r-l+1];
        return min(rmq[l][k],rmq[r-(1<<k)+1][k]);
    }
}SA;

bool cmp(pair<int,int> a, pair<int,int> b) {
    int l1 = a.first, r1 = a.second, l2 = b.first, r2 = b.second;
    bool f = 0;
    if(SA.rev_sa[l2] < SA.rev_sa[l1]) {
        swap(l1, l2);
        swap(r1, r2);
        f ^= 1;
    }
    int len1 = r1-l1+1, len2 = r2-l2+1;
    int com = SA.query_lcp(SA.rev_sa[l1], SA.rev_sa[l2]);
    if(com < min(len1, len2)) return f ^ 1;
    return (len1 < len2) ^ f;
}

int main () {

    return 0;
}
