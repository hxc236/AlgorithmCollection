#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010, M = 1010;
int n, m;
int v[N], w[N];
int f[M];

int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i ++ )
		cin >> w[i] >> v[i];

	for(int i = 0; i < n; i ++ )
		for(int j = m; j >= w[i]; j -- )
			f[j] = max(f[j], f[j - w[i]] + v[i]);

	cout << f[m] << endl;
	return 0;
}
