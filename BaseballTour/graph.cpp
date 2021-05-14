#include "graph.h"

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
void Graph<Type>::addEdge(Type& objU, Type& objV, int weight) {
    int u = getIndex(objU);
    int v = getIndex(objV);
    Edge uEdge = {u, v, weight};
    Edge vEdge = {v, u, weight};
    adjMatrix[u][v] = uEdge;
    adjMatrix[v][u] = vEdge;
}

template<class Type>
int Graph<Type>::getIndex(Type& obj) {
    auto it = find(nodeList.begin(), nodeList.end(), obj);
    return it - nodeList.begin();
}

template<class Type>
int Graph<Type>::startDFS(Type& start) {
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
         distTraveled += it->weight + dfs(it->v, visited);
    }
    return distTraveled;
}

template<class Type>
int Graph<Type>::startBFS(Type& start) {
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
