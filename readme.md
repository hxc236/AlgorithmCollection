# 算法模板

整理一些常见的**算法模板**和**模型转化**的方法

___

## 基础算法



### 快速排序



### 第k大数



### 归并排序



### 二分

#### 整数二分

本质：在一个区间$[l, r]$上，能够找到某个性质，把整个区间一分为二，在右半边区间满足该性质，在左半边区间不满足该性质，两半边没有交点，则可以使用二分寻找性质的边界。

性质1和性质2真假性相反。
$$
(l)[————————(满足性质1)——————(边界1)][(边界2)————(满足性质2)————————](r)
$$
既可以二分出边界1，也可二分求出边界2。

求边界1：

```cpp
while(l < r)
{
    int mid = l + r + 1 >> 1;
    if(check(mid)) l = mid; // check检查mid是不是满足性质1
    else r = mid - 1;
}
// l == r == 边界1
```

求边界点2：

```cpp
while(l < r) 
{
    int mid = l + r >> 1;
    if(check(mid)) r = mid; // check检查mid是不是满足性质2
    else l = mid + 1;
}	
//l == r == 边界2
```








## 动态规划
___
### 背包模型


#### 01背包

> $n$个物品，最大容量为$m$，第$i$个物品的体积和价值分别为$w_i$，$v_i$，求最大价值。
> **特殊之处：每个物品只能选1次。**

$$
\begin{aligned}
& 状态表示：f(i, j)表示从前i个物品中选，最大容量为j的最大价值\\
& 状态计算:f(i, j) = max(f(i - 1, j), f(i - 1, j - w_i) + v_i)
\end{aligned}
$$
伪代码：
```cpp
f[0] = 0;
for(int i = 0; i < n; i ++ )    // 枚举物品
    for(int j = m; j >= w[i]; j -- )    // 倒序枚举容量
        f[j] = max(f[j], f[j - w[i]] + v[i]);   //状态转移
```

#### 完全背包


> $n$个物品，最大容量为$m$，第$i$个物品的体积和价值分别为$w_i$，$v_i$，求最大价值。
> **特殊之处：每个物品可以选无限次。**


$$
\begin{aligned}
& 状态表示：f(i, j)表示从前i个物品中选，最大容量为j的最大价值\\
& 状态计算:f(i, j) = max(f(i - 1, j), f(i, j - w_i) + v_i)
\end{aligned}
$$
伪代码：
```cpp
f[0] = 0;
for(int i = 0; i < n; i ++ )    // 枚举物品
    for(int j = m; j >= w[i]; j -- )    // 正序枚举容量
        f[j] = max(f[j], f[j - w[i]] + v[i]);   // 状态转移
```

#### 多重背包
> $n$个物品，最大容量为$m$，第$i$个物品的体积、价值和数量分别为$w_i$，$v_i$，$s_i$，求最大价值。
> **特殊之处：每个物品只能选$s_i$次。**

$$
\begin{aligned}
& 状态表示：f(i, j)表示从前i个物品中选，最大容量为j的最大价值\\
& 状态计算:f(i,j)=max(f(i-1,j),f(i−1,j−v)+w, f(i−1,j−2v)+2w,…,f(i−1,j−kv)+kw)
\end{aligned}
$$

朴素 $O(nms)$
```cpp
for(int i = 1; i <= n; ++i)     // 枚举物品
        for(int j = 0; j <= m; ++j)     // 枚举容量
            for(int k = 0; k <= s[i] && k * v[i] <= j; ++k)     // 枚举物品个数
                    f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
```
二进制优化 $O(nmlog(S))$

> 利用$2^0,2^1,2^2,...,2^n$可以组合出小于$2^{n + 1}$的任意数，将每种物品的$s_i$个打包成$log(s)$个$2^k$个该种物品，转化成01背包来做，此时共有$n*log(s)$个物品，每种物品选一次，容量为$m$,求最大价值。

```cpp
const int N = 110, M = 110, S = 110;
const int NN = N * M * S;
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
        while(ss >= k) {
            cnt ++ ; w[cnt] = k * ww; v[cnt] = k * vv; ss -= k; k <<= 1;
        }
        if(ss > 0) {
            cnt ++ ; w[cnt] = ss * ww; v[cnt] = ss * vv;
        }
    }
    
    for(int i = 1; i <= cnt; i ++ )     // cnt最大为 n * log(s)
        for(int j = m; j >= w[i]; j -- )
            f[j] = max(f[j], f[j - w[i]] + v[i]);
        
    cout << f[m] << endl;
    
    return 0;
}
```

单调队列优化 $O(nm)$
