#include <stdio.h>
#include<queue>

int visited[100][100] = {0};
int dist[100][100] = {0};
int G[10000][10000] = {0};
typedef struct
{
    int x;
    int y;
}pair;
pair prev[100][100];

int min(int u, int v)
{
    if (u > v) return v;
    else return u;
}

void djkstra(int m)//m là số đỉnh của đồ thị
{
    int i, j, k;
    queue<int> q;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            dist[i][j] = -1;
        }
    }

    for (i = 0; i < m; i++)
    {
        dist[i][i] = 0;
        q.push(i);
        while(!q.empty())
        {
            k = q.top();
            q.pop();
            for (j = 0; j < m; i++)
            if (G[k][j]) //Tất cả những đỉnh kề với đỉnh vừa lấy ra khỏi hàng đợi
            {
                if (!visited[j][k])
                {
                    if (dist[i][j] == -1)
                    {
                        dist[i][j] = dist[i][k] + G[k][j];
                        dist[j][i] = dist[i][k] + G[k][j];
                        visited[j][k] = 1; visited[k][j] = 1;
                    }
                    else
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + G[k][j]);
                        visited[j][k] = 1; visited[k][j] = 1;
                    }
                }
            }
        }
    }
}
//Kết thúc tt này các biến sau có giá trị của các phần tử thay đổi: dist[][], visited[][]

void inRaDuongDi(int a, int b)
{
    if (prev[a][b].x == -1 && prev[a][b].y == -1)
    {
        return;
    }
    inRaDuongDi(prev[a][b].x, prev[a][b].y);
    printf("%d %d\n", a, b);
}

int main()
{
    int n, m, x, y, w, a, b, c, d, r;
    FILE* p = fopen("input.txt", "w");
    FILE* q = fopen("output.txt", "r");

    scanf("%d %d\n", &n, &m);
    int i, j;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d\n", &x, &y, &w);
        G[x][y] = w;
        G[y][x] = w;
    }
    scanf("%d %d %d %d\n", &a, &b, &c, &d);
    scanf("%d", &r);

    djkstra(m);
    //Làm mới mảng visited[]
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            prev[i][j].x = 0; prev[i][j].y = 0;
        }
    }

    queue <int>p, <int>q;
    p.push(a); q.push(b);
    int e, f;
    prev[a][b].x = -1; prev[a][b].y = -1;
    while (!p.empty() && !q.empty())
    {
        e = p.top(); f = q.top();
        p.pop(); q.pop();
        for (i = 0; i < m; i++)
        {
            if (G[f][i] && dist[i][f] > r && !visited[i][f])
            {
                p.push(i); q.push(f);
                visited[i][f] = 1; //Giữ nguyên đỉnh f
                prev[i][f].x = e; prev[i][f].y = f;
            }
        }

        for (i = 0; i < m; i++)
        {
            if (G[e][i] && dist[i][e] > r && !visited[e][i])
            {
                p.push(e); q.push(i);
                visited[e][i] = 1; //giữ nguyên đỉnh e
                prev[e][i].x = e; prev[e][i].y = f;
            }
        }
    }

    if (prev[c][d].x == 0 && prev[c][d].y == 0)
    {
        printf("Không thể!");
        return 1;
    }
    else
    {
        inRaDuongDi(c, d);
    }
}