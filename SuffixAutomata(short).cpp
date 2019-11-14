/*
https://www.spoj.com/problems/STRSOCU/
given two strings s,t and an integer k, how many distinct substrings of s occurs exactly k times in t ?
O(n) solution
*/
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define IN freopen("C.in","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef pair<int, int> pi ;
typedef tree< pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 100005

/*
     *os.find_by_order(k) -> returns the k'th smallest element (indexing starts from 0)
      os.order_of_key(v)  -> returns how many elements are strictly smaller than v
*/
class SuffixAutomaton{
public:
    struct state{
        int edge[27] , len , link , cnt ;
    };

    state *st ;
    int sz , last , alpha = 26 ;

    SuffixAutomaton( string &s )
    {
        int l = s.length() ;
        int i , j ;
        st = new state[l*2] ;

        st[0].link = -1  ; st[0].len = 0 ; st[0].cnt = 0 ; sz = 1 ; last = 0 ;
        for(i=0 ; i<alpha ; i++) st[0].edge[i] = -1 ;

        for(i=0 ; i<l ; i++)
        {
            int cur = sz++ ;

            for(j=0 ; j<alpha ; j++) st[cur].edge[j] = -1 ;
            st[cur].len = st[last].len+1 ; st[cur].cnt = 1 ;

            int p = last , c = s[i]-'a' ;

            while( p!=-1 && st[p].edge[c] == -1 )
            {
                st[p].edge[c] = cur ;
                p = st[p].link ;
            }

            if( p == -1 )
            {
                st[cur].link = 0 ;
            }
            else
            {
                int q = st[p].edge[c] ;
                if( st[p].len+1 == st[ q ].len  ) st[cur].link = q ;
                else{
                    int clone = sz++ ;
                    for(j=0 ; j<alpha ; j++) st[clone].edge[j] = st[q].edge[j] ;
                    st[clone].len = st[p].len+1 ;
                    st[clone].link = st[q].link ;
                    st[clone].cnt = 0 ;

                    while( p!=-1 && st[p].edge[c] == q )
                    {
                        st[p].edge[c] = clone ;
                        p = st[p].link ;
                    }
                    st[q].link = st[cur].link = clone ;
                }
            }
            last = cur ;
        }
        vector <pi> vp ;
        for(i=0 ; i<sz ; i++) vp.pb( mp( st[i].len , i ) ) ;
        sort(vp.begin(),vp.end()) ;

        for( i=sz-1 ; i>0 ; i-- )
        {
            int state = vp[i].yy ;
            st[st[ state].link].cnt += st[ state].cnt ;
   //         printf("%d %d\n",st[state].cnt[0],st[state].cnt[1]) ;
        }
    }

    int f( string t )
    {
        int len = (int)t.size() ;
        t = t+t ;
//        t.pop_back() ;

        int cur = 0 , myLen = 0 ;

        vector <int> vis ;

        for(int i=0 ; i<t.size() ; i++)
        {
            int ch = t[i] - 'a' ;
            while( st[ cur ].edge[ch] == -1 && st[cur].link!=-1 )
            {
                cur = st[cur].link ;
                myLen = st[cur].len ;
            }
            if( st[cur].edge[ch]!=-1 ) cur = st[cur].edge[ch] , myLen++ ;

            while( cur!=0 && st[ st[cur].link ].len >= len )
            {
                cur = st[cur].link ;
                myLen = st[cur].len ;
            }
            if( cur !=0 && myLen >= len ) vis.pb( cur ) ;

//            if( myLen >= len && st[cur].len >= len  ) cout<<i<<" "<<st[cur].cnt<<endl ;

        }
        sort( vis.begin() , vis.end() ) ;

        int ans = 0 ;

        for( int i=0 ; i<vis.size() ; i++ )
        {
            int cur = vis[i] ;
            if( i > 0 && vis[i]==vis[i-1] ) continue ;
            if( st[cur].len >= len && st[ st[cur].link ].len < len ) ans += st[cur].cnt ;
        }
        return ans ;
    }

    ~SuffixAutomaton()
    {
        delete []st ;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s  , t ;

    cin>>s ;

    int m ;
    cin>>m ;

    SuffixAutomaton sa(s) ;

    for(int i=1 ; i<=m ; i++)
    {
        cin>>t ;
        cout<<sa.f(t)<<"\n" ;
    }

    return 0 ;
}
