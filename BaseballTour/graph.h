#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Graph class based on adjacency matrix
 */

// struct representation of edge in graph
struct Edge {

    // index of first node
    int u;

    // index of second node
    int v;

    int weight;
};

template <class Type>
class Graph
{
public:
    Graph();

    /**
     * @brief Adds node to graph
     * @param obj Object to add to graph
     */
    void addNode(Type obj);

    /**
     * @brief Add edge between two nodes
     * @param objU
     * @param objV
     * @param weight
     */
    void addEdge(Type& objU, Type& objV, int weight);

private:

    /**
     * @brief Helper function to get index of obj
     * @param obj object to be found
     * @return index of obj
     */
    int getIndex(Type& obj);

    /**
     * @brief size number of nodes
     */
    int size;

    /**
     * @brief Adjacency matrix
     */
    vector<vector<Edge>> adjMatrix;


    /**
     * @brief List of data associated with index
     */
    vector<Type> nodeList;

};

#endif // GRAPH_H
