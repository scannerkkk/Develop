int n;
int dp[1010][1010],s1[1010],s2[1010];
void solve()
{
	rep(i,1,n) cin>>s1[i];
	rep(i,1,n) cin>>s2[i];
	rep(i,1,n) rep(j,1,n) if(s1[i]==s2[j]) dp[i][j]=dp[i-1][j-1]+1;
						else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
	cout<<dp[n][n]<<endl;
}
int main()
{
	cin >> n;
	solve();
	return 0;
}
