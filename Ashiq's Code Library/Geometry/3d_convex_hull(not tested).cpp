/// 3D Convex Hull (not tested)

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1010

typedef double vtype;

/* Basic 3D vector implementation */
struct vec3
{
    vec3()
    {
        X[0] = X[1] = X[2] = 0;
    }
    vec3(vtype x, vtype y, vtype z)
    {
        X[0] = x;
        X[1] = y;
        X[2] = z;
    }

    /* 3D cross product */
    vec3 operator*(const vec3& v) const
    {
        return vec3(X[1] * v.X[2] - X[2] * v.X[1],
                    X[2] * v.X[0] - X[0] * v.X[2],
                    X[0] * v.X[1] - X[1] * v.X[0]);
    }

    vec3 operator-(const vec3& v) const
    {
        return vec3(X[0] - v.X[0], X[1] - v.X[1], X[2] - v.X[2]);
    }

    vec3 operator-() const
    {
        return vec3(-X[0], -X[1], -X[2]);
    }

    vtype dot(const vec3& v) const
    {
        return X[0] * v.X[0] + X[1] * v.X[1] + X[2] * v.X[2];
    }

    vtype X[3];
};

/* Original points in the input. */
vec3 A[MAXN] , B[MAXN] , C[MAXN] ;

/* E[i][j] indicates which (up to two) other points combine with the edge i and
 * j to make a face in the hull.  Only defined when i < j.
 */
struct twoset
{
    void insert(int x)
    {
        (a == -1 ? a : b) = x;
    }
    bool contains(int x)
    {
        return a == x || b == x;
    }
    void erase(int x)
    {
        (a == x ? a : b) = -1;
    }
    int size()
    {
        return (a != -1) + (b != -1);
    }
    int a, b;
} E[MAXN][MAXN];

struct face
{
    vec3 norm;
    vtype disc;
    int I[3];
    vec3 f[3] ;
};

/* Compute the half plane {x : c^T norm < disc}
 * defined by the three points A[i], A[j], A[k] where
 * A[inside_i] is considered to be on the 'interior' side of the face. */
face make_face(int i, int j, int k, int inside_i)
{
    E[i][j].insert(k);
    E[i][k].insert(j);
    E[j][k].insert(i);

    face f;
    f.I[0] = i; f.f[0] = A[i] ;
    f.I[1] = j; f.f[1] = A[j] ;
    f.I[2] = k; f.f[2] = A[k] ;
    f.norm = (A[j] - A[i]) * (A[k] - A[i]);
    f.disc = f.norm.dot(A[i]);
    if(f.norm.dot(A[inside_i]) > f.disc)
    {
        f.norm = -f.norm;
        f.disc = -f.disc;
    }
    return f;
}

vector <face> ConvexHull3d(int N) {
        /* Initially construct the hull as containing only the first four points. */
    face f;
    vector<face> faces;
    memset(E, -1, sizeof(E));
    for(int i = 0; i < 4; i++)
        for(int j = i + 1; j < 4; j++)
            for(int k = j + 1; k < 4; k++)
            {
                faces.push_back(make_face(i, j, k, 6 - i - j - k));
            }

    /* Now add a point into the hull one at a time. */
    for(int i = 4; i < N; i++)
    {
        /* Find and delete all faces with their outside 'illuminated' by this
         * point. */
        for(int j = 0; j < faces.size(); j++)
        {
            f = faces[j];
            if(f.norm.dot(A[i]) > f.disc)
            {
                E[f.I[0]][f.I[1]].erase(f.I[2]);
                E[f.I[0]][f.I[2]].erase(f.I[1]);
                E[f.I[1]][f.I[2]].erase(f.I[0]);
                faces[j--] = faces.back();
                faces.resize(faces.size() - 1);
            }
        }
        /* Now for any edge still in the hull that is only part of one face
         * add another face containing the new point and that edge to the hull. */
        int nfaces = faces.size();
        for(int j = 0; j < nfaces; j++)
        {
            f = faces[j];
            for(int a = 0; a < 3; a++) for(int b = a + 1; b < 3; b++)
                {
                    int c = 3 - a - b;
                    if(E[f.I[a]][f.I[b]].size() == 2) continue;
                    faces.push_back(make_face(f.I[a], f.I[b], i, f.I[c]));
                }
        }
    }

    return faces ;
}

