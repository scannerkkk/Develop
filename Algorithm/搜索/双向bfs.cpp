#include "bits/stdc++.h"
using namespace std;
const int N = 6;
int n;
string a[N],b[N];
//双向bfs适合有双向规则的最小步数题
int extend(queue<string> &q,unordered_map<string,int>&da,unordered_map<string,int>&db,string a[],string b[])
{
	string v = q.front();
	q.pop();
	for(int i = 0;i < v.size();i ++)
		for(int j = 0;j < n;j ++){
			if(v.substr(i,a[j].size()) == a[j]){
				string tmp = v.substr(0,i) + b[j] + v.substr(i + a[j].size());
				if(db.count(tmp)) return db[tmp] + 1 + da[v];
				if(da.count(tmp)) continue;
				da[tmp] = da[v] + 1;
				q.push(tmp);
			}
		}
	return 11;
}
int bfs(string s1,string s2)
{
	if(s1 == s2) return 0;
	queue <string> qa,qb;
	unordered_map<string,int> da,db;
	qa.push(s1);qb.push(s2);
	da[s1] = 0;db[s2] = 0;
	while(qa.size() && qb.size()) {
		int t;
		//每次搜较少的那边
		if(qa.size() > qb.size()) t = extend(qb,db,da,b,a);
		else t = extend(qa,da,db,a,b);
		if(t <= 10) return t;
	}
	return 11;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s1,s2;
	cin >> s1 >> s2;
	while(cin >> a[n] >> b[n]) n++;
	int step = bfs(s1,s2);
	if(step > 10) puts("NO ANSWER!");
	else cout << step << endl;
	return 0;
}
