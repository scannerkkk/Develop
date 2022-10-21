#include "bits/stdc++.h"
using namespace std;
void sub(vector <int> &A,vector <int> &B)
{
    int t = 0;
    vector <int> res;
    for(int i = 0;i < B.size();i++) {
        if(t) A[i] -= t,t = 0;
        if(A[i] >= B[i]) A[i] -= B[i];
        else {
            A[i] = A[i] + 10 - B[i];
            t = 1;
        }
    }
    if(t) A[B.size()] -= 1;
    while(A.size() > 1 && A.back() == 0) A.pop_back();
}
int cmp(vector <int> &A,vector <int> &B)
{
    if(A.size() < B.size()) return -1;
    if(A.size() > B.size()) return 1;
    for(int i = A.size() - 1;i >= 0;i--) {
        if(A[i] > B[i]) return 1;
        if(A[i] < B[i]) return -1;
    }
    return 0;
}
void div(string s1,string s2)
{
    if(s1.size() < s2.size()) {
        cout << 0 << endl;
        cout << s2 << endl;
        return ;
    }
    vector <int> A,B,C;
    while(s1.size()) A.push_back(s1.back() - '0'),s1.pop_back();
    while(s2.size()) B.push_back(s2.back() - '0'),s2.pop_back();
    int d = A.size() - B.size();
    for(int i = 1;i <= d;i++) C.push_back(0);
    for(int i = 0;i < B.size();i++) C.push_back(B[i]);
    B = C;
    int tmp;
    vector <int> Z,P;
    for(int j = 0;j <= d;j++) {
        P.clear();
        int res = 0;
        while((tmp = cmp(A,B)) >= 0) {
            res ++;
            sub(A,B);
        }
        Z.push_back(res);
        if(tmp < 0 && B.size() && !B[0]) {
            for(int i = 1;i < B.size();i++) P.push_back(B[i]);
            B = P;
        }
    }
    reverse(Z.begin(),Z.end());
    while(Z.size() > 1 && Z.back() == 0) Z.pop_back();
    while(A.size() > 1 && A.back() == 0) A.pop_back();
    //商
    while(Z.size()) cout << Z.back(),Z.pop_back();
    cout << endl;
    //模
    while(A.size()) cout << A.back(),A.pop_back();
}
int main()
{
    string s1,s2;
    cin >> s1 >> s2;
    div(s1,s2);
    return 0;
}
