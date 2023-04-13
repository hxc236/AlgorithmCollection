#include <bits/stdc++.h>
#define int long long
#define debug(x) cout<<"#x: "<<x<<endl
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 2e5 + 10, M = 2 * N;

int n, m, s, d;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int dist[N];
int a[N];

int ans, cnt;
vector<int> ans_path, path;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, s});
    dist[s] = 0;
    while(q.size())
    {
        auto t = q.top();
        q.pop();
        int ver = t.first;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                q.push({j, dist[j]});
            }
        }
    }
}

// dfs遍历以x为起点的所有路径
// 标记走过的点，同时剪掉不满足约束条件的分支(此处约束条件是路径长度不超过len)
void dfs(int x, int len, int sum)
{

    if(len > dist[d]) return;
    if(len == dist[d] && x == d)
    {
        cnt ++ ;
        if(sum > ans)
        {
            ans = sum;
            ans_path = path;
        }
    }
    for(int i = h[x]; ~i; i = ne[i])
    {
        int j = e[i];
        if(!st[j] && j != x)
        {
            if(len + w[i] > dist[d]) continue;
            st[j] = true;
            path.push_back(j);
            dfs(j, len + w[i], sum + a[j]);
            path.pop_back();
            st[j] = false;
        }
    }
}

void solve()
{
    memset(h, -1, sizeof h);
    cin >> n >> m >> s >> d;
    for(int i = 0; i < n; i ++ )
        cin >> a[i];

    for(int i = 0; i < m; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    dijkstra();
    memset(st, 0, sizeof st);
    st[s] = true;
    path.push_back(s);
    dfs(s, 0, a[s]);

    cout << cnt << " " << ans << endl;
    for(int i = 0; i < ans_path.size(); i ++ )
        (i == 0) ? cout << ans_path[i] : cout << ' ' << ans_path[i];
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
