#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1010, M = 2010, S = 1010;
const int NN = N * M * log2(S);

int n, m;
int w[NN], v[NN];
int f[NN];

int main()
{
    cin >> n >> m;
    int cnt = 0;
    for(int i = 0; i < n; i ++ )
    {
        int ww, vv, ss;
        cin >> ww >> vv >> ss;
        int k = 1;
        while(ss >= k)      // 一共ss个物品，二进制拆分
        {
            cnt ++ ;
            w[cnt] = k * ww;
            v[cnt] = k * vv;
            ss -= k;
            k <<= 1;
        }
        if(ss > 0)      // 余下不够2的幂次方的单独打包
        {
            cnt ++ ;
            w[cnt] = ss * ww;
            v[cnt] = ss * vv;
        }
    }
    
    for(int i = 1; i <= cnt; i ++ )     // cnt最大为 n * log(s)
        for(int j = m; j >= w[i]; j -- )
            f[j] = max(f[j], f[j - w[i]] + v[i]);
        
    cout << f[m] << endl;
    
    return 0;
}
