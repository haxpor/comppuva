/**
 * Implementation of BFS for graph using std::queue as auxiliary data structure to hold breadth-first
 * storage.
 *
 * The problem set is as follows
 *  - 2 (treat it as value) is root
 *  - 2 points to 0
 *  - 2 points to 3
 *  - 0 points to 2
 *  - 0 points to 1
 *  - 1 points to 2
 *  - 3 point to 3
 */

#include <iostream>
#include <list>
#include <queue>

#define NUM_VERTICES 4

struct Vertex
{
    // value for this vertex
    int value;

    // adajency list, containing the index-based location of Vertex
    std::list<int> adjacency;
};

static void BFS(const Vertex v[], int start, int num_vertices)
{
    // started off with all false for our memo of visited vertices
    bool visited[num_vertices];
    for (int i=0; i<num_vertices; ++i)
        visited[i] = false;

    // will save those visited vertex serving for breadth-first
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int vi = q.front();   
        std::cout << vi << " ";
        q.pop();

        // before we traverse deeper, store its nearby connected vertices first
        // so we can process it one by one in the next future loop before further traversal
        auto adjacencyList = v[vi].adjacency;
        for (auto it=adjacencyList.begin(); it != adjacencyList.end(); ++it)
        {
            int ii = *it;
            if (!visited[ii])
            {
                visited[ii] = true;
                q.push(ii);
            }
        }
    }
}

static void AddEdge(Vertex* vertices, int u, int v)
{
    vertices[u].adjacency.push_back(v);
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

    BFS(v, 2, NUM_VERTICES);

    return 0;
}
