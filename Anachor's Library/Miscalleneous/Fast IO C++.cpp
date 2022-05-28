///Source: Vule gesi :(

#include<bits/stdc++.h>
using namespace std;

namespace FASTIO {
    static const int buf_size = 4096;

    /** read */
    inline int getChar() {
        static char buf[buf_size];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, buf_size, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }

    inline int readChar() {
        int c = 0;
        while (c <= 32)     c = getChar();
        return c;
    }

    template <class T = long long>
    inline T readInt() {
        int s = 1, c = readChar();
        T x = 0;
        if (c == '-')       s = -1, c = getChar();
        while ('0' <= c && c <= '9')    x = x * 10 + c - '0', c = getChar();
        return s == 1 ? x : -x;
    }

    /** Write */
    static int write_pos = 0;
    static char write_buf[buf_size];
    inline void writeChar( int x ) {
        if (write_pos == buf_size)  fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
        write_buf[write_pos++] = x;
    }

    template <class T = long long>
    inline void writeInt( T x, char end = 0) {
        if (x < 0)  writeChar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--)     writeChar(s[n]);
        if (end)        writeChar(end);
    }

    inline void writeWord( const char *s ) {
        while (*s)  writeChar(*s++);
    }

    struct Flusher {
        ~Flusher() {
            if (write_pos)  fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
        }
    } flusher;
}

///Solves https://old.yosupo.jp/problem/many_aplusb
int main() {
    long long t;
    t = FASTIO::readInt();

    while (t--) {
        long long x, y;
        x = FASTIO::readInt(), y = FASTIO::readInt();
        FASTIO::writeInt(x+y);
        FASTIO::writeChar('\n');
    }
}
