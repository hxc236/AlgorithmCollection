#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10, M = 2 * N;


int n, m;
int fa[N][18];
int dist[N][18];
int depth[N];
int h[N], w[M], e[M], ne[M], idx;
bool v[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u, int level)
{
    v[u] = true;
    depth[u] = level;
    for(int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(!v[j])
        {
            fa[j][0] = u;
            dist[j][0] = w[i];
            for(int k = 1; k <= 16; k ++ )
            {
                fa[j][k] = fa[fa[j][k - 1]][k - 1];
                dist[j][k] = dist[j][k - 1] + dist[fa[j][k - 1]][k - 1];
            }
            dfs(j, level + 1);
        }
    }
}

int lca(int a, int b, int& distance)
{
    distance = 0;
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = 16; k >= 0; k -- )
        if(depth[fa[a][k]] >= depth[b])
        {
            distance += dist[a][k];
            a = fa[a][k];
        }

    if(a == b) return a;
    for(int k = 16; k >= 0; k -- )
        if(fa[a][k] != fa[b][k])
        {
            distance += dist[a][k];
            distance += dist[b][k];
            a = fa[a][k];
            b = fa[b][k];
        }
    distance += dist[a][0] + dist[b][0];
    return fa[a][0];
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(depth, 0x3f, sizeof depth);
    for(int i = 0; i < n - 1; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    int root = 1;
    depth[0] = 0;
    dfs(root, 1);

    for(int i = 0; i < m; i ++ )
    {
        int x, y;
        cin >> x >> y;
        int distance;
        int p = lca(x, y, distance);
        printf("%d\n", distance);
    }

    return 0;
}
