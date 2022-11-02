void Gauss()
{
    for(int r = 1,c = 1;c <= n;c ++) {
        int t = r;
        //找元
        for(int i = r + 1;i <= n;i++) if(b[t][c] < b[i][c]) t = i;
        //判0,最大是0,表示这列不需要操作
        if(fabs(b[t][c]) == 0) continue;
        //换行
        for(int i = c;i <= n + 1;i++) swap(b[r][i],b[t][i]);
        //变列
        for(int i = n + 1;i >= c;i--) b[r][i] /= b[r][c];
        //消元
        for(int i = r + 1;i <= n;i++) {
            if(fabs(b[i][c] == 0)) continue;
            for(int j = n + 1;j >= c;j--) b[i][j] -= b[r][j] * b[i][c]; 
        }
        r ++;
    }
    //消成最简行列式
    for(int i = n;i >= 1;i--) 
        for(int j = i - 1;j >= 1;j--) {
            b[j][n + 1] -= b[j][i] * b[i][n + 1];
            b[j][i] = 0;
        }
}
