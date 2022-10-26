#include "bits/stdc++.h"

using namespace std;
unsigned int seed = 1e9+7;
int Random()
{
    seed = (seed << 10) + (seed >> 10) + seed + 1e9 + 7;
    return seed / 2;
}
int main() {
    mt19937 myrand(time(0));
    //基于线性同余方法随机生成
    cout << Random() << endl;
    //基于梅森缠绕器随机生成
    cout << myrand() << endl;
    srand(time(0));
    //random_shuffle配合随机函数随机生成数字 速度很快
    vector <long long> v = {1,3,2};
    for(int i = 1;i <= 10;i++) {
        random_shuffle(v.begin(),v.end());
        for(auto x:v) cout << x << ' ';
        cout << endl;
    }
    
    return 0;
}

