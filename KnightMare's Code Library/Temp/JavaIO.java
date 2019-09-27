import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task solver = new Task();
        solver.solve(1, in, out);
        out.close();
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }

    // Here
    static class Task {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            BigInteger sum = new BigInteger(in.next());

            data[] bids = new data[n];

            for (int i = 0; i < n; i++) {
                bids[i] = new data();
                bids[i].name = in.next();
                bids[i].bid = new BigInteger(in.next());
            }

            Arrays.sort(bids);
            ArrayList<String> ans = new ArrayList<>();
            for (int i = n - 1; i >= 0; i--) {
                BigInteger bid = bids[i].bid;
                if (sum.compareTo(bid) < 0) continue;
                sum = sum.subtract(bid);
                ans.add(bids[i].name);
            }
            if (sum.compareTo(BigInteger.ZERO) != 0) out.println(0);
            else {
                out.println(ans.size());
                for (String name : ans)
                    out.println(name);
            }
        }
        public class data implements Comparable{
            BigInteger bid;
            String name;

            public data() {
            }

            public data(BigInteger bid, String name)  {
                this.bid = bid;
                this.name = name;
            }

            @Override
            public int compareTo(Object o) {
                return bid.compareTo(((data) o).bid);
            }
        }
    }
}
