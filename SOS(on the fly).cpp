public class TestProctoring {
    public double expectedTime(int[] p, int[] q) {
        int n = p.length;
        double[] prob = new double[n];
        for (int i = 0; i < n; i++) {
            prob[i] = p[i] * 1.0 / q[i];
        }
        double[][] t = new double[n+1][1<<n];
        double[] dp = new double[1<<n];

       /* t[i][mask] is sum of all submask of mask where
       difference of mask and submask is before i'th bit( 0 based ) , that means
       difference can be in 0 to i-1 th bit
       t[0][mask] contains nothing other than just value of this mask
       t[n][mask] contains result of all submask of this mask
        */

        for (int mask = 1; mask < 1 << n; mask++) {
            double fail = 1;
            double mult = 1;
            double am = 1;
            for (int j = 0; j < n; j++) { t[j+1][mask] = t[j][mask]; if (((mask>>j)&1) == 1) {
                    t[j+1][mask] += t[j][mask^(1<<j)];
                    fail *= (1 - prob[j]);
                    mult *= prob[j];
                    am *= (1 - prob[j]) / prob[j];
                }
            }
            dp[mask] = (1 + mult * t[n][mask]) / (1 - fail);
            for (int j = 0; j <= n; j++) {
                t[j][mask] += dp[mask] * am;
            }
        }
        return dp[(1<<n)-1];
    }
}
