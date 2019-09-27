/*
struct line :
    m -> slope
    c -> y intercept
    xleft -> stores the left point of the line till which it is optimal
    type = 0 -> lines to be stored
    type = 1 -> query type

double meet(line x, line y)
    returns the x coordinate of intersection of x and y

struct cht:
    cht() -> constructor
    void addline(m, c) -> adds line(m, c) to hull
    long long getbest(long long x) ->   finds optimal line for given x and
                                        returns value of y(x) on that line

cht stores the lower hull of lines
to store the upper hull of lines
    negate m and c in the constructor of line
    negate the output of getbest(x)
*/



#include <bits/stdc++.h>
using namespace std;

/// CHT code courtesy : rajat1603

struct line{
	long long m , c;
	double xleft;
	bool type;
	line(long long _m , long long _c){
		m = _m;
		c = _c;
		type = 0;
	}
	bool operator < (const line &other) const{
		if(other.type){
			return xleft < other.xleft;
		}
		return m > other.m;
	}
};
double meet(line x , line y){
	return 1.0 * (y.c - x.c) / (x.m - y.m);
}
struct cht{     /// stores the lower hull of lines
	set < line > hull;
	cht(){
		hull.clear();
	}
	typedef set < line > :: iterator ite;
	bool hasleft(ite node){
		return node != hull.begin();
	}
	bool hasright(ite node){
		return node != prev(hull.end());
	}
	void updateborder(ite node){
		if(hasright(node)){
			line temp = *next(node);
			hull.erase(temp);
			temp.xleft = meet(*node , temp);
			hull.insert(temp);
		}
		if(hasleft(node)){
			line temp = *node;
			temp.xleft = meet(*prev(node) , temp);
			hull.erase(node);
			hull.insert(temp);
		}
		else{
			line temp = *node;
			hull.erase(node);
			temp.xleft = -1e18;
			hull.insert(temp);
		}
	}
	bool useless(line left , line middle , line right){
		return meet(left , middle) > meet(middle , right);
	}
	bool useless(ite node){
		if(hasleft(node) && hasright(node)){
			return useless(*prev(node) , *node , *next(node));
		}
		return 0;
	}
	void addline(long long m , long long c){
		line temp = line(m, c);
		auto it = hull.lower_bound(temp);
		if(it != hull.end() && it -> m == m){
			if(it -> c > c){
				hull.erase(it);
			}
			else{
				return;
			}
		}
		hull.insert(temp);
		it = hull.find(temp);
		if(useless(it)){
			hull.erase(it);
			return;
		}
		while(hasleft(it) && useless(prev(it))){
			hull.erase(prev(it));
		}
		while(hasright(it) && useless(next(it))){
			hull.erase(next(it));
		}
		updateborder(it);
	}
	long long getbest(long long x){
		if(hull.empty()){
			return -1e18;
		}

		line query(0 , 0);
		query.xleft = x;
		query.type = 1;

		auto it = hull.lower_bound(query);
		it = prev(it);
		return it -> m * x + it -> c;
	}
};
