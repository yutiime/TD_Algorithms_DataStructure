#include <stdio.h>

#define MAXN 100
#define MAXM 100
#define MAXK 100

// dp[i][j][p] = number of paths to reach (i, j)
// having caught exactly p Pokémon
// the decad team uses long long for large capacity.
static unsigned long long dp[MAXN][MAXM][MAXK + 1];
static int grid[MAXN][MAXM];

int main(void) {
    int n, m, k;

    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0; // invalid input
    }

    // read the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // initialization to 0 (already the case as static, but we keep the idea in mind)
    // dp[...] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int val = grid[i][j];  // pokemon on this cell

            if (i == 0 && j == 0) {
                // starting cell
                if (val <= k) {
                    dp[0][0][val] = 1;
                }
                continue; // move to next cell
            }

            // for each possible sum p when reaching (i, j)
            // we needed to have p - val before entering this cell
            for (int p = val; p <= k; p++) {
                unsigned long long ways = 0;

                // come from top (i-1, j)
                if (i > 0) {
                    ways += dp[i - 1][j][p - val];
                }
                // come from left (i, j-1)
                if (j > 0) {
                    ways += dp[i][j - 1][p - val];
                }

                dp[i][j][p] = ways;
            }
        }
    }

    // paths reaching bottom-right with exact sum = k
    printf("%llu\n", dp[n - 1][m - 1][k]);

    return 0;
}
