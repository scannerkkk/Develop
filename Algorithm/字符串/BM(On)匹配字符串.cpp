#include "bits/stdc++.h"
using namespace std;
int Tables[260];
//Suffix长度为模式串的长度，数组的下标为模式串后缀子串的长度
//值为后缀子串在模式串中可匹配的子串的起始下标
//Prefix表示模式串的后缀子串是否有可匹配的前缀子串
int Suffix[260];
bool Prefix[260];
void Get_GTables(string pat)
{
	int len = pat.length();
	for(int i = 0;i < len;i++){
		Prefix[i] = false;
		Suffix[i] = -1;
	}
	//len - 1是因为最后一个字符不作为后缀
	for(int i = 0;i < len - 1;i++){
		int idx = i;
		int stp = 0;
		while(idx >= 0 && pat[idx] == pat[len - stp - 1]){
			idx--;
			stp++;
			Suffix[stp] = idx + 1;
		}
		//如果存在完整的后缀
		if(idx == -1)
			Prefix[stp] = true;
	}
}
void Get_BTables(string pat)
{
	for(int i = 0;i <= 256;i++)
		Tables[i] = -1;
	//初始化某个字符为最右边的字符的位置
	for(int i = 0,len = pat.length();i < len;i++)
		Tables[pat[i] - '0'] = i;
}
int G_length(int len,int pos)
{
	int idx = len - pos - 1;
	//好后缀在模式串中，直接计算可以移动的位置
	if(Suffix[idx] != -1)
		return pos - Suffix[idx] + 1;

	//好后缀不在字符串中，子串有重合
	for(int i = idx - 1;i >= 0;i--)
		if(Prefix[i])
			return len - Suffix[i] + 1;

	//好后缀不在模式串中，子串无重合
	return len;
}
int Match(string mod,string pat)
{
	int len1 = pat.length();
	int len =  mod.length();
	//如果主串比子串短，则直接返回匹配失败
	if(len < len1)
		return -1;
	int step = 0;
	for(int i = 0;i < len;i+=step){
		step = 0;
		for(int j = len1 - 1;j >= 0;j--){
			if(pat[j] != mod[i + j]){
				//坏字符的匹配
				int moveB = j-Tables[mod[i + j] - '0'];
				if(moveB < 1) moveB = 1;
				//step小于1是因为我已经部分匹配了，然后在中间某个点失配了，但是我的坏字符在我当前失配的字符的后面，而我们只能找左边的失配的位置的点
				//所以step=1
				//防止只有单个字符失配的情况，也就是不存在后缀的情况下
				int moveG = -INT_MAX;
				if(j < len1 - 1)
					moveG = G_length(len1,j);
				step = max(moveB,moveG);
				break;
			}
		}
		if(step == 0)
			return i + 1;
	}
	//匹配失败
	return -1;
}
int main()
{
	//pat为匹配串，mod为主串
	string pat;
	string mod;
	cin >> mod >> pat;
	Get_BTables(pat);
	Get_GTables(pat);
	int ok = Match(mod,pat);
	cout << ok << endl;
	return 0;
}
