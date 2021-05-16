#include "graph.h"
#include <QDebug>

template<class Type>
Graph<Type>::Graph()
{
    size = 0;
}

template<class Type>
void Graph<Type>::addNode(Type obj) {
    nodeList.push_back(obj);
    size++;
    adjMatrix.resize(size);
    for (auto it = adjMatrix.begin(); it != adjMatrix.end(); it++)
        it->resize(size);
}

template<class Type>
void Graph<Type>::addEdge(const Type& objU, const Type& objV, int weight) {
    int u = getIndex(objU);
    int v = getIndex(objV);
    Edge uEdge = {u, v, weight};
    Edge vEdge = {v, u, weight};
    adjMatrix[u][v] = uEdge;
    adjMatrix[v][u] = vEdge;

}

template<class Type>
int Graph<Type>::getIndex(const Type& obj) {
    auto it = find(nodeList.begin(), nodeList.end(), obj);
    return it - nodeList.begin();
}

template<class Type>
int Graph<Type>::startDFS(const Type& start) {
    vector<bool> visited(size, false);
    dfsOrder.resize(0);
    return dfs(getIndex(start), visited);
}

template<class Type>
int Graph<Type>::dfs(int v, vector<bool>& visited) {

    int distTraveled = 0;
    visited[v] = true;
    dfsOrder.push_back(nodeList[v]);

    // create adjacency list of valid nodes
    // and sort in order of increasing weight
    vector<Edge> adjList;
    for (auto it = adjMatrix[v].begin(); it != adjMatrix[v].end(); it++) {
        // find valid edge
        if (it->weight != 0 && !visited[it->v])
            adjList.push_back(*it);
    }
    sort(adjList.begin(), adjList.end(), compareWeight);

    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        distTraveled += it->weight;
        distTraveled += dfs(it->v, visited);
    }
    return distTraveled;
}

template<class Type>
int Graph<Type>::startBFS(const Type& start) {
    vector<bool> visited(size, false);
    queue<int> queue;
    int distTraveled = 0;

    int currNode = getIndex(start);
    queue.push(currNode);
    visited[currNode] = true;

    while (!queue.empty()) {
        currNode = queue.front();
        bfsOrder.push_back(nodeList[currNode]);
        queue.pop();

        // create adjacency list of valid edges
        vector<Edge> adjList;
        for (auto it = adjMatrix[currNode].begin();
             it != adjMatrix[currNode].end(); it++) {
            if (it->weight != 0 && !visited[it->v])
                adjList.push_back(*it);
        }
        sort(adjList.begin(), adjList.end(), compareWeight);

        for (auto it = adjList.begin(); it != adjList.end(); it++) {
            queue.push(it->v);
            visited[it->v] = true;
            distTraveled += it->weight;
        }
    }

    return distTraveled;
}

template<class Type>
int Graph<Type>::startMST() {

    priority_queue<node, vector<node>, greater<node>> pq;

    // starting node
    int src = 0;

    // parent of each node in MST
    vector<int> parent(size, -1);
    // distance to each node
    vector<int> distance(size, INT_MAX);
    vector<bool> inMST(size, false);

    // starting point
    pq.push(make_pair(0, src));
    distance[src] = 0;

    // temp adjacency list
    vector<Edge> adjList;

    while (!pq.empty()) {
        // look at first node in the priority queue
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        // get valid edges
        for (auto it = adjMatrix[u].begin(); it != adjMatrix[u].end(); it++) {
            if (it->weight > 0)
                adjList.push_back(*it);
        }

        // iterate through all adjacent vertices
        for (auto i = adjList.begin(); i != adjList.end(); i++)
        {
            int v = i->v;
            int dist = i->weight;

            // if v is valid and closer, push onto pq
            if (!inMST[v] && distance[v] > dist)
            {
                distance[v] = dist;
                pq.push(make_pair(distance[v], v));
                parent[v] = u;
            }
        }

        adjList.clear();
    }

    int weight;
    mstString = "";
    for (int i = 0; i < size; i++) {
        if (parent[i] != -1) {
            mstString += nodeList[parent[i]] + " - " + nodeList[i];
            weight = adjMatrix[parent[i]][i].weight;
            mstString += ": " + QString::number(weight);
            mstString += "\n";
        }
    }

    int total = 0;
    for (int dist : distance)
            total += dist;
    return total;
}

