int dp[505][505][10][10];
int val[505][505];
int num[505];
 
void rmq(int n, int m){
    int nn = log2(n), mm = log2(m);
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) dp[i][j][0][0] = val[i][j];
    
    for(int ii=0; ii<=nn; ii++)
    for(int jj=0; jj<=mm; jj++)
    if(ii + jj) {
        for(int i=1; i+(1<<ii)-1 <= n; i++)
        for(int j=1; j+(1<<jj)-1 <= m; j++) {
            if(ii) dp[i][j][ii][jj] = max(dp[i][j][ii-1][jj], dp[i+(1<<(ii-1))][j][ii-1][jj]);
            else dp[i][j][ii][jj] = max(dp[i][j][ii][jj-1], dp[i][j+(1<<(jj-1))][ii][jj-1]);
        }
    }
}
 
int query(int x1, int y1, int x2, int y2){
    int k1 = log2(x2-x1+1); //num[x2-x1+1];
    int k2 = log2(y2-y1+1); //num[y2-y1+1];
    x2 = x2 - (1<<k1) + 1;
    y2 = y2 - (1<<k2) + 1;
    
    int ans1 = max(dp[x1][y1][k1][k2], dp[x1][y2][k1][k2]);
    int ans2 = max(dp[x2][y1][k1][k2], dp[x2][y2][k1][k2]);
    return max(ans1, ans2);
}
 
void init(){ // 计算1-500的位数
    num[0] = -1;
    for(int i=1; i<=500; i++) num[i] = (i & (i-1)) ? num[i-1] : num[i-1] + 1;
}
