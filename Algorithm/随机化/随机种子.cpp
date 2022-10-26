#include <ctime>
#include <iostream>
#include <random>

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
    return 0;
}