template<class Type>
int Graph<Type>::startDijkstra(const Type& start, const Type& dest) {
    vector<vector<int>> T;
    T = DijkstraPaths(start);
    return T[getIndex(dest)][1];
}

template<class Type>
int Graph<Type>::startMultiDijkstra(vector<Type> nodes, const Type& start) {
    dijkstraOrder.clear();
    return multiDijkstra(nodes, start);
}

template<class Type>
int Graph<Type>::multiDijkstra(vector<Type> nodes, const Type& start) {

    dijkstraOrder.push_back(start);

    // remove starting point from nodes
    auto pos = find(nodes.begin(), nodes.end(), start);
    if (pos != nodes.end())
        nodes.erase(pos);

    // base case
    if (nodes.size() < 1)
        return 0;

    vector<vector<int>> T;
    T = DijkstraPaths(start);

    // find closest in selected nodes
    int distance = INT_MAX;
    int closest = getIndex(start);
    int i = 0;
    for (Type node : nodes) {
        i = getIndex(node);
        if (T[i][1] < distance) {
            closest = i;
            distance = T[i][1];
        }
    }

    distance += multiDijkstra(nodes, nodeList[closest]);
    return distance;
}

template<class Type>
vector<vector<int>> Graph<Type>::DijkstraPaths(const Type& start) {
    vector<vector<int>> T(size);
    for (auto it = T.begin(); it != T.end(); it++)
        it->resize(3);

    for (unsigned int i = 0; i < nodeList.size(); i++) {
        T[i][0] = -1;       // parent node
        T[i][1] = INT_MAX;  // distance
        T[i][2] = 0;        // in SPT set (0=false, 1=true)
    }

    int startIndex = getIndex(start);
    T[startIndex][0] = startIndex;
    T[startIndex][1] = 0;
    T[startIndex][2] = 1;

    for (unsigned int i = 0; i < adjMatrix[startIndex].size(); i++) {
        T[adjMatrix[startIndex][i].v][0] = startIndex;
        T[adjMatrix[startIndex][i].v][1] = adjMatrix[startIndex][i].weight;
    }

    int shortestIndex = -1;
    int shortest = INT_MAX;
    for (int i = 0; i < (int)nodeList.size(); i++) {
        if (T[i][2] == 0){
            if (T[i][1] < shortest) {
                shortestIndex = i;
                shortest = T[i][1];
            }
        }
    }

    while (shortestIndex != -1) {
        for (unsigned int i = 0; i < adjMatrix[shortestIndex].size(); i++) {
            int current = adjMatrix[shortestIndex][i].v;

            if (T[current][2] == 0) {
                if ((T[shortestIndex][1] + adjMatrix[shortestIndex][i].weight) < T[current][1]) {
                    T[current][1] = T[shortestIndex][1] + adjMatrix[shortestIndex][i].weight;
                    T[current][0] = shortestIndex;
                }
            }
        }

        T[shortestIndex][2] = 1;

        shortestIndex = -1;
        shortest = INT_MAX;
        for (int i  = 0; i < (int)nodeList.size(); i++) {
            if (T[i][2] == 0){
                if (T[i][1] < shortest) {
                    shortestIndex = i;
                    shortest = T[i][1];
                }
            }
        }
    }

    return T;
}

template<class Type>
int Graph<Type>::startShortestPath(const Type& start) {
    shortestOrder.clear();
    return shortestPath(start);
}

template<class Type>
int Graph<Type>::shortestPath(const Type& start) {

    int curr = getIndex(start);
    int next = 0;
    vector<bool> visited(size, false);

    int distance = 0;
    int min;
    do {
        visited[curr] = true;
        shortestOrder.push_back(nodeList[curr]);
        min = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (adjMatrix[curr][j].weight > 0 && !visited[j]
                    && adjMatrix[curr][j].weight < min) {
                next = j;
                min = adjMatrix[curr][next].weight;
            }
        }
        distance += adjMatrix[curr][next].weight;
        curr = next;
    } while(!visited[curr]);
    return distance;
}


// explicitly instantiate template so it's compiled
template class Graph<QString>;
