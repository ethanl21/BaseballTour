#include "graph.h"
#include <QDebug>
#include <QString>

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
         distTraveled += it->weight + dfs(it->v, visited);
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


// explicitly instantiate template so it's compiled
template class Graph<QString>;
