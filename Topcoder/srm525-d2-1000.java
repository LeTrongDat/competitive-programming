/*
  Author: Le Trong Dat.
  
*/
public class MagicalSquare {
    private int[][][][] dp = new int[3][3][55][55];

    public long getCount(String[] rowStrings, String[] columnStrings) {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                for (int irow = 1; irow <= rowStrings[row].length(); ++irow)
                    for (int icol = 1; icol <= columnStrings[col].length(); ++icol) {
                        dp[row][col][irow][icol] = 0;
                        for (int l = 1; irow + l - 1 <= rowStrings[row].length() && icol + l - 1 <= columnStrings[col].length(); ++l) {
                            if (rowStrings[row].charAt(irow + l - 2) == columnStrings[col].charAt(icol + l - 2))
                                dp[row][col][irow][icol]++;
                            else break;
                        }
                    }
            }
        long rez=0;
        for (int i1 = 0; i1 <= rowStrings[0].length(); ++i1) {
            for (int i2 = 0; i1+i2 <= rowStrings[0].length(); ++i2) {
                int i3 = rowStrings[0].length() - i1 - i2;
                if (dp[0][0][1][1] >= i1 && dp[0][1][i1+1][1] >= i2 && dp[0][2][i1+i2+1][1] >= i3) {
                    for(int j1 = 0; j1 <= rowStrings[1].length(); ++j1) {
                        for(int j2 = 0; j1+j2 <= rowStrings[1].length(); ++j2) {
                            int j3 = rowStrings[1].length() - j1 - j2;
                            if (dp[1][0][1][i1+1] >= j1 && dp[1][1][j1+1][i2+1] >= j2 && dp[1][2][j1+j2+1][i3+1] >= j3) {
                                int z1 = columnStrings[0].length()-i1-j1, z2=columnStrings[1].length()-i2-j2, z3=columnStrings[2].length()-i3-j3;
                                if (dp[2][0][1][i1+j1+1] == z1 && dp[2][1][z1+1][i2+j2+1] == z2 && dp[2][2][z1+z2+1][i3+j3+1] == z3 && z1+z2+z3==rowStrings[2].length()) {
                                    rez ++;
                                }
                            }
                        }
                    }
                }
            }
        }
        return rez;
    }
}
