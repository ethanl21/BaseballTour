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
