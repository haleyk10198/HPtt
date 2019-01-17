// forked from the official editorial
// https://www.hackerrank.com/challenges/digit-products/editorial

// Be responsible in using the editorial code

#include <stdio.h>
#include <stdbool.h>

#include <bits/stdc++.h>

#define MAXL 102
#define MAXN 66666
#define MOD  1000000007

const int primes[] = {2, 3, 5, 7};
const int logK[] = {60, 38, 26, 22};
const int counter[10][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {2, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 1}, {3, 0, 0, 0}, {0, 2, 0, 0}}; // Prime factorization table for 0-9

char A[MAXL], B[MAXL];
bool visited[MAXL][MAXN] = {false};
int n, dp[MAXL][MAXN], num[60][38][26][22];

int F(int n, int a, int b, int c, int d){
    if (!n) return (!a && !b && !c && !d);
    if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
    int j, k, h = num[a][b][c][d];
    if (visited[n][h]) return dp[n][h];

    int res = 0;
    for (j = 1; j < 10; j++){
        res += F(n - 1, a - counter[j][0], b - counter[j][1], c - counter[j][2], d - counter[j][3]);
        if (res >= MOD) res -= MOD;
    }
    visited[n][h] = true;
    return (dp[n][h] = res);
}

int dfs(char* str, int i, int a, int b, int c, int d){
    if (i == n) return (!a && !b && !c && !d);

    int j, res = 0, x = str[i] - '0';
    if (x) res += dfs(str, i+1, a-counter[x][0], b-counter[x][1], c-counter[x][2], d-counter[x][3]);
    for (j = 1; j < x; j++){
        res += F(n - i - 1, a - counter[j][0], b - counter[j][1], c - counter[j][2], d - counter[j][3]);
        if (res >= MOD) res -= MOD;
    }
    return res;
}

int count(char* str, long long k){
    n = strlen(str);
    int i, j, ar[4] = {0};

    for (i = 0; i < 4; i++){
        while (!(k % primes[i])){
            k /= primes[i];
            ar[i]++;
        }
    }
    if (k > 1) return 0; // Contains prime factor > 7

    long long res = dfs(str, 0, ar[0], ar[1], ar[2], ar[3]);
    for (i = 1; i < n; i++) res += F(n - i, ar[0], ar[1], ar[2], ar[3]);
    return (res % MOD);
}

void Generate(){
    int i, j, k, l, d, c = 0;
    const double lg2 = log10(2.0), lg3 = log10(3.0), lg5 = log10(5.0), lg7 = log10(7.0);

    for (i = 0; i < logK[0]; i++){
        for (j = 0; j < logK[1]; j++){
            for (k = 0; k < logK[2]; k++){
                for (l = 0; l < logK[3]; l++){
                    if (((lg2 * i) + (lg3 * j) + (lg5 * k) + (lg7 * l)) > 18.0001) break;
                    num[i][j][k][l] = c++;
                }
            }
        }
    }
}

int main(){
    Generate();
    long long k, x;
    int T = 0, t, i, j, res;

    scanf("%d", &t);
    while (t--){
        scanf("%s %s %lld", A, B, &k);
        res = (count(B, k) - count(A, k) + MOD) % MOD;

        for (x = 1, i = 0; A[i] != 0; i++){
            x *= (A[i] - '0');
            if (x > k) break;
        }
        printf("Case %d: %d\n", ++T, (res + (x == k)) % MOD );
    }
    return 0;
}
