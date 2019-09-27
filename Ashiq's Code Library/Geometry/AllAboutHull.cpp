/// All About Convex Hull....
struct Point{
    bool operator < (const Point &p) const {
        return make_pair(x,y) < make_pair(p.x,p.y) ;
    }
    bool operator > (const Point &p) const {
        return make_pair(x,y) > make_pair(p.x,p.y) ;
    }
};
struct ConvexHull {
	vector<Point> hull, lower, upper;
	int n;
	/// builds convex hull of a set of points
	bool ccw(Point p,Point q,Point r) {
        return ((q-p)^(r-q)) > 0 ;
    }
  ll cross(Point p, Point q, Point r) {
    return (q-p)^(r-q);
  }
  Point LineLineIntersection(Point p1, Point p2, Point q1, Point q2) {
    ll a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
  }

  void init(vector<Point> &poly) {
    hull.clear() ; lower.clear() ; upper.clear() ;
    sort(poly.begin(),poly.end()) ;
    for(int i = 0 ; i < poly.size() ; i++) {
      while(lower.size() >= 2 and !ccw(lower[lower.size()-2],lower.back(),poly[i])) {
          lower.pop_back() ;
      }
      lower.push_back(poly[i]) ;
    }
    for(int i = (int)poly.size()-1 ; i >= 0 ; i--) {
      while(upper.size() >= 2 and !ccw(upper[upper.size()-2],upper.back(),poly[i])) {
        upper.pop_back() ;
      }
      upper.push_back(poly[i]) ;
    }
    hull = lower ;
    for(int i = 1 ; i + 1 < upper.size() ; i++) hull.push_back(upper[i]) ;
    n = hull.size();
  }
  int sign(ll x) {
    if (x < 0) return -1 ;
    return x > 0 ;
  }
  int crossOp(Point p, Point q, Point r) {
    ll c = (q-p)^(r-q) ;
    if (c < 0) return -1 ;
    return (c > 0) ;
  }
  /// tests if Point p is inside or on the convex polygon
  /// if Point p is on any side a,b is the index of two endpoint of the segment
  bool contain(Point p,int&a,int&b){
		if(p.x < lower[0].x || p.x > lower.back().x) return 0;
    int id = lower_bound(lower.begin(), lower.end(),Point(p.x,-INF)) - lower.begin();
    if(lower[id].x == p.x){
			if(lower[id].y > p.y) return 0;
		} else {
			if(crossOp(lower[id-1],lower[id],p) < 0) return 0;
			if(crossOp(lower[id-1],lower[id],p) == 0){
        a = id - 1; b = id;
        return 1;
			}
		}
    id = lower_bound(upper.begin(), upper.end(),Point(p.x,INF),greater<Point>()) - upper.begin();
		if(upper[id].x == p.x){
			if(upper[id].y < p.y) return 0;
		} else {
			if(crossOp(upper[id-1],upper[id],p) < 0) return 0;
			if(crossOp(upper[id-1],upper[id],p) == 0) {
        a = id - 1 + lower.size() - 1;
        b = id  + lower.size() - 1;
        return 1;
			}
		}
		return 1;
	}
	int find(vector<Point>&vec, Point dir){
		int l = 0 , r = vec.size();
		while(l+5<r){
			int L = (l*2+r)/3, R = (l+r*2)/3;
			if(vec[L]*dir > vec[R]*dir)
				r=R;
			else
				l=L;
		}
		int ret = l;
		for(int k = l+1; k < r; k++) if(vec[k]*dir > vec[ret]*dir) ret = k;
		return ret;
	}
	/// if there are rays coming from infinite distance in dir direction, the furthest Point of the hull is returned
	int findFarest(Point dir){
		if(sign(dir.y) > 0 || sign(dir.y) == 0 && sign(dir.x) > 0){
			return ( (int)lower.size()-1 + find(upper,dir)) % n;
		} else {
			return find(lower,dir);
		}
	}
	Point get(int l,int r,Point p1,Point p2){
		int sl = crossOp(p1,p2,hull[l%n]);
		while(l+1<r){
			int m = (l+r)>>1;
			if(crossOp(p1,p2,hull[m%n]) == sl)
				l = m;
			else
				r = m;
		}
		return LineLineIntersection(p1,p2,hull[l%n],hull[(l+1)%n]);
	}
//Intersection between a line and a convex polygon. O(log(n))
// touching the hull does not count as intersection
	vector<Point> Line_Hull_Intersection(Point p1, Point p2){
		int X = findFarest((p2-p1).rot90());
		int Y = findFarest((p1-p2).rot90());
		if(X > Y) swap(X,Y);
		if(crossOp(p1,p2,hull[X]) * crossOp(p1,p2,hull[Y]) < 0){
			return {get(X,Y,p1,p2),get(Y,X+n,p1,p2)};
		} else {
			return {};
		}
	}
	void update_tangent(Point p, int id, int&a,int&b){
		if(crossOp(p,hull[a],hull[id]) > 0) a = id;
		if(crossOp(p,hull[b],hull[id]) < 0) b = id;
	}
	void binary_search(int l,int r,Point p,int&a,int&b){
		if(l==r) return;
		update_tangent(p,l%n,a,b);
		int sl = crossOp(p,hull[l%n],hull[(l+1)%n]);
		while(l+1<r){
			int m = l+r>>1;
			if(crossOp(p,hull[m%n],hull[(m+1)%n]) == sl)
				l=m;
			else
				r=m;
		}
		update_tangent(p,r%n,a,b);
	}
	void get_tangent(Point p,int&a,int&b){
		if(contain(p,a,b)) {
			return ;
		}
		a = b = 0;
		int id = lower_bound(lower.begin(), lower.end(),p) - lower.begin();
		binary_search(0,id,p,a,b);
		binary_search(id,lower.size(),p,a,b);
		id = lower_bound(upper.begin(), upper.end(),p,greater<Point>()) - upper.begin();
		binary_search((int)lower.size() - 1, (int) lower.size() - 1 + id,p,a,b);
		binary_search((int) lower.size() - 1 + id,(int) lower.size() - 1 + upper.size(),p,a,b);
	}
};
