#include "bits/stdc++.h"
#define PIS pair<int,string>
#define PSC pair<string,char>
#define fi first
#define se second
using namespace std;
int mx[] = {-1,1,0,0};
int my[] = {0,0,-1,1};
char d[] = "udlr";
// BFS的优化，用一个启发函数，来计算出某个状态到目标状态的预估值

// 可以达到在很大的搜索范围中，找到一种方法最快的搜索到

// 这题的启发函数，是每个数到目标状态对应数位置的曼哈顿距离
int f(string s)
{
	int res = 0;
	//估计函数必须是正
	for(int i = 0;i < s.size();i ++){
		if(s[i] !=  'x'){
			int t = s[i] - '1';
			res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
		}
	}
	return res;
}
string bfs(string s)
{
	string res = "",end = "12345678x";
	priority_queue<PIS,vector<PIS>,greater<PIS>> que;
	unordered_map<string,int> dis;
	unordered_map<string,PSC> pre;
	que.push({f(s),s});
	while(que.size()) {
		PIS v = que.top();
		que.pop();
		//如果已经找到了，出队的时候判的最终答案一定是对的
		if(v.se == end) break;	
		int curx,cury;
		for(int i = 0;i < v.se.size();i ++)
			if(v.se[i] == 'x'){
				curx = i / 3;
				cury = i % 3;
			}

		string src = v.se;
		for(int i  = 0;i < 4;i ++) {
			int dx = curx + mx[i];
			int dy = cury + my[i];
			if(dx < 0 || dx >= 3 || dy < 0 || dy >= 3) continue;
			swap(v.se[curx * 3 + cury],v.se[dx * 3 + dy]);
			if(!dis.count(v.se) || dis[v.se] > dis[src] + 1)  {
				dis[v.se] = dis[src] + 1;
				pre[v.se] = {src,d[i]};
				que.push({dis[v.se],v.se});
			}
			swap(v.se[curx * 3 + cury],v.se[dx * 3 + dy]);
		}
	}

	string sta = s;
	while(sta != end){
		res += pre[sta].se;
		end = pre[sta].fi;
	}
	reverse(res.begin(),res.end());
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int cnt = 0;
	string res,seq;
	res = seq = "";
	char c;
	while(cin >> c) {
		if(c != 'x') seq += c;
		res += c;
	}

	for(int i = 0;i < 8;i ++)
		for(int j = i + 1;j < 8;j ++)
			if(seq[j] < seq[i]) cnt++;
	if(cnt & 1) {
		puts("unsolvable");
		return 0;
	}
	cout << bfs(res) << endl;
	return 0;
}
