// Implemenatation of basic graph coloring algorithm
#include <iostream>
#include <list>
#include <cstring>
#include <vector>

struct Node {
    int val;
    std::list<int> adjacency;   // contains the index-number of node in its adjacency
};

void addEdge(std::vector<Node>& nodes, int nodeA, int nodeB) {
    nodes[nodeA].adjacency.push_back(nodeB);
}

// the algorithm always start at the first index of node in the graph
// Return color index assigned to each node. All nodes are in the same order as of input nodes.
std::vector<int> basicGraphColoring(const std::vector<Node>& nodes) {
    if (nodes.size() == 0)
        return {};

    const int numNode = nodes.size();

    std::vector<int> colorResults (numNode, -1);
    // set first color to the first node
    colorResults[0] = 0;

    // auxiliary holder for color idx available to be used to assign to each node
    std::vector<int> tempColorAvailable (numNode, true);
    std::memset(tempColorAvailable.data(), true, sizeof(bool) * numNode);

    // mark color as available
    for (int i=1; i<numNode; ++i) {
        for (auto it = nodes[i].adjacency.begin(); it != nodes[i].adjacency.end(); ++it) {
            if (colorResults[*it] != -1) {                           // if node is not assigned with color yet
                tempColorAvailable[colorResults[*it]] = false;       // mark color as not available
            }
        }
        
        // find the available color
        int colorIdx;
        for (int j=0; j<numNode; ++j) {
            if (tempColorAvailable[j]) {
                colorIdx = j;       // found the first available color to use
                break;
            }
        }

        // assign color to node
        colorResults[i] = colorIdx;

        // reset all temporary color available
        std::memset(tempColorAvailable.data(), true, sizeof(bool) * numNode);
    }

    return colorResults;
}

int main()
{
    {
        // testcase#1
        std::vector<Node> nodes (5, {.val = -1});
        for (int i=0; i<nodes.size(); ++i) {
            nodes[i].val = i;
        }

        addEdge(nodes, 0, 1);
        addEdge(nodes, 0, 2);
        addEdge(nodes, 1, 0);
        addEdge(nodes, 1, 2);
        addEdge(nodes, 1, 3);
        addEdge(nodes, 2, 0);
        addEdge(nodes, 2, 1);
        addEdge(nodes, 2, 3);
        addEdge(nodes, 3, 1);
        addEdge(nodes, 3, 2);
        addEdge(nodes, 3, 4);
        addEdge(nodes, 4, 3);

        std::vector<int> colorResults = basicGraphColoring(nodes);
        for (int i=0; i<colorResults.size(); ++i) {
            std::cout << "Node: " << i << " [value: " << nodes[i].val << "] has color " << colorResults[i] << '\n';
        }
    }

    std::cout << '\n';

    {
        // testcase#2
        std::vector<Node> nodes (5, {.val = -1});
        for (int i=0; i<nodes.size(); ++i) {
            nodes[i].val = i;
        }

        addEdge(nodes, 0, 1);
        addEdge(nodes, 0, 2);
        addEdge(nodes, 1, 0);
        addEdge(nodes, 1, 2);
        addEdge(nodes, 1, 3);
        addEdge(nodes, 2, 0);
        addEdge(nodes, 2, 1);
        addEdge(nodes, 2, 4);
        addEdge(nodes, 4, 1);
        addEdge(nodes, 4, 2);
        addEdge(nodes, 4, 3);
        addEdge(nodes, 3, 4);

        std::vector<int> colorResults = basicGraphColoring(nodes);
        for (int i=0; i<colorResults.size(); ++i) {
            std::cout << "Node: " << i << " [value: " << nodes[i].val << "] has color " << colorResults[i] << '\n';
        }
    }

    return 0;
}
