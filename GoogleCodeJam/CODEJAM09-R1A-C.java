/*
  Author: Le Trong Dat
  Idea: Dp(i) = number of expected packs that we need to buy to get enough C kinds.
      Dp(i) = 1 + Dp(j) * possibilities to get j kinds after buy one more pack.
       (i<= j <= min(i+n, c));
       possibilites to get j kinds after buy one more pack = C(j-i, c-i)*C(n-j+i, i)/C(n, c).
*/
package com.letrongdat;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Scanner;

public class Main {
    public static int c, n;
    public static BigDecimal dp[] = new BigDecimal[50];
    public static BigDecimal C[][] = new BigDecimal[50][50];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        for(int i=1; i<=40; ++i) C[0][i]=C[i][i]=new BigDecimal("1");
        for(int i=1; i<=40; ++i) for(int j=1; j<i; ++j)
        {
            C[j][i] = C[j][i - 1].add(C[j - 1][i - 1]);
        }
        int T = scanner.nextInt();
        for (int itest = 1; itest <= T; ++itest)
        {
            c = scanner.nextInt();
            n = scanner.nextInt();
            dp[c] = new BigDecimal("0");
            for(int i=c-1; i>=n; --i)
            {
                BigDecimal sum = new BigDecimal("0");
                sum=sum.add(C[n][c]);
                for(int j=i+1; j<=Math.min(i+n, c); ++j)
                {
                    sum = sum.add(dp[j].multiply(C[j - i][c - i]).multiply(C[n - j + i][i]));
                }
                dp[i]=sum.divide(C[n][c].subtract(C[n][i]), 17, RoundingMode.HALF_UP);
            }
            BigDecimal tmp = new BigDecimal("1");
            dp[n]=dp[n].add(tmp);
            System.out.print("Case #" + itest + ": ");
            System.out.println(dp[n]);
        }
    }

}
