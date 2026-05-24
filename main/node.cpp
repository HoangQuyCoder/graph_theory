#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define maxV 99
using namespace std;

typedef struct Node
{
    int v; // adjacent vertices
    struct Node *next;
} node;

int n, m;
node *p;
int a[1001][1001]; // matrix adjacency

node *adj[maxV];
vector<pair<int, int>> edge; // edge list

void readAdjList()
{
    string s, num;
    cin >> n;

    cin.ignore();
    for (int i = 1; i <= n; ++i)
    {
        getline(cin, s);
        stringstream ss(s);
        while (ss >> num)
        {
            p = new node;
            p->v = stoi(num);
            p->next = adj[i];
            adj[i] = p;
        }
    }
}

void addEdge(int u, int v)
{
    node *newNode = new node;
    newNode->v = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void printAdjMatix()
{
    cout << "Ma tran ke" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void printEdgeList()
{
    cout << "Dinh dau\tDinh cuoi" << endl;
    for (auto it : edge)
    {
        cout << it.first << "\t\t" << it.second << endl;
    }
}

void printAdjList()
{
    for (int i = 1; i <= n; i++)
    {
        cout << "Danh sach ke cua dinh " << i << ":";
        p = adj[i];
        while (p != NULL)
        {
            cout << " " << p->v;
            p = p->next;
        }
        cout << endl;
    }
}

void MTK_to_DSK()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j])
            {
                p = new node;
                p->v = j;
                p->next = adj[i];
                adj[i] = p;
            }
        }
    }
}

void DSC_to_DSK()
{
    cin >> n >> m;

    int x, y;
    for (int j = 1; j <= m; j++)
    {
        cin >> x >> y;

        p = new node;
        p->v = y;
        p->next = adj[x];
        adj[x] = p;

        // if the graph is directed, remove this line
        p = new node;
        p->v = x;
        p->next = adj[y];
        adj[y] = p;
    }
}

void DSK_to_DSC()
{
    readAdjList();

    for (int i = 1; i <= n; i++)
    {

        p = adj[i];
        while (p != NULL)
        {
            if (p->v > i) // if the graph is directed, remove this condition
                edge.push_back({i, p->v});
            p = p->next;
        }
    }
}

void DSK_to_MTK()
{
    readAdjList();
    for (int i = 1; i <= n; i++)
    {
        p = adj[i];
        while (p != NULL)
        {
            a[i][p->v] = 1;
            p = p->next;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    for (int i = 1; i <= n; i++)
    {
        adj[i] = NULL;
    }
    DSK_to_DSC();
    // printAdjList();
    // printAdjMatix();
    printEdgeList();
    return 0;
}
