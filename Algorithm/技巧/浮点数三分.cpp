const double EPS = 1e-9;
while(r - l < EPS) {
    double lmid = l + (r - l) / 3;
    double rmid = r - (r - l) / 3;
    lans = cal(lmid),rans = cal(rmid);
    
    // 求凹函数的极小值
    if(lans <= rans) r = rmid;
    else l = lmid;
    
    // 求凸函数的极大值
    if(lans >= rans) l = lmid;
    else r = rmid;
}
// 输出 l 或 r 都可
