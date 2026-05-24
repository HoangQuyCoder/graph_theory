#include "Graph.h"
#include <sstream>
#include <algorithm>
#include <set>
#include <stack>
#include <climits>
using namespace std;

Graph::Graph(int x) {
	this->n = x;
	this->m = 0;
	// Initialize adjacency matrix to 0
	for (int i = 0; i < MAXV; i++) {
		for (int j = 0; j < MAXV; j++) {
			a[i][j] = 0;
		}
	}
}

// Helper functions to synchronize representations
void Graph::syncFromMatrix() {
    // Sync adj and edge from matrix a
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    edge.clear();
    
    bool isUndir = unDirected();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != 0) {
                adj[i].push_back(j);
                if (!isUndir || i < j) {
                    edge.push_back({i, j});
                }
            }
        }
    }
    m = edge.size();
}

void Graph::syncFromEdgeList(bool isUndirected) {
    // Clear matrix and adj
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
        adj[i].clear();
    }
    
    m = edge.size();
    for (auto const& e : edge) {
        int u = e.first;
        int v = e.second;
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            a[u][v] = 1;
            adj[u].push_back(v);
            if (isUndirected) {
                a[v][u] = 1;
                adj[v].push_back(u);
            }
        }
    }
}

void Graph::syncFromAdjList() {
    // Clear matrix and edge
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
    }
    edge.clear();
    
    for (int i = 1; i <= n; i++) {
        for (int v : adj[i]) {
            if (i >= 1 && i <= n && v >= 1 && v <= n) {
                a[i][v] = 1;
            }
        }
    }
    
    bool isUndir = unDirected();
    for (int i = 1; i <= n; i++) {
        for (int v : adj[i]) {
            if (!isUndir || i < v) {
                edge.push_back({i, v});
            }
        }
    }
    m = edge.size();
}

void Graph::readMTK(string path) {
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Khong the mo file: " << path << endl;
        return;
    }

    string firstLine;
    if (!getline(fin, firstLine)) {
        fin.close();
        return;
    }

    stringstream ss(firstLine);
    vector<int> firstRow;
    int val;
    while (ss >> val) {
        firstRow.push_back(val);
    }

    if (firstRow.empty()) {
        fin.close();
        return;
    }

    if (firstRow.size() == 1) {
        // The first line is n
        n = firstRow[0];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                fin >> a[i][j];
            }
        }
    } else {
        // The first line is actually the first row of the matrix
        n = firstRow.size();
        for (int j = 1; j <= n; j++) {
            a[1][j] = firstRow[j - 1];
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                fin >> a[i][j];
            }
        }
    }
    fin.close();

    // Sync other representations
    syncFromMatrix();
}

void Graph::readDSC(string path)
{
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Khong the mo file: " << path << endl;
        return;
    }

    edge.clear();
    fin >> n >> m;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        if (fin >> x >> y) {
            edge.push_back({ x, y });
        }
    }
    fin.close();

    // Default to treating edge list as undirected
    syncFromEdgeList(true);
}

void Graph::readDSK(string path)
{
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Khong the mo file: " << path << endl;
        return;
    }

    // Clear existing adjacency list
    for (int i = 1; i < MAXV; i++) {
        adj[i].clear();
    }

    string firstLine;
    if (!getline(fin, firstLine)) {
        fin.close();
        return;
    }
    
    stringstream ss(firstLine);
    ss >> n;

    for (int i = 1; i <= n; ++i)
    {
        string line;
        if (getline(fin, line)) {
            stringstream line_ss(line);
            int vertexAdj;
            while (line_ss >> vertexAdj)
            {
                adj[i].push_back(vertexAdj);
            }
        }
    }
    fin.close();

    // Sync other representations
    syncFromAdjList();
}

void Graph::writeMTK(string path) {
    ofstream fout(path);
    if (!fout.is_open()) {
        cout << "Khong the mo file de ghi: " << path << endl;
        return;
    }
    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fout << a[i][j] << (j == n ? "" : " ");
        }
        fout << "\n";
    }
    fout.close();
}

void Graph::writeDSC(string path) {
    ofstream fout(path);
    if (!fout.is_open()) {
        cout << "Khong the mo file de ghi: " << path << endl;
        return;
    }
    fout << n << " " << edge.size() << "\n";
    for (auto const& e : edge) {
        fout << e.first << " " << e.second << "\n";
    }
    fout.close();
}

void Graph::writeDSK(string path) {
    ofstream fout(path);
    if (!fout.is_open()) {
        cout << "Khong the mo file de ghi: " << path << endl;
        return;
    }
    fout << n << "\n";
    for (int i = 1; i <= n; i++) {
        for (size_t j = 0; j < adj[i].size(); j++) {
            fout << adj[i][j] << (j + 1 == adj[i].size() ? "" : " ");
        }
        fout << "\n";
    }
    fout.close();
}

