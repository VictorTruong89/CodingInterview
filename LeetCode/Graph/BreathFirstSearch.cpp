/**
 * @file BreathFirstSearch.cpp
 * @author VictorTruong
 * 
 * @brief Fundamental knowledge & Sample Code & Cheatsheet of BFS
 * @date 2022-07-07
 * @link https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/ @endlink
 * 
 */
#include <bits/stdc++.h>

/**
 * @brief Sample code of a typical Breath First Search algorithm
 */
// Graph class represents a directed graph using adjacency list representation
class Graph {
    // Number of vertices
    int numVertices;

    // Pointer to an array contianing adjency lists
    std::vector< std::list<int> > adj;

public:
    Graph(int V) {
        this->numVertices = V;
        adj.resize(V);
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void BreadthFirstSearch(int s) {
        // Mark all vertices as not visited
        std::vector<bool> visited;
        visited.resize(numVertices, false);

        // Create a queue for BFS
        std::list<int> queue;

        // Mark the current Node as visited and enqueue it
        visited[s] = true;
        queue.push_back(s);

        while(!queue.empty()) {
            // Dequeue a vertex and display it
            s = queue.front();
            std::cout << s << " ";
            queue.pop_front();

            // Get all adjacent vertices of the dequeued vertex s
            // If an adjacent has not been visited, then mark it visited and enqueue it
            for(auto adjacent : adj[s]) {
                if(!visited[adjacent]) {
                    visited[adjacent] = true;
                    queue.push_back(adjacent);
                }
            } 
        }
    }
};