double distance(vec3 v , face f) {
    /* Compute the minimum distance of each query
         * point to given face of the hull. */
    double mn = 1e10 ;
    /* distance of the query point to
    each vertex of the face */
    for (int i = 0 ; i < 3 ; i++) {
        vec3 d = f.f[i]-v ;
        mn = min(mn , sqrt(1.0*d.dot(d))) ;
    }
    cout << "min: " << mn << endl ;
    vec3 U = f.f[1]-f.f[0] , V = f.f[2]-f.f[0] , W = v-f.f[0] ;
    vtype gamma = abs ( (U*W).dot(f.norm) ) , beta = abs ( (W*V).dot(f.norm) ) ;
    vtype n_2 = f.norm.dot(f.norm) ;
    vtype alpha = n_2-gamma-beta ;
    if (gamma <= n_2 and gamma >= 0 and beta <= n_2 and beta >= 0 and alpha >= 0 and alpha <= n_2) {
        vec3 tmp ;
        for (int i = 0 ; i < 3 ; i++) {
            tmp.X[i] = alpha*f.f[0].X[i] + beta*f.f[1].X[i] + gamma*f.f[2].X[i] ;
            tmp.X[i] /= n_2 ;
        }
        cout << "tmp: " << tmp.X[0] << " " << tmp.X[1] << " " << tmp.X[2] << endl ;
        cout << "n_2: " << n_2 << endl ;
        cout << "v: " << v.X[0] << " " << v.X[1] << " " << v.X[2] << endl ;
        vec3 d = tmp-v ;
        cout << "d: " << d.X[0] << " " << d.X[1] << " " << d.X[2] << endl ;
        double dd = sqrt(1.0*d.dot(d)) ;
        cout << "dd: " << dd << endl ;
        mn = min(mn , dd) ;
    }
    return mn ;
}



int main()
{

   // freopen("in.txt" , "r" , stdin) ;
    int tc ;
    cin >> tc ;
    while (tc--)
    {
        double area = 0.0 ;
        int N; cin >> N ;
        for(int i = 0; i < N; i++)
        {
            cin >> A[i].X[0] >> A[i].X[1] >> A[i].X[2];
            B[i] = A[i] ;
        }
        vector<face> face1 = ConvexHull3d(N) ;
       /* cout << face1.size() << endl ;
        for (int i = 0; i < face1.size() ; i++) {
            cout << face1[i].I[0] << " " << face1[i].I[1] << " " << face1[i].I[2] << endl ;
        }*/
        for (int i = 0 ; i < face1.size() ; i++) {
            double cur_area = sqrt(1.0*face1[i].norm.dot(face1[i].norm))/2.0 ;
            area += cur_area ;
        }

        int M ; cin >> M ;
        for (int i = 0 ; i < M ; i++) {
            cin >> A[i].X[0] >> A[i].X[1] >> A[i].X[2] ;
            C[i] = A[i] ;
        }
        vector <face> face2 = ConvexHull3d(M) ;
        for (int i = 0 ; i < face2.size() ; i++) {
            double cur_area = sqrt(1.0*face2[i].norm.dot(face2[i].norm))/2.0 ;
            area += cur_area ;
        }
       // cout << "area: " << area << endl ;
        double mn = 1e10 ;
        for (int i = 0 ; i < N ; i++) {
            for (int j = 0 ; j < face2.size() ; j++) {
                double cur = distance(B[i],face2[j]) ;
                mn = min(mn,cur) ;
                cout << cur << endl ;
            }
        }
        for (int i = 0 ; i < M ; i++) {
            for (int j = 0 ; j < face1.size() ; j++) {
                double cur = distance(C[i],face1[j]) ;
                mn = min(mn,cur) ;
                //cout << cur << endl ;
            }
        }
        area += mn ;
        printf ("%.12f\n" , area) ;
    }
}