void Graph::printMTK() {
    cout << "Ma tran ke:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printDSC()
{
    cout << "Danh sach canh:\n";
    cout << "Dinh dau\tDinh cuoi" << endl;
    for (auto it : edge)
    {
        cout << it.first << "\t\t" << it.second << endl;
    }
}

void Graph::printDSK()
{
    cout << "Danh sach ke:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Danh sach ke cua dinh " << i << ": ";
        for (int x : adj[i])
        {
            cout << x << " ";
        }
        cout << endl;
    }
}

bool Graph::unDirected()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (a[i][j] != a[j][i])
                return false;
        }
    }
    return true;
}

int Graph::sumDeg()
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] != 0)
                cnt++;
        }
    }
    return cnt;
}

int Graph::deg(int i)
{
    int cnt = 0;
    for (int j = 1; j <= n; j++)
    {
        if (a[i][j])
            cnt++;
    }
    return cnt;
}

int Graph::sumDegOut()
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j])
                cnt++;
        }
    }
    return cnt;
}

int Graph::sumDegIn() {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[j][i])
                cnt++;
        }
    }
    return cnt;
}

int Graph::degOut(int i)
{
    int cnt = 0;
    for (int j = 1; j <= n; j++)
    {
        if (a[i][j])
            cnt++;
    }
    return cnt;
}

int Graph::degIn(int i)
{
    int cnt = 0;
    for (int j = 1; j <= n; j++)
    {
        if (a[j][i])
            cnt++;
    }
    return cnt;
}

bool Graph::isGraphFull()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (!a[i][j] && i != j)
                return false;
        }
    }
    return true;
}

bool Graph::isGraphCycle(int u, vector<bool>& visited, int parent)
{
    visited[u] = true;
    for (int v = 1; v <= n; v++)
    {
        if (a[u][v])
        {
            if (!visited[v])
            {
                if (isGraphCycle(v, visited, u))
                {
                    return true;
                }
            }
            else if (v != parent)
            {
                return true;
            }
        }
    }
    return false;
}

bool Graph::isGraphCircle()
{
    if (!unDirected()) return false;
    if (n < 3) return false;
    
    // Check if every vertex has degree 2
    for (int i = 1; i <= n; i++) {
        if (deg(i) != 2) return false;
    }
    
    // Check connectivity
    vector<bool> visited(n + 1, false);
    int visitedCount = 0;
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visitedCount++;
        for (int v = 1; v <= n; v++) {
            if (a[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return visitedCount == n;
}

bool Graph::isBipartite()
{
    vector<int> color(n + 1, -1);
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            q.push(i);

            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                for (int v : adj[u])
                {
                    if (color[v] == -1)
                    {
                        color[v] = 1 - color[u]; // Color vertex v opposite to u
                        q.push(v);
                    }
                    else if (color[v] == color[u])
                    {
                        return false; // Not bipartite
                    }
                }
            }
        }
    }

    return true; // Bipartite
}

void Graph::DFS_helper(int u, vector<bool>& visited) {
    cout << u << ' ';
    visited[u] = true;
    for (int j = 1; j <= n; j++)
    {
        if (a[u][j] && !visited[j])
        {
            DFS_helper(j, visited);
        }
    }
}

void Graph::DFS(int i)
{
    vector<bool> visited(n + 1, false);
    DFS_helper(i, visited);
}

void Graph::BFS(int i)
{
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(i);
    visited[i] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        cout << v << " ";
        for (int x = 1; x <= n; x++)
        {
            if (a[v][x] && !visited[x])
            {
                q.push(x);
                visited[x] = true;
            }
        }
    }
}

void Graph::connectedComponent(int& tplt)
{
    vector<bool> visited(n + 1, false);
    tplt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            tplt++;
            cout << "Cac dinh thuoc thanh phan lien thong thu " << tplt << ": ";
            DFS_helper(i, visited);
            cout << endl;
        }
    }
}

void Graph::readDSC_weighted(string path, bool isUndirected, int &s, int &t) {
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Khong the mo file: " << path << endl;
        return;
    }
    string firstLine;
    if (!getline(fin, firstLine)) {
        fin.close();
        return;
    }
    stringstream ss(firstLine);
    vector<int> vals;
    int val;
    while (ss >> val) {
        vals.push_back(val);
    }
    if (vals.size() >= 2) {
        n = vals[0];
        m = vals[1];
    }
    if (vals.size() >= 4) {
        s = vals[2];
        t = vals[3];
    } else {
        s = 1;
        t = n;
    }

    if (n >= MAXV) {
        cout << "So dinh vuot qua gioi han MAXV = " << MAXV - 1 << endl;
        fin.close();
        return;
    }

    // Clear representations
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = 0;
        }
        adj[i].clear();
    }
    edge.clear();

    int u, v, w;
    for (int i = 0; i < m; i++) {
        if (fin >> u >> v >> w) {
            if (u >= 1 && u <= n && v >= 1 && v <= n) {
                a[u][v] = w;
                adj[u].push_back(v);
                edge.push_back({u, v});
                if (isUndirected) {
                    a[v][u] = w;
                    adj[v].push_back(u);
                }
            }
        }
    }
    fin.close();
}

