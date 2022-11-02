ll mul(ll a,ll k,ll p)
{
    ll res = 0;
    while(k) {
        if(k & 1) res = (res + a) % p;
        a = (a + a) % p;
        k >>= 1;
    }
    return res;
}
ll ksm(ll a,ll k,ll p)
{
    ll res = 1;
    while(k) {
        if(k & 1) res = mul(res,a,p);
        a = mul(a,a,p);
        k >>= 1;
    }
    return res;
}
//当p过于大的时候，就需要用龟速乘规避精度问题
