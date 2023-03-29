#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 4e4 + 10, M = 2 * N;

int fa[N][16];
int depth[N];

int n, m;

int h[N], e[M], ne[M], idx;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}



void dfs(int u, int d)
{
    depth[u] = d;
    for(int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(depth[j] == 0x3f3f3f3f)
        {
            fa[j][0] = u;
            for(int k = 1; k <= 15; k ++ )
                fa[j][k] = fa[fa[j][k - 1]][k - 1];
            dfs(j, d + 1);
        }
    }
}

int lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = 15; k >= 0; k -- )
        if(depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    
    if(a == b) return a;
    for(int k = 15; k >= 0; k -- )
        if(fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

int main()
{
    cin >> n;
    int root = -1;
    memset(h, -1, sizeof h);
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0;
    for(int i = 0; i < n; i ++ )
    {
        int a, b;
        cin >> a >> b;
        if(b == -1) root = a;
        else add(a, b), add(b, a);
    }
    depth[root] = 1;
    dfs(root, 1);
    
    cin >> m;
    for(int i = 0; i < m; i ++ )
    {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        if(a == p) puts("1");
        else if(b == p) puts("2");
        else puts("0");
    }
    return 0;
}