void Graph::Euler(int v) {
    if (v < 1 || v > n) {
        cout << "Dinh bat dau khong hop le!" << endl;
        return;
    }

    // Create local set-based adjacency list to support easy deletion
    vector<set<int>> local_adj(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int neighbor : adj[i]) {
            local_adj[i].insert(neighbor);
        }
    }

    stack<int> st;
    vector<int> EC;
    st.push(v);
    while (!st.empty()) {
        int x = st.top();
        if (!local_adj[x].empty()) {
            int y = *local_adj[x].begin();
            st.push(y);
            // Erase undirected edge (x, y)
            local_adj[x].erase(y);
            local_adj[y].erase(x);
        } else {
            st.pop();
            EC.push_back(x);
        }
    }

    reverse(EC.begin(), EC.end());
    cout << "Chu trinh/Duong di Euler: ";
    for (int x : EC) {
        cout << x << " ";
    }
    cout << endl;
}

// Disjoint Set Union (DSU) structure helper for Kruskal
struct KruskalDSU {
    vector<int> parent;
    vector<int> sz;
    KruskalDSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }
    bool Union(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

void Graph::Kruskal() {
    struct KruskalEdge {
        int u, v, w;
    };
    
    // Populate local edges
    vector<KruskalEdge> local_edges;
    for (auto const& e : edge) {
        local_edges.push_back({e.first, e.second, a[e.first][e.second]});
    }

    // Sort edges by weight
    sort(local_edges.begin(), local_edges.end(), [](const KruskalEdge& e1, const KruskalEdge& e2) {
        return e1.w < e2.w;
    });

    KruskalDSU dsu(n);
    vector<KruskalEdge> mst;
    int total_weight = 0;

    for (const auto& e : local_edges) {
        if (mst.size() == (size_t)(n - 1))
            break;
        if (dsu.Union(e.u, e.v)) {
            mst.push_back(e);
            total_weight += e.w;
        }
    }

    if (mst.size() != (size_t)(n - 1)) {
        cout << "Do thi khong lien thong!" << endl;
    } else {
        cout << "MST: " << total_weight << endl;
        for (auto const& it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

void Graph::Prim(int u) {
    if (u < 1 || u > n) {
        cout << "Dinh bat dau khong hop le!" << endl;
        return;
    }

    struct PrimEdge {
        int u, v, w;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    vector<bool> used(n + 1, false);
    vector<int> d(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    vector<PrimEdge> mst;
    int res = 0;

    d[u] = 0;
    Q.push({0, u});

    while (!Q.empty()) {
        auto top = Q.top();
        Q.pop();
        int dinh = top.second;
        int trongso = top.first;

        if (used[dinh])
            continue;

        res += trongso;
        used[dinh] = true;

        if (u != dinh) {
            mst.push_back({dinh, parent[dinh], trongso});
        }

        for (int y : adj[dinh]) {
            int w = a[dinh][y];
            if (!used[y] && w < d[y]) {
                Q.push({w, y});
                d[y] = w;
                parent[y] = dinh;
            }
        }
    }

    int visitedCount = 0;
    for (int i = 1; i <= n; i++) {
        if (used[i]) visitedCount++;
    }

    if (visitedCount < n) {
        cout << "Do thi khong lien thong!" << endl;
    } else {
        cout << "MST: " << res << endl;
        for (auto const& it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

void Graph::Dijkstra(int s, int t) {
    if (s < 1 || s > n || t < 1 || t > n) {
        cout << "Dinh nguon hoac dinh dich khong hop le!" << endl;
        return;
    }

    const long INF = 1e9;
    vector<long> d(n + 1, INF);
    vector<int> pre(n + 1, -1);
    d[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    Q.push({0, s});

    while (!Q.empty()) {
        auto top = Q.top();
        Q.pop();
        int kc = top.first;
        int u = top.second;

        if (kc > d[u])
            continue;

        for (int v : adj[u]) {
            int w = a[u][v];
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push({d[v], v});
                pre[v] = u;
            }
        }
    }

    if (d[t] == INF) {
        cout << "Khong co duong di tu dinh " << s << " den dinh " << t << "!" << endl;
    } else {
        cout << "Khoang cach ngan nhat tu " << s << " den " << t << ": " << d[t] << endl;
        vector<int> path;
        int curr = t;
        while (curr != -1) {
            path.push_back(curr);
            curr = pre[curr];
        }
        reverse(path.begin(), path.end());
        cout << "Duong di: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 == path.size() ? "" : " -> ");
        }
        cout << endl;
    }
}
