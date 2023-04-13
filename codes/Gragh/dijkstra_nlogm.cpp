#include <bits/stdc++.h>
#define int long long
#define debug(x) cout<<"#x: "<<x<<endl
using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 2e6 + 10, M = 2 * N;
const int INF = 1e18;

int n, m, s, d;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int dist[N], num[N];        
// dist[i]: 起点到i的最短距离
// num[i]: 起点到i的最短路条数
int sum[N], pre[N];         
// sum[i]: 起点到i的节点权值累加和
// pre[i]: i的前一个点
int a[N];

vector<int> ans_path;

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
    num[s] = 1;
    sum[s] = a[s];
    pre[s] = -1;

    while(q.size())
    {
        auto t = q.top();
        q.pop();
        int ver = t.second;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[ver] + w[i])
            {
                dist[j] = dist[ver] + w[i];
                q.push({dist[j], j});
                num[j] = num[ver];
                sum[j] = sum[ver] + a[j];
                pre[j] = ver;
            }
            else if(dist[j] == dist[ver] + w[i])
            {
                num[j] += num[ver];
                if(sum[ver] + a[j] > sum[j])
                {
                    sum[j] = sum[ver] + a[j];
                    pre[j] = ver;
                }
            }
        }
    }
}

void getPath()
{
    stack<int> stk;
    while(pre[d] != -1)
    {
        stk.push(d);
        d = pre[d];
    }
    stk.push(d);
    while(stk.size())
    {
        ans_path.push_back(stk.top());
        stk.pop();
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

    cout << num[d] << " " << sum[d] << endl;
    getPath();
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
