#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
int a[N];

void quickSort(int * a, int l, int r)
{
	if(l > r) return ;
	int i = l - 1, j = r + 1, x = a[l + r >> 1];
	while(i < j)
	{
		do i ++ ; while(a[i] < x);
		do j -- ; while(a[j] > x);
		if(i < j) swap(a[i], a[j]);
	}
	quickSort(a, l, j), quickSort(a, j + 1, r);
}

int main()
{
	cin >> n;
	for(int i = 0; i < n; i ++ )
		cin >> a[i];
	quickSort(a, 0, n - 1);
	for(int i = 0; i < n; i ++ )
		cout << a[i] << ' ';
	return 0;
}
