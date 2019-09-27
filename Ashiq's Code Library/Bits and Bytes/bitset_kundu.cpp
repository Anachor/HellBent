typedef unsigned int UI;

struct Bitset {
    const static int K = 32, X = 31;

    vector<UI> bs;
    int N;

    Bitset(int n) {
        N = n/K+1;
        bs.resize(N);
    }

    bool get(int i) {
        return bs[i>>5] & (1U<<(i&X));
    }

    void set(int i) {
        bs[i>>5] |= (1U<<(i&X));
    }

    void And(const Bitset &b) {
        for (int i=0; i<N; i++)
            bs[i] &= b.bs[i];
    }

    int count() {
        int ans = 0;
        for (int i=0; i<N; i++)
            ans += __builtin_popcount(bs[i]);
        return ans;
    }
};
