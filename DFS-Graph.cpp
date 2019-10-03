/**
 * Implementation of DFS for Graph.
 *
 * With the graph setup of https://media.geeksforgeeks.org/wp-content/uploads/bfs-5.png
 * Or the following in text
 *  - 2 (treat it as value) is root
 *  - 2 points to 0
 *  - 2 points to 3
 *  - 0 points to 2
 *  - 0 points to 1
 *  - 1 points to 2
 *  - 3 point to 3
 *
 *  Concept of implementation
 *      - have a dedicated memory space on stack to store all Vertex, not individually allocated
 *      - Vertex struct has information for its connected Vertices as std::forward_list<int> to store its indexed-based locations
 *      - have externall a couple of utility functions to manage DFS, we could even create just one class to manage this i.e. Graph but this opts for simplicity
 *      - indexed-based location representing each Vertex is used for ease of implementation and aligned with locating individual Vertex on a single allocated memory space
 *
 *  Note: If you compare the result from this implementation to result from https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/, it's different but that's because it's due to the order we inserted an edge between vertex. In this case we use std::forward_list which has no push_back() or inserting into the end, thus it will prepend new vertex at the beginning. Another way to make it the same result is to reversely add new edge.
 */

#include <iostream>
#include <forward_list>

#define NUM_VERTICES 4

struct Vertex
{
    // value for this vertex
    int value;

    // adajency list, containing the index-based location of Vertex
    std::forward_list<int> adjacency;
};

static void DFS_(const Vertex v[], bool visited[], int start, int num_vertices)
{
    // mark root vertex as visited
    visited[start] = true;
    std::cout << start << " ";

    for (auto it = v[start].adjacency.begin(); it != v[start].adjacency.end(); ++it)
    {
        int itVal = *it;
        if (!visited[itVal])
        {
            DFS_(v, visited, itVal, num_vertices); 
        }
    }
}
static void DFS(const Vertex v[], int start, int num_vertices)
{
    // started off with all false for our memo of visited vertices
    bool visited[num_vertices];
    for (int i=0; i<num_vertices; ++i)
        visited[i] = false;

    DFS_(v, visited, start, num_vertices);
}

static void AddEdge(Vertex* vertices, int u, int v)
{
    vertices[u].adjacency.push_front(v);
}

int main()
{
    Vertex v[NUM_VERTICES];
    for (int i=0; i<NUM_VERTICES; ++i)
    {
        v[i].value = i;
    }

    AddEdge(v, 2, 0);
    AddEdge(v, 2, 3);
    AddEdge(v, 1, 2);
    AddEdge(v, 0, 1);
    AddEdge(v, 0, 2);
    AddEdge(v, 3, 3);

    DFS(v, 2, NUM_VERTICES);

    return 0;
}
