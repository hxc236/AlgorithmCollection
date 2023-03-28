#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010, M = 1010;

int n, m;	// n个物品，最大容量m
int v[N], w[N];	//价值和重量 v[i], w[i]
int f[M];	// 最大容量为j的最大价值f[j]

int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i ++ )
		cin >> w[i] >> v[i];

	for(int i = 0; i < n; i ++ )
		for(int j = w[i]; j <= m; j ++ )
			f[j] = max(f[j], f[j - w[i]] + v[i]);

	cout << f[m] << endl;
	return 0;
}
