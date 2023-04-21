#include <bits/stdc++.h>
#define int long long
#define debug(x) cout<<"#x: "<<x<<endl
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 55, M = 2 * N;
const int INF = 1e18;

int n, m, k;
set<int> st[N];


void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> m;
        for(int j = 0; j < m; j ++ )
        {
            int x; cin >> x;
            st[i].insert(x);
        }
    }
    cin >> k;
    while(k -- )
    {
        int a, b;
        cin >> a >> b;
        int * res1 = (int *)malloc(sizeof(int) * (st[a].size() + st[b].size() + 5));
        int * p1 = set_union(st[a].begin(), st[a].end(), st[b].begin(), st[b].end(), res1);
        int len1 = p1 - res1;
        int * res2 = (int *)malloc(sizeof(int) * (min(st[a].size(), st[b].size()) + 5));
        int * p2 = set_intersection(st[a].begin(), st[a].end(), st[b].begin(), st[b].end(), res2);
        int len2 = p2 - res2;
       cout << len1 << ' ' << len2 << endl;
       for(int i = 0; i < len1; i ++ )
           cout << res1[i] << ' ';
       cout << endl;
       for(int i = 0; i < len2; i ++ )
           cout << res2[i] << ' ';
       cout << endl;
        free(res1);
        free(res2);
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
