#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;

int n, a[N];

int Bsearch1(int *a, int l, int r, int x) // the first >= x
{
	while(l < r)
	{
		int mid = l + r >> 1;
		if(a[mid] >= x) r = mid;
		else l = mid + 1;
	}
	return l;
}

int Bsearch2(int *a, int l, int r, int x) 	// the last <= x
{
	while(l < r)
	{
		int mid = l + r + 1 >> 1;
		if(a[mid] <= x) l = mid;
		else r = mid - 1;
	}
	return l;
}

int main()
{
	cin >>  n;
	for(int i = 0; i < n; i ++ ) cin >> a[i];
	
	// find the first >= x or > x element
	int idx = Bsearch1(a, 0, n - 1, x);
	
	// find the last <= x or < x element
	int idx2 = Bsearch2(a, 0, n - 1, x);


	return 0;
}
