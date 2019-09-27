#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;
using namespace __gnu_pbds;

/*** Needs C++11 or C++14 ***/

class Treap{
    public:

    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> T;

    Treap(){
        T.clear();
    }

    inline void insert(int x){
        T.insert(x);
    }

    inline void erase(int x){
        T.erase(x);
    }

    /// 1-based index, returns the K'th element in the treap, -1 if none exists
    inline int kth(int k){
        if (k < 1) return -1;
        auto it = T.find_by_order(--k);
        if (it == T.end()) return -1;
        return *it;
    }

    /// Count of value < x in treap
    inline int count(int x){
        return (T.order_of_key(x));
    }

    /// Number of elements in treap
    inline int size(){
        return T.size();
    }
};

int main(){
}
