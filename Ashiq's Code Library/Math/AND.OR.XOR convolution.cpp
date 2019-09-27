struct ANDconvolution {
    ///poww(a,b,m) returns (a^b)%m
    ///XOR
    void WHtransform(vector<long long>&P,bool inverse=0 ) {
        for (int len = 1; 2 * len <= P.size(); len <<= 1) {
            for(int i = 0; i < P.size(); i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    long long u = P[i + j];
                    long long v = P[i + len + j];
                    P[i + j] = u + v;//% mod
                    P[i + len + j] = u - v; //% mod
                }
            }
        }

        if (inverse) {
            //long long inv = poww(P.size(), mod-2, mod);
            for (int i = 0; i < P.size(); i++)
                P[i] = (P[i]/P.size()) ;
                //in case whole operation is done on modulo
        }
    }
    ///ORtransform
    void ANDtransform(vector<long long>&vec,bool inverse=0) {
        for(int len = 1; 2 * len <= vec.size(); len <<= 1) {
            for(int i = 0; i < vec.size(); i += 2 * len) {
                for(int j = 0; j < len; j++) {
                    long long u = vec[i + j];
                    long long v = vec[i + len + j];
                    if( !inverse ) {
                        //AND
                        vec[i + j] = v;
                        vec[i + len + j] = (u + v);//%mod;
                        //OR
                        vec[i + j] = u + v;
                        vec[i + len + j] = u;//%mod;
                    }
                    else {
                        //AND
                        vec[i + j] = (-u + v);//%mod;
                        vec[i + len + j] = u;
                        //OR
                        vec[i + j] = v;//%mod;
                        vec[i + len + j] = u - v;
                    }
                }
            }
        }
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting their multiplication x^a*x^b
    //= x^(a operation(and, or, xor) b)
    vector<long long> multiply( vector<long long> v1,
                               vector<long long>v2 ) {
        int d = 1, dd = max( v1.size(), v2.size() );
        while(d<dd) d*=2;
        v1.resize(d, 0); v2.resize(d, 0);
        vector<long long>res(d, 0);
        ANDtransform(v1, 0); ANDtransform(v2, 0);
        for( int i = 0; i < d; i++ ) res[i] = v1[i]*v2[i];
        ANDtransform(res, 1);
        return res;
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting (poly)^n
    vector<long long> multiply( vector<long long>v1, int n )
    {
        int d = 1, dd = v1.size();
        while(d<dd) d*=2;
        v1.resize(d, 0); vector<long long>res(d, 0);
        ANDtransform(v1, 0);
        for( int i = 0; i < d; i++ )
          res[i] = poww( v1[i], n, mod );
        ANDtransform(res, 1);
        return res;
    }

